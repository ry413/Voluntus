/*
 * eez-framework
 *
 * MIT License
 * Copyright 2024 Envox d.o.o.
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <eez/conf-internal.h>

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>

#include <eez/core/debug.h>
#include <eez/core/os.h>
#include <eez/core/util.h>
#include <eez/core/utf8.h>

#include <eez/flow/flow.h>
#include <eez/flow/private.h>
#include <eez/flow/debugger.h>
#include <eez/flow/hooks.h>

namespace eez {
namespace flow {

#define MAX_ARRAY_SIZE_TRANSFERRED_IN_DEBUGGER 1000

enum MessagesToDebugger {
    MESSAGE_TO_DEBUGGER_STATE_CHANGED, // STATE

    MESSAGE_TO_DEBUGGER_ADD_TO_QUEUE, // FLOW_STATE_INDEX, SOURCE_COMPONENT_INDEX, SOURCE_OUTPUT_INDEX, TARGET_COMPONENT_INDEX, TARGET_INPUT_INDEX, FREE_MEMORT, ALLOC_MEMORY
    MESSAGE_TO_DEBUGGER_REMOVE_FROM_QUEUE, // no params

    MESSAGE_TO_DEBUGGER_GLOBAL_VARIABLE_INIT, // GLOBAL_VARIABLE_INDEX, VALUE_ADDR, VALUE
    MESSAGE_TO_DEBUGGER_LOCAL_VARIABLE_INIT, // FLOW_STATE_INDEX, LOCAL_VARIABLE_INDEX, VALUE_ADDR, VALUE
    MESSAGE_TO_DEBUGGER_COMPONENT_INPUT_INIT, // FLOW_STATE_INDEX, COMPONENT_INPUT_INDEX, VALUE_ADDR, VALUE

    MESSAGE_TO_DEBUGGER_VALUE_CHANGED, // VALUE_ADDR, VALUE

    MESSAGE_TO_DEBUGGER_FLOW_STATE_CREATED, // FLOW_STATE_INDEX, FLOW_INDEX, PARENT_FLOW_STATE_INDEX (-1 - NO PARENT), PARENT_COMPONENT_INDEX (-1 - NO PARENT COMPONENT)
    MESSAGE_TO_DEBUGGER_FLOW_STATE_TIMELINE_CHANGED, // FLOW_STATE_INDEX, TIMELINE_POSITION
    MESSAGE_TO_DEBUGGER_FLOW_STATE_DESTROYED, // FLOW_STATE_INDEX

	MESSAGE_TO_DEBUGGER_FLOW_STATE_ERROR, // FLOW_STATE_INDEX, COMPONENT_INDEX, ERROR_MESSAGE

    MESSAGE_TO_DEBUGGER_LOG, // LOG_ITEM_TYPE, FLOW_STATE_INDEX, COMPONENT_INDEX, MESSAGE

	MESSAGE_TO_DEBUGGER_PAGE_CHANGED, // PAGE_ID

    MESSAGE_TO_DEBUGGER_COMPONENT_EXECUTION_STATE_CHANGED, // FLOW_STATE_INDEX, COMPONENT_INDEX, STATE
    MESSAGE_TO_DEBUGGER_COMPONENT_ASYNC_STATE_CHANGED // FLOW_STATE_INDEX, COMPONENT_INDEX, STATE
};

enum MessagesFromDebugger {
    MESSAGE_FROM_DEBUGGER_RESUME, // no params
    MESSAGE_FROM_DEBUGGER_PAUSE, // no params
    MESSAGE_FROM_DEBUGGER_SINGLE_STEP, // no params

    MESSAGE_FROM_DEBUGGER_ADD_BREAKPOINT, // FLOW_INDEX, COMPONENT_INDEX
    MESSAGE_FROM_DEBUGGER_REMOVE_BREAKPOINT, // FLOW_INDEX, COMPONENT_INDEX
    MESSAGE_FROM_DEBUGGER_ENABLE_BREAKPOINT, // FLOW_INDEX, COMPONENT_INDEX
    MESSAGE_FROM_DEBUGGER_DISABLE_BREAKPOINT, // FLOW_INDEX, COMPONENT_INDEX

    MESSAGE_FROM_DEBUGGER_MODE // MODE (0:RUN | 1:DEBUG)
};

enum LogItemType {
	LOG_ITEM_TYPE_FATAL,
	LOG_ITEM_TYPE_ERROR,
    LOG_ITEM_TYPE_WARNING ,
    LOG_ITEM_TYPE_SCPI,
    LOG_ITEM_TYPE_INFO,
    LOG_ITEM_TYPE_DEBUG
};

enum DebuggerState {
    DEBUGGER_STATE_RESUMED,
    DEBUGGER_STATE_PAUSED,
    DEBUGGER_STATE_SINGLE_STEP,
    DEBUGGER_STATE_STOPPED,
};

bool g_debuggerIsConnected;
static uint32_t g_messageSubsciptionFilter = 0xFFFFFFFF;

static DebuggerState g_debuggerState;
static bool g_skipNextBreakpoint;

static char g_inputFromDebugger[64];
static unsigned g_inputFromDebuggerPosition;

int g_debuggerMode = DEBUGGER_MODE_RUN;

////////////////////////////////////////////////////////////////////////////////

void setDebuggerMessageSubsciptionFilter(uint32_t filter) {
    g_messageSubsciptionFilter = filter;
}

static bool isSubscribedTo(MessagesToDebugger messageType) {
    if (g_debuggerIsConnected && (g_messageSubsciptionFilter & (1 << messageType)) != 0) {
        startToDebuggerMessageHook();
        return true;
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////

static void setDebuggerState(DebuggerState newState) {
	if (newState != g_debuggerState) {
		g_debuggerState = newState;

		if (isSubscribedTo(MESSAGE_TO_DEBUGGER_STATE_CHANGED)) {
			char buffer[256];
			snprintf(buffer, sizeof(buffer), "%d\t%d\n",
				MESSAGE_TO_DEBUGGER_STATE_CHANGED,
				g_debuggerState
			);
			writeDebuggerBufferHook(buffer, strlen(buffer));
		}
	}
}

////////////////////////////////////////////////////////////////////////////////

void onDebuggerClientConnected() {
    g_debuggerIsConnected = true;

	g_skipNextBreakpoint = false;
	g_inputFromDebuggerPosition = 0;

    setDebuggerState(DEBUGGER_STATE_PAUSED);
}

void onDebuggerClientDisconnected() {
    g_debuggerIsConnected = false;
    setDebuggerState(DEBUGGER_STATE_RESUMED);
}

////////////////////////////////////////////////////////////////////////////////

void processDebuggerInput(char *buffer, uint32_t length) {
	for (uint32_t i = 0; i < length; i++) {
		if (buffer[i] == '\n') {
			int messageFromDebugger = g_inputFromDebugger[0] - '0';

			if (messageFromDebugger == MESSAGE_FROM_DEBUGGER_RESUME) {
				setDebuggerState(DEBUGGER_STATE_RESUMED);
			} else if (messageFromDebugger == MESSAGE_FROM_DEBUGGER_PAUSE) {
				setDebuggerState(DEBUGGER_STATE_PAUSED);
			} else if (messageFromDebugger == MESSAGE_FROM_DEBUGGER_SINGLE_STEP) {
				setDebuggerState(DEBUGGER_STATE_SINGLE_STEP);
			} else if (
				messageFromDebugger >= MESSAGE_FROM_DEBUGGER_ADD_BREAKPOINT &&
				messageFromDebugger <= MESSAGE_FROM_DEBUGGER_DISABLE_BREAKPOINT
			) {
				char *p;
				auto flowIndex = (uint32_t)strtol(g_inputFromDebugger + 2, &p, 10);
				auto componentIndex = (uint32_t)strtol(p + 1, nullptr, 10);

				auto assets = g_firstFlowState->assets;
				auto flowDefinition = static_cast<FlowDefinition *>(assets->flowDefinition);
				if (flowIndex < flowDefinition->flows.count) {
					auto flow = flowDefinition->flows[flowIndex];
					if (componentIndex < flow->components.count) {
						auto component = flow->components[componentIndex];

						component->breakpoint = messageFromDebugger == MESSAGE_FROM_DEBUGGER_ADD_BREAKPOINT ||
							messageFromDebugger == MESSAGE_FROM_DEBUGGER_ENABLE_BREAKPOINT ? 1 : 0;
					} else {
						ErrorTrace("Invalid breakpoint component index\n");
					}
				} else {
					ErrorTrace("Invalid breakpoint flow index\n");
				}
			} else if (messageFromDebugger == MESSAGE_FROM_DEBUGGER_MODE) {
                g_debuggerMode = strtol(g_inputFromDebugger + 2, nullptr, 10);
#if EEZ_OPTION_GUI
                gui::refreshScreen();
#endif
            }

			g_inputFromDebuggerPosition = 0;
		} else {
			if (g_inputFromDebuggerPosition < sizeof(g_inputFromDebugger)) {
				g_inputFromDebugger[g_inputFromDebuggerPosition++] = buffer[i];
			} else if (g_inputFromDebuggerPosition == sizeof(g_inputFromDebugger)) {
				ErrorTrace("Input from debugger buffer overflow\n");
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////

bool canExecuteStep(FlowState *&flowState, unsigned &componentIndex) {
    if (!g_debuggerIsConnected) {
        return true;
    }

    if (!isSubscribedTo(MESSAGE_TO_DEBUGGER_ADD_TO_QUEUE)) {
        return true;
    }

    if (g_debuggerState == DEBUGGER_STATE_PAUSED) {
        return false;
    }

    if (g_debuggerState == DEBUGGER_STATE_SINGLE_STEP) {
        g_skipNextBreakpoint = false;
	    setDebuggerState(DEBUGGER_STATE_PAUSED);
        return true;
    }

    // g_debuggerState == DEBUGGER_STATE_RESUMED

    auto component = flowState->flow->components[componentIndex];

    if (g_skipNextBreakpoint) {
        if (component->breakpoint) {
            g_skipNextBreakpoint = false;
        }
    } else {
        if (component->breakpoint) {
            g_skipNextBreakpoint = true;
			setDebuggerState(DEBUGGER_STATE_PAUSED);
            return false;
        }
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////

#if defined(__EMSCRIPTEN__)
char outputBuffer[1024 * 1024];
#else
char outputBuffer[64];
#endif
int outputBufferPosition = 0;

#define WRITE_TO_OUTPUT_BUFFER(ch) \
	outputBuffer[outputBufferPosition++] = ch; \
	if (outputBufferPosition == sizeof(outputBuffer)) { \
		writeDebuggerBufferHook(outputBuffer, outputBufferPosition); \
		outputBufferPosition = 0; \
	}

#define FLUSH_OUTPUT_BUFFER() \
	if (outputBufferPosition > 0) { \
		writeDebuggerBufferHook(outputBuffer, outputBufferPosition); \
		outputBufferPosition = 0; \
	}

static void writeValueAddr(const void *pValue) {
	char tmpStr[32];
	snprintf(tmpStr, sizeof(tmpStr), "%p", pValue);
	auto len = strlen(tmpStr);
	for (size_t i = 0; i < len; i++) {
		WRITE_TO_OUTPUT_BUFFER(tmpStr[i]);
	}
}

static void writeString(const char *str) {
	WRITE_TO_OUTPUT_BUFFER('"');

    while (true) {
        utf8_int32_t cp;
        str = utf8codepoint(str, &cp);
        if (!cp) {
            break;
        }

        if (cp == '"') {
			WRITE_TO_OUTPUT_BUFFER('\\');
			WRITE_TO_OUTPUT_BUFFER('"');
		} else if (cp == '\t') {
			WRITE_TO_OUTPUT_BUFFER('\\');
			WRITE_TO_OUTPUT_BUFFER('t');
		} else if (cp == '\n') {
			WRITE_TO_OUTPUT_BUFFER('\\');
			WRITE_TO_OUTPUT_BUFFER('n');
		} else if (cp >= 32 && cp < 127) {
			WRITE_TO_OUTPUT_BUFFER(cp);
        } else {
            char temp[32];
            snprintf(temp, sizeof(temp), "\\u%04x", (int)cp);
            for (size_t i = 0; i < strlen(temp); i++) {
			    WRITE_TO_OUTPUT_BUFFER(temp[i]);
            }
        }
    }

	WRITE_TO_OUTPUT_BUFFER('"');
	WRITE_TO_OUTPUT_BUFFER('\n');
	FLUSH_OUTPUT_BUFFER();
}

static void writeArrayType(uint32_t arrayType) {
	char tmpStr[32];
	snprintf(tmpStr, sizeof(tmpStr), "%x", (int)arrayType);
	auto len = strlen(tmpStr);
	for (size_t i = 0; i < len; i++) {
		WRITE_TO_OUTPUT_BUFFER(tmpStr[i]);
	}
}

static void writeArray(const ArrayValue *arrayValue) {
	WRITE_TO_OUTPUT_BUFFER('{');

	writeValueAddr(arrayValue);

    WRITE_TO_OUTPUT_BUFFER(',');
    writeArrayType(arrayValue->arraySize);

    WRITE_TO_OUTPUT_BUFFER(',');
    writeArrayType(arrayValue->arrayType);

    auto transferredSize = arrayValue->arraySize > MAX_ARRAY_SIZE_TRANSFERRED_IN_DEBUGGER ? MAX_ARRAY_SIZE_TRANSFERRED_IN_DEBUGGER : arrayValue->arraySize;

	for (uint32_t i = 0; i < transferredSize; i++) {
		WRITE_TO_OUTPUT_BUFFER(',');
		writeValueAddr(&arrayValue->values[i]);
	}

	WRITE_TO_OUTPUT_BUFFER('}');
	WRITE_TO_OUTPUT_BUFFER('\n');
	FLUSH_OUTPUT_BUFFER();

    for (uint32_t i = 0; i < transferredSize; i++) {
        onValueChanged(&arrayValue->values[i]);
    }
}

static void writeHex(char *dst, uint8_t *src, size_t srcLength) {
    *dst++ = 'H';
    for (size_t i = 0; i < srcLength; i++) {
        *dst++ = toHexDigit(src[i] / 16);
        *dst++ = toHexDigit(src[i] % 16);
    }
    *dst++ = 0;
}

static void writeValue(const Value &value) {
	char tempStr[64];

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4474)
#endif

	switch (value.getType()) {
	case VALUE_TYPE_UNDEFINED:
		stringCopy(tempStr, sizeof(tempStr) - 1, "undefined");
		break;

	case VALUE_TYPE_NULL:
		stringCopy(tempStr, sizeof(tempStr) - 1, "null");
		break;

	case VALUE_TYPE_BOOLEAN:
		stringCopy(tempStr, sizeof(tempStr) - 1, value.getBoolean() ? "true" : "false");
		break;

	case VALUE_TYPE_INT8:
		snprintf(tempStr, sizeof(tempStr) - 1, "%" PRId8 "", value.int8Value);
		break;

	case VALUE_TYPE_UINT8:
		snprintf(tempStr, sizeof(tempStr) - 1, "%" PRIu8 "", value.uint8Value);
		break;

	case VALUE_TYPE_INT16:
		snprintf(tempStr, sizeof(tempStr) - 1, "%" PRId16 "", value.int16Value);
		break;

	case VALUE_TYPE_UINT16:
		snprintf(tempStr, sizeof(tempStr) - 1, "%" PRIu16 "", value.uint16Value);
		break;

	case VALUE_TYPE_INT32:
		snprintf(tempStr, sizeof(tempStr) - 1, "%" PRId32 "", value.int32Value);
		break;

	case VALUE_TYPE_UINT32:
		snprintf(tempStr, sizeof(tempStr) - 1, "%" PRIu32 "", value.uint32Value);
		break;

	case VALUE_TYPE_INT64:
#ifdef PRId64
		snprintf(tempStr, sizeof(tempStr) - 1, "%" PRId64 "", value.int64Value);
#else
		snprintf(tempStr, sizeof(tempStr) - 1, "%" PRId32 "", (int32_t)value.int64Value);
#endif
		break;

	case VALUE_TYPE_UINT64:
#ifdef PRIu64
		snprintf(tempStr, sizeof(tempStr) - 1, "%" PRIu64 "", value.uint64Value);
#else
		snprintf(tempStr, sizeof(tempStr) - 1, "%" PRIu32 "", (uint32_t)value.uint64Value);
#endif
		break;

	case VALUE_TYPE_DOUBLE:
        writeHex(tempStr, (uint8_t *)&value.doubleValue, sizeof(double));
		break;

	case VALUE_TYPE_FLOAT:
        writeHex(tempStr, (uint8_t *)&value.floatValue, sizeof(float));
		break;

	case VALUE_TYPE_STRING:
    case VALUE_TYPE_STRING_ASSET:
	case VALUE_TYPE_STRING_REF:
		writeString(value.getString());
		return;

	case VALUE_TYPE_ARRAY:
    case VALUE_TYPE_ARRAY_ASSET:
	case VALUE_TYPE_ARRAY_REF:
		writeArray(value.getArray());
		return;

	case VALUE_TYPE_BLOB_REF:
		snprintf(tempStr, sizeof(tempStr) - 1, "@%d", (int)((BlobRef *)value.refValue)->len);
		break;

	case VALUE_TYPE_STREAM:
		snprintf(tempStr, sizeof(tempStr) - 1, ">%d", (int)(value.int32Value));
		break;

	case VALUE_TYPE_JSON:
		snprintf(tempStr, sizeof(tempStr) - 1, "#%d", (int)(value.int32Value));
		break;

	case VALUE_TYPE_DATE:
        tempStr[0] = '!';
		writeHex(tempStr + 1, (uint8_t *)&value.doubleValue, sizeof(double));
		break;

    case VALUE_TYPE_POINTER:
        snprintf(tempStr, sizeof(tempStr) - 1, "%p", value.getVoidPointer());
		break;

	case VALUE_TYPE_WIDGET:
		snprintf(tempStr, sizeof(tempStr) - 1, "*p%p", value.getVoidPointer());
		break;

	case VALUE_TYPE_EVENT:
		snprintf(tempStr, sizeof(tempStr) - 1, "!!%p", value.getVoidPointer());
		break;

	default:
		tempStr[0] = 0;
		break;
	}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

	stringAppendString(tempStr, sizeof(tempStr), "\n");

	writeDebuggerBufferHook(tempStr, strlen(tempStr));
}

////////////////////////////////////////////////////////////////////////////////

void onStarted(Assets *assets) {
    if (isSubscribedTo(MESSAGE_TO_DEBUGGER_GLOBAL_VARIABLE_INIT)) {
		auto flowDefinition = static_cast<FlowDefinition *>(assets->flowDefinition);

        if (g_globalVariables) {
            for (uint32_t i = 0; i < g_globalVariables->count; i++) {
                auto pValue = g_globalVariables->values + i;

                char buffer[256];
                snprintf(buffer, sizeof(buffer), "%d\t%d\t%p\t",
                    MESSAGE_TO_DEBUGGER_GLOBAL_VARIABLE_INIT,
                    (int)i,
                    (const void *)pValue
                );
                writeDebuggerBufferHook(buffer, strlen(buffer));

                writeValue(*pValue);
            }
        } else {
            for (uint32_t i = 0; i < flowDefinition->globalVariables.count; i++) {
                auto pValue = flowDefinition->globalVariables[i];

                char buffer[256];
                snprintf(buffer, sizeof(buffer), "%d\t%d\t%p\t",
                    MESSAGE_TO_DEBUGGER_GLOBAL_VARIABLE_INIT,
                    (int)i,
                    (const void *)pValue
                );
                writeDebuggerBufferHook(buffer, strlen(buffer));

                writeValue(*pValue);
            }
        }
    }
}

void onStopped() {
    setDebuggerState(DEBUGGER_STATE_STOPPED);
}

void onAddToQueue(FlowState *flowState, int sourceComponentIndex, int sourceOutputIndex, unsigned targetComponentIndex, int targetInputIndex) {
    if (isSubscribedTo(MESSAGE_TO_DEBUGGER_ADD_TO_QUEUE)) {
        uint32_t free;
        uint32_t alloc;
        getAllocInfo(free, alloc);

        char buffer[256];
		snprintf(buffer, sizeof(buffer), "%d\t%d\t%d\t%d\t%d\t%d\t%u\t%u\n",
			MESSAGE_TO_DEBUGGER_ADD_TO_QUEUE,
			(int)flowState->flowStateIndex,
			sourceComponentIndex,
			sourceOutputIndex,
			targetComponentIndex,
			targetInputIndex,
            (unsigned int)free,
            (unsigned int)ALLOC_BUFFER_SIZE
		);
        writeDebuggerBufferHook(buffer, strlen(buffer));
    }
}

void onRemoveFromQueue() {
    if (isSubscribedTo(MESSAGE_TO_DEBUGGER_REMOVE_FROM_QUEUE)) {
        char buffer[256];
		snprintf(buffer, sizeof(buffer), "%d\n",
			MESSAGE_TO_DEBUGGER_REMOVE_FROM_QUEUE
		);
        writeDebuggerBufferHook(buffer, strlen(buffer));
    }
}

void onValueChanged(const Value *pValue) {
    if (isSubscribedTo(MESSAGE_TO_DEBUGGER_VALUE_CHANGED)) {
        char buffer[256];
		snprintf(buffer, sizeof(buffer), "%d\t%p\t",
			MESSAGE_TO_DEBUGGER_VALUE_CHANGED,
            (const void *)pValue
		);
        writeDebuggerBufferHook(buffer, strlen(buffer));

		writeValue(pValue->getValue());
    }
}

void onFlowStateCreated(FlowState *flowState) {
    if (isSubscribedTo(MESSAGE_TO_DEBUGGER_FLOW_STATE_CREATED)) {
        char buffer[256];
		snprintf(buffer, sizeof(buffer), "%d\t%d\t%d\t%d\t%d\n",
			MESSAGE_TO_DEBUGGER_FLOW_STATE_CREATED,
			(int)flowState->flowStateIndex,
			(int)flowState->flowIndex,
			(int)(flowState->parentFlowState ? flowState->parentFlowState->flowStateIndex : -1),
			(int)flowState->parentComponentIndex
		);
        writeDebuggerBufferHook(buffer, strlen(buffer));
    }

    if (isSubscribedTo(MESSAGE_TO_DEBUGGER_LOCAL_VARIABLE_INIT)) {
		auto flow = flowState->flow;

		for (uint32_t i = 0; i < flow->localVariables.count; i++) {
			auto pValue = &flowState->values[flow->componentInputs.count + i];

            char buffer[256];
            snprintf(buffer, sizeof(buffer), "%d\t%d\t%d\t%p\t",
                MESSAGE_TO_DEBUGGER_LOCAL_VARIABLE_INIT,
				(int)flowState->flowStateIndex,
				(int)i,
                (const void *)pValue
            );
            writeDebuggerBufferHook(buffer, strlen(buffer));

			writeValue(*pValue);
        }
    }

    if (isSubscribedTo(MESSAGE_TO_DEBUGGER_COMPONENT_INPUT_INIT)) {
		auto flow = flowState->flow;

		for (uint32_t i = 0; i < flow->componentInputs.count; i++) {
			//auto &input = flow->componentInputs[i];
			//if (!(input & COMPONENT_INPUT_FLAG_IS_SEQ_INPUT)) {
				auto pValue = &flowState->values[i];

				char buffer[256];
				snprintf(buffer, sizeof(buffer), "%d\t%d\t%d\t%p\t",
					MESSAGE_TO_DEBUGGER_COMPONENT_INPUT_INIT,
					(int)flowState->flowStateIndex,
					(int)i,
					(const void *)pValue
				);
				writeDebuggerBufferHook(buffer, strlen(buffer));

				writeValue(*pValue);
			//}
        }
	}
}

void onFlowStateDestroyed(FlowState *flowState) {
	if (isSubscribedTo(MESSAGE_TO_DEBUGGER_FLOW_STATE_DESTROYED)) {
		char buffer[256];
		snprintf(buffer, sizeof(buffer), "%d\t%d\n",
			MESSAGE_TO_DEBUGGER_FLOW_STATE_DESTROYED,
			(int)flowState->flowStateIndex
		);
		writeDebuggerBufferHook(buffer, strlen(buffer));
	}
}

void onFlowStateTimelineChanged(FlowState *flowState) {
	if (isSubscribedTo(MESSAGE_TO_DEBUGGER_FLOW_STATE_TIMELINE_CHANGED)) {
		char buffer[256];
		snprintf(buffer, sizeof(buffer), "%d\t%d\t%g\n",
			MESSAGE_TO_DEBUGGER_FLOW_STATE_TIMELINE_CHANGED,
			(int)flowState->flowStateIndex,
            flowState->timelinePosition
		);
		writeDebuggerBufferHook(buffer, strlen(buffer));
	}
}

void onFlowError(FlowState *flowState, int componentIndex, const char *errorMessage) {
	if (isSubscribedTo(MESSAGE_TO_DEBUGGER_FLOW_STATE_ERROR)) {
		char buffer[256];
		snprintf(buffer, sizeof(buffer), "%d\t%d\t%d\t",
			MESSAGE_TO_DEBUGGER_FLOW_STATE_ERROR,
			(int)flowState->flowStateIndex,
			componentIndex
		);
		writeDebuggerBufferHook(buffer, strlen(buffer));
		writeString(errorMessage);
	}

    if (onFlowErrorHook) {
        onFlowErrorHook(flowState, componentIndex, errorMessage);
    }
}

void onComponentExecutionStateChanged(FlowState *flowState, int componentIndex) {
	if (isSubscribedTo(MESSAGE_TO_DEBUGGER_COMPONENT_EXECUTION_STATE_CHANGED)) {
		char buffer[256];
		snprintf(buffer, sizeof(buffer), "%d\t%d\t%d\t%p\n",
			MESSAGE_TO_DEBUGGER_COMPONENT_EXECUTION_STATE_CHANGED,
			(int)flowState->flowStateIndex,
			componentIndex,
            (void *)flowState->componenentExecutionStates[componentIndex]
		);

        writeDebuggerBufferHook(buffer, strlen(buffer));
	}
}

void onComponentAsyncStateChanged(FlowState *flowState, int componentIndex) {
	if (isSubscribedTo(MESSAGE_TO_DEBUGGER_COMPONENT_ASYNC_STATE_CHANGED)) {
		char buffer[256];
		snprintf(buffer, sizeof(buffer), "%d\t%d\t%d\t%d\n",
			MESSAGE_TO_DEBUGGER_COMPONENT_ASYNC_STATE_CHANGED,
			(int)flowState->flowStateIndex,
			componentIndex,
            flowState->componenentAsyncStates[componentIndex] ? 1 : 0
		);

        writeDebuggerBufferHook(buffer, strlen(buffer));
	}
}

static void writeLogMessage(const char *str) {
	for (const char *p = str; *p; p++) {
		if (*p == '\t') {
			WRITE_TO_OUTPUT_BUFFER('\\');
			WRITE_TO_OUTPUT_BUFFER('t');
		} if (*p == '\n') {
			WRITE_TO_OUTPUT_BUFFER('\\');
			WRITE_TO_OUTPUT_BUFFER('n');
		} else {
			WRITE_TO_OUTPUT_BUFFER(*p);
		}
	}

	WRITE_TO_OUTPUT_BUFFER('\n');
	FLUSH_OUTPUT_BUFFER();
}

static void writeLogMessage(const char *str, size_t len) {
	for (size_t i = 0; i < len; i++) {
		if (str[i] == '\t') {
			WRITE_TO_OUTPUT_BUFFER('\\');
			WRITE_TO_OUTPUT_BUFFER('t');
		} if (str[i] == '\n') {
			WRITE_TO_OUTPUT_BUFFER('\\');
			WRITE_TO_OUTPUT_BUFFER('n');
		} else {
			WRITE_TO_OUTPUT_BUFFER(str[i]);
		}
	}

	WRITE_TO_OUTPUT_BUFFER('\n');
	FLUSH_OUTPUT_BUFFER();
}

void logInfo(FlowState *flowState, unsigned componentIndex, const char *message) {
#if defined(EEZ_FOR_LVGL)
    LV_LOG_USER("EEZ-FLOW: %s", message);
#endif

	if (isSubscribedTo(MESSAGE_TO_DEBUGGER_LOG)) {
		char buffer[256];
		snprintf(buffer, sizeof(buffer), "%d\t%d\t%d\t%d\t",
			MESSAGE_TO_DEBUGGER_LOG,
            LOG_ITEM_TYPE_INFO,
            (int)flowState->flowStateIndex,
			componentIndex
		);
		writeDebuggerBufferHook(buffer, strlen(buffer));
		writeLogMessage(message);
    }
}

void logScpiCommand(FlowState *flowState, unsigned componentIndex, const char *cmd) {
	if (isSubscribedTo(MESSAGE_TO_DEBUGGER_LOG)) {
		char buffer[256];
		snprintf(buffer, sizeof(buffer), "%d\t%d\t%d\t%d\tSCPI COMMAND: ",
			MESSAGE_TO_DEBUGGER_LOG,
            LOG_ITEM_TYPE_SCPI,
            (int)flowState->flowStateIndex,
			componentIndex
		);
		writeDebuggerBufferHook(buffer, strlen(buffer));
		writeLogMessage(cmd);
    }
}

void logScpiQuery(FlowState *flowState, unsigned componentIndex, const char *query) {
	if (isSubscribedTo(MESSAGE_TO_DEBUGGER_LOG)) {
		char buffer[256];
		snprintf(buffer, sizeof(buffer), "%d\t%d\t%d\t%d\tSCPI QUERY: ",
			MESSAGE_TO_DEBUGGER_LOG,
            LOG_ITEM_TYPE_SCPI,
            (int)flowState->flowStateIndex,
			componentIndex
		);
		writeDebuggerBufferHook(buffer, strlen(buffer));
		writeLogMessage(query);
    }
}

void logScpiQueryResult(FlowState *flowState, unsigned componentIndex, const char *resultText, size_t resultTextLen) {
	if (isSubscribedTo(MESSAGE_TO_DEBUGGER_LOG)) {
		char buffer[256];
		snprintf(buffer, sizeof(buffer) - 1, "%d\t%d\t%d\t%d\tSCPI QUERY RESULT: ",
			MESSAGE_TO_DEBUGGER_LOG,
            LOG_ITEM_TYPE_SCPI,
            (int)flowState->flowStateIndex,
			componentIndex
		);
		writeDebuggerBufferHook(buffer, strlen(buffer));
		writeLogMessage(resultText, resultTextLen);
    }
}

#if EEZ_OPTION_GUI
void onPageChanged(int previousPageId, int activePageId, bool activePageIsFromStack, bool previousPageIsStillOnStack) {
    if (flow::isFlowStopped()) {
        return;
    }

    if (previousPageId == activePageId) {
        return;
    }

    if (!previousPageIsStillOnStack) {
        if (previousPageId > 0 && previousPageId < FIRST_INTERNAL_PAGE_ID) {
            auto flowState = getPageFlowState(g_mainAssets, previousPageId - 1, WidgetCursor());
            if (flowState) {
                onEvent(flowState, FLOW_EVENT_CLOSE_PAGE, Value());
            }
        } else if (previousPageId < 0) {
            auto flowState = getPageFlowState(g_externalAssets, -previousPageId - 1, WidgetCursor());
            if (flowState) {
                onEvent(flowState, FLOW_EVENT_CLOSE_PAGE, Value());
            }
        }
    }

    if (!activePageIsFromStack) {
        if (activePageId > 0 && activePageId < FIRST_INTERNAL_PAGE_ID) {
            auto flowState = getPageFlowState(g_mainAssets, activePageId - 1, WidgetCursor());
            if (flowState) {
                onEvent(flowState, FLOW_EVENT_OPEN_PAGE, Value());
            }
        } else if (activePageId < 0) {
            auto flowState = getPageFlowState(g_externalAssets, -activePageId - 1, WidgetCursor());
            if (flowState) {
                onEvent(flowState, FLOW_EVENT_OPEN_PAGE, Value());
            }
        }
    }

	if (isSubscribedTo(MESSAGE_TO_DEBUGGER_PAGE_CHANGED)) {
        char buffer[256];
        snprintf(buffer, sizeof(buffer), "%d\t%d\n",
            MESSAGE_TO_DEBUGGER_PAGE_CHANGED,
            activePageId
        );
        writeDebuggerBufferHook(buffer, strlen(buffer));
    }
}
#else
void onPageChanged(int previousPageId, int activePageId, bool activePageIsFromStack, bool previousPageIsStillOnStack) {
    if (flow::isFlowStopped()) {
        return;
    }

    if (previousPageId == activePageId) {
        return;
    }

    if (!previousPageIsStillOnStack) {
        if (previousPageId > 0) {
            auto flowState = getPageFlowState(g_mainAssets, previousPageId - 1);
            if (flowState) {
                onEvent(flowState, FLOW_EVENT_CLOSE_PAGE, Value());
            }
        }
    }

    if (!activePageIsFromStack) {
        if (activePageId > 0) {
            auto flowState = getPageFlowState(g_mainAssets, activePageId - 1);
            if (flowState) {
                onEvent(flowState, FLOW_EVENT_OPEN_PAGE, Value());
            }
        }
    }

	if (isSubscribedTo(MESSAGE_TO_DEBUGGER_PAGE_CHANGED)) {
        char buffer[256];
        snprintf(buffer, sizeof(buffer), "%d\t%d\n",
            MESSAGE_TO_DEBUGGER_PAGE_CHANGED,
            activePageId
        );
        writeDebuggerBufferHook(buffer, strlen(buffer));
    }
}
#endif // EEZ_OPTION_GUI

} // namespace flow
} // namespace eez
