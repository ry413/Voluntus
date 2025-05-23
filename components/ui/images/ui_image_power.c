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

#ifndef LV_ATTRIBUTE_IMG_IMG_POWER
#define LV_ATTRIBUTE_IMG_IMG_POWER
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_IMG_POWER uint8_t img_power_map[] = {
  0x00, 0x00, 0x00, 0x00, 	/*Color of index 0*/
  0x00, 0x00, 0xff, 0x02, 	/*Color of index 1*/
  0x00, 0x00, 0xff, 0x0e, 	/*Color of index 2*/
  0x00, 0x00, 0xff, 0x1b, 	/*Color of index 3*/
  0x00, 0x00, 0xff, 0x2e, 	/*Color of index 4*/
  0x00, 0x00, 0xff, 0x40, 	/*Color of index 5*/
  0x00, 0x00, 0xff, 0x54, 	/*Color of index 6*/
  0x00, 0x00, 0xff, 0x66, 	/*Color of index 7*/
  0x00, 0x00, 0xff, 0x79, 	/*Color of index 8*/
  0x00, 0x00, 0xff, 0x8d, 	/*Color of index 9*/
  0x00, 0x00, 0xff, 0xa0, 	/*Color of index 10*/
  0x00, 0x00, 0xff, 0xb4, 	/*Color of index 11*/
  0x00, 0x00, 0xff, 0xc5, 	/*Color of index 12*/
  0x00, 0x00, 0xff, 0xd7, 	/*Color of index 13*/
  0x00, 0x00, 0xff, 0xe7, 	/*Color of index 14*/
  0x00, 0x00, 0xff, 0xfc, 	/*Color of index 15*/

  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x31, 0x00, 0x1c, 0xfb, 0x00, 0x00, 0x31, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x6a, 0xb3, 0x00, 0x1c, 0xfb, 0x00, 0x01, 0xe9, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x39, 0xce, 0xe3, 0x00, 0x1c, 0xfb, 0x00, 0x01, 0xfd, 0xb7, 0x31, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x34, 0x8f, 0xfd, 0xb2, 0x00, 0x1c, 0xfb, 0x00, 0x01, 0xde, 0xfd, 0x84, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x68, 0xff, 0xd8, 0x21, 0x00, 0x1c, 0xfb, 0x00, 0x00, 0x3a, 0xef, 0xf9, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0xbc, 0xfb, 0x74, 0x11, 0x00, 0x1c, 0xfb, 0x00, 0x00, 0x15, 0x8c, 0xfd, 0x63, 0x10, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x01, 0x0a, 0xef, 0xd5, 0x30, 0x00, 0x00, 0x1c, 0xfb, 0x00, 0x00, 0x00, 0x38, 0xdf, 0xb7, 0x21, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x02, 0x3f, 0xfe, 0x60, 0x00, 0x00, 0x00, 0x1c, 0xfb, 0x00, 0x00, 0x00, 0x03, 0x7e, 0xfd, 0x42, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x05, 0x9f, 0xca, 0x00, 0x00, 0x00, 0x00, 0x1c, 0xfb, 0x00, 0x00, 0x00, 0x01, 0x29, 0xee, 0xa4, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x27, 0xef, 0x75, 0x00, 0x00, 0x00, 0x00, 0x1c, 0xfb, 0x00, 0x00, 0x00, 0x00, 0x14, 0xcf, 0xf5, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x59, 0xfc, 0x41, 0x00, 0x00, 0x00, 0x00, 0x1c, 0xfb, 0x00, 0x00, 0x00, 0x00, 0x10, 0x9e, 0xf8, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x9b, 0xf8, 0x30, 0x00, 0x00, 0x00, 0x00, 0x1c, 0xfb, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7b, 0xfb, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xbd, 0xf5, 0x20, 0x00, 0x00, 0x00, 0x00, 0x1c, 0xfb, 0x00, 0x00, 0x00, 0x00, 0x00, 0x58, 0xfd, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xce, 0xf3, 0x20, 0x00, 0x00, 0x00, 0x00, 0x1c, 0xfb, 0x00, 0x00, 0x00, 0x00, 0x00, 0x47, 0xfe, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xef, 0xf0, 0x10, 0x00, 0x00, 0x00, 0x00, 0x1c, 0xfb, 0x00, 0x00, 0x00, 0x00, 0x00, 0x25, 0xff, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xff, 0xf0, 0x10, 0x00, 0x00, 0x00, 0x00, 0x1b, 0xeb, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14, 0xff, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xef, 0xf0, 0x10, 0x00, 0x00, 0x00, 0x00, 0x02, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0xff, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xee, 0xf1, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x26, 0xef, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xce, 0xf3, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x47, 0xfe, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xac, 0xf6, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x59, 0xfc, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x7b, 0xf9, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8c, 0xfa, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x59, 0xfc, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x9e, 0xf8, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x27, 0xef, 0x75, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14, 0xcf, 0xe6, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x05, 0x9f, 0xca, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x2a, 0xee, 0xa4, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x02, 0x3f, 0xfe, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x8d, 0xfd, 0x42, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x01, 0x0a, 0xef, 0xd5, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0xdf, 0xb7, 0x21, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0xbd, 0xfb, 0x74, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x15, 0x8d, 0xfd, 0x63, 0x10, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x57, 0xef, 0xe9, 0x43, 0x22, 0x11, 0x11, 0x12, 0x23, 0x5b, 0xef, 0xd8, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x6f, 0xff, 0xeb, 0x75, 0x31, 0x01, 0x36, 0x9a, 0xff, 0xfc, 0x52, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x39, 0xbe, 0xfe, 0xba, 0x99, 0x89, 0x9b, 0xdd, 0xfd, 0xb7, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x59, 0xde, 0xff, 0xff, 0xff, 0xff, 0xee, 0xd8, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x36, 0xab, 0xde, 0xee, 0xda, 0x87, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

const lv_img_dsc_t img_power = {
  .header.cf = LV_IMG_CF_INDEXED_4BIT,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = 48,
  .header.h = 48,
  .data_size = 1216,
  .data = img_power_map,
};
