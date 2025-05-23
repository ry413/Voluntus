#ifdef __has_include
    #if __has_include("lvgl.h")
        #ifndef LV_LVGL_H_INCLUDE_SIMPLE
            #define LV_LVGL_H_INCLUDE_SIMPLE
        #endif
    #endif
#endif
#ifdef __has_include
    #if __has_include("lvgl.h")
        #ifndef LV_LVGL_H_INCLUDE_SIMPLE
            #define LV_LVGL_H_INCLUDE_SIMPLE
        #endif
    #endif
#endif

#if defined(LV_LVGL_H_INCLUDE_SIMPLE)
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif


#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

#ifndef LV_ATTRIBUTE_IMG_IMG_MODE_COOLING
#define LV_ATTRIBUTE_IMG_IMG_MODE_COOLING
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_IMG_MODE_COOLING uint8_t img_mode_cooling_map[] = {
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 0*/
  0xff, 0xff, 0x00, 0x01, 	/*Color of index 1*/
  0xff, 0xaa, 0x55, 0x03, 	/*Color of index 2*/
  0xff, 0x9a, 0x6b, 0x05, 	/*Color of index 3*/
  0xff, 0xb4, 0x7b, 0x07, 	/*Color of index 4*/
  0xff, 0xaf, 0x73, 0x15, 	/*Color of index 5*/
  0xff, 0xae, 0x76, 0x27, 	/*Color of index 6*/
  0xff, 0xae, 0x75, 0x3d, 	/*Color of index 7*/
  0xff, 0xae, 0x76, 0x5c, 	/*Color of index 8*/
  0xff, 0xae, 0x75, 0x7f, 	/*Color of index 9*/
  0xff, 0xae, 0x75, 0x97, 	/*Color of index 10*/
  0xff, 0xae, 0x75, 0xa8, 	/*Color of index 11*/
  0xff, 0xae, 0x75, 0xc4, 	/*Color of index 12*/
  0xff, 0xae, 0x75, 0xe4, 	/*Color of index 13*/
  0xff, 0xae, 0x75, 0xfe, 	/*Color of index 14*/
  0xff, 0x7f, 0x7f, 0x02, 	/*Color of index 15*/

  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8e, 0xe8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9e, 0xe9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9e, 0xe9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x80, 0x9e, 0xe9, 0x17, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9e, 0xe9, 0x9e, 0xe9, 0xae, 0xe6, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9e, 0xee, 0xde, 0xed, 0xee, 0xe7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4b, 0xee, 0xee, 0xee, 0xee, 0xa1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xbe, 0xee, 0xee, 0xea, 0xf0, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x4a, 0xc6, 0x00, 0x00, 0x00, 0x4b, 0xee, 0xee, 0xaf, 0x00, 0x00, 0x00, 0x8d, 0xd4, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x04, 0x97, 0x00, 0x7e, 0xeb, 0x00, 0x00, 0x00, 0x00, 0xae, 0xea, 0x00, 0x00, 0x00, 0x00, 0xce, 0xe7, 0x00, 0x79, 0x50, 0x00, 0x00, 
  0x00, 0x00, 0x0b, 0xee, 0xb6, 0x6e, 0xee, 0x40, 0x00, 0x00, 0x00, 0x9e, 0xe9, 0x00, 0x00, 0x00, 0x04, 0xee, 0xe5, 0x6b, 0xee, 0xb0, 0x00, 0x00, 
  0x00, 0x00, 0x0b, 0xee, 0xee, 0x9d, 0xee, 0x70, 0x00, 0x00, 0x00, 0x9e, 0xe9, 0x00, 0x00, 0x00, 0x07, 0xee, 0xd9, 0xee, 0xee, 0xb0, 0x00, 0x00, 
  0x00, 0x00, 0x05, 0xbe, 0xee, 0xee, 0xee, 0x90, 0x00, 0x00, 0x00, 0x9e, 0xe9, 0x00, 0x00, 0x00, 0x09, 0xee, 0xee, 0xee, 0xeb, 0x50, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x07, 0xce, 0xee, 0xee, 0xa0, 0x00, 0x00, 0x00, 0x9e, 0xe9, 0x00, 0x00, 0x00, 0x0b, 0xee, 0xee, 0xec, 0x70, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x6c, 0xee, 0xee, 0xeb, 0x50, 0x00, 0x00, 0x9e, 0xe9, 0x00, 0x00, 0x05, 0xbe, 0xee, 0xee, 0xc6, 0x10, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x5c, 0xee, 0xee, 0xee, 0xee, 0xe9, 0x30, 0x00, 0x9e, 0xe9, 0x00, 0x03, 0x9e, 0xee, 0xee, 0xee, 0xee, 0xc3, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x8e, 0xee, 0xee, 0xcb, 0xee, 0xee, 0xd8, 0x00, 0x9e, 0xe9, 0x00, 0x8d, 0xee, 0xee, 0xbc, 0xee, 0xee, 0xe6, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x5d, 0xeb, 0x96, 0x00, 0x7c, 0xee, 0xee, 0xc6, 0x9e, 0xe9, 0x6c, 0xee, 0xee, 0xc7, 0x00, 0x68, 0xbd, 0xa1, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x01, 0x30, 0x00, 0x00, 0x02, 0x8d, 0xee, 0xee, 0xde, 0xed, 0xee, 0xee, 0xd8, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x9e, 0xee, 0xee, 0xee, 0xee, 0xea, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0xbe, 0xee, 0xee, 0xec, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0xbe, 0xee, 0xee, 0xec, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x9e, 0xee, 0xee, 0xee, 0xee, 0xea, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x8d, 0xee, 0xee, 0xde, 0xed, 0xee, 0xee, 0xd8, 0x20, 0x00, 0x00, 0x02, 0x20, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x1b, 0xdb, 0x86, 0x00, 0x7c, 0xee, 0xee, 0xc6, 0x9e, 0xe9, 0x6c, 0xee, 0xee, 0xc7, 0x00, 0x69, 0xbe, 0xd5, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x6e, 0xee, 0xee, 0xcb, 0xee, 0xee, 0xd8, 0x00, 0x9e, 0xe9, 0x00, 0x8d, 0xee, 0xee, 0xbc, 0xee, 0xee, 0xe8, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x3c, 0xee, 0xee, 0xee, 0xee, 0xe9, 0x40, 0x00, 0x9e, 0xe9, 0x00, 0x04, 0x9e, 0xee, 0xee, 0xee, 0xee, 0xc5, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x01, 0x6c, 0xee, 0xee, 0xeb, 0x50, 0x00, 0x00, 0x9e, 0xe9, 0x00, 0x00, 0x05, 0xbe, 0xee, 0xee, 0xc6, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x07, 0xce, 0xee, 0xee, 0xb0, 0x00, 0x00, 0x00, 0x9e, 0xe9, 0x00, 0x00, 0x00, 0x0a, 0xee, 0xee, 0xec, 0x70, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x05, 0xae, 0xee, 0xee, 0xee, 0x90, 0x00, 0x00, 0x00, 0x9e, 0xe9, 0x00, 0x00, 0x00, 0x09, 0xee, 0xee, 0xee, 0xea, 0x50, 0x00, 0x00, 
  0x00, 0x00, 0x0b, 0xee, 0xee, 0x9d, 0xee, 0x70, 0x00, 0x00, 0x00, 0x9e, 0xe9, 0x00, 0x00, 0x00, 0x07, 0xee, 0xd9, 0xee, 0xee, 0xb0, 0x00, 0x00, 
  0x00, 0x00, 0x0b, 0xee, 0xb6, 0x5e, 0xee, 0x40, 0x00, 0x00, 0x00, 0x9e, 0xe9, 0x00, 0x00, 0x00, 0x04, 0xde, 0xe6, 0x6b, 0xee, 0xb0, 0x00, 0x00, 
  0x00, 0x00, 0x05, 0x87, 0x00, 0x7e, 0xec, 0x00, 0x00, 0x00, 0x00, 0xae, 0xea, 0x00, 0x00, 0x00, 0x00, 0xbe, 0xe7, 0x00, 0x78, 0x50, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x4d, 0xd8, 0x00, 0x00, 0x00, 0xfa, 0xee, 0xee, 0xa4, 0x00, 0x00, 0x00, 0x6c, 0xa4, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x0f, 0xae, 0xee, 0xee, 0xeb, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1a, 0xee, 0xee, 0xee, 0xee, 0xb4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0xee, 0xde, 0xed, 0xee, 0xe9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0xea, 0x9e, 0xe9, 0x9e, 0xe9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x81, 0x9e, 0xe9, 0x08, 0x83, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9e, 0xe9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9e, 0xe9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8e, 0xe8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

const lv_img_dsc_t img_mode_cooling = {
  .header.cf = LV_IMG_CF_INDEXED_4BIT,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = 48,
  .header.h = 48,
  .data_size = 1216,
  .data = img_mode_cooling_map,
};
