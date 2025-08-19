/**
 * @file lv_conf.h
 * Configuration file for v9.3.0 - Based on manufacturer settings, adapted for v9
 */

/* clang-format off */
#if 1 /* Set this to "1" to enable content */

#ifndef LV_CONF_H
#define LV_CONF_H

/*====================
   COLOR SETTINGS
 *====================*/

/** Color depth: 1 (I1), 8 (L8), 16 (RGB565), 24 (RGB888), 32 (XRGB8888) */
#define LV_COLOR_DEPTH 16

/*=========================
   STDLIB WRAPPER SETTINGS
 *=========================*/

/** In LVGL v9, this replaces LV_MEM_CUSTOM from v8 */
#define LV_USE_STDLIB_MALLOC    LV_STDLIB_BUILTIN
#define LV_USE_STDLIB_STRING    LV_STDLIB_BUILTIN
#define LV_USE_STDLIB_SPRINTF   LV_STDLIB_BUILTIN

#define LV_STDINT_INCLUDE       <stdint.h>
#define LV_STDDEF_INCLUDE       <stddef.h>
#define LV_STDBOOL_INCLUDE      <stdbool.h>
#define LV_INTTYPES_INCLUDE     <inttypes.h>
#define LV_LIMITS_INCLUDE       <limits.h>
#define LV_STDARG_INCLUDE       <stdarg.h>

#if LV_USE_STDLIB_MALLOC == LV_STDLIB_BUILTIN
    /** Size of memory available for `lv_malloc()` in bytes (>= 2kB) */
    #define LV_MEM_SIZE (48U * 1024U)          /**< [bytes] - Same as manufacturer setting */

    /** Size of the memory expand for `lv_malloc()` in bytes */
    #define LV_MEM_POOL_EXPAND_SIZE 0

    /** Set an address for the memory pool instead of allocating it as a normal array. Can be in external SRAM too. */
    #define LV_MEM_ADR 0     /**< 0: unused*/
    /* Instead of an address give a memory allocator that will be called to get a memory pool for LVGL. E.g. my_malloc */
    #if LV_MEM_ADR == 0
        #undef LV_MEM_POOL_INCLUDE
        #undef LV_MEM_POOL_ALLOC
    #endif
#endif  /*LV_USE_STDLIB_MALLOC == LV_STDLIB_BUILTIN*/

/*====================
   HAL SETTINGS
 *====================*/

/** Default display refresh, input device read and animation step period. */
#define LV_DEF_REFR_PERIOD  33      /**< [ms] */

/** Default Dots Per Inch. Used to initialize default sizes such as widgets sized, style paddings.
 * (Not so important, you can adjust it to modify default sizes and spaces.) */
#define LV_DPI_DEF 130              /**< [px/inch] */

/*=================
 * OPERATING SYSTEM
 *=================*/
#define LV_USE_OS   LV_OS_NONE

/*========================
 * RENDERING CONFIGURATION
 *========================*/

/** Align stride of all layers and images to this bytes */
#define LV_DRAW_BUF_STRIDE_ALIGN                1

/** Align start address of draw_buf addresses to this bytes*/
#define LV_DRAW_BUF_ALIGN                       4

/** Using matrix for transformations. */
#define LV_DRAW_TRANSFORM_USE_MATRIX            0

/** The target buffer size for simple layer chunks. */
#define LV_DRAW_LAYER_SIMPLE_BUF_SIZE    (24 * 1024)    /**< [bytes]*/

#define LV_USE_DRAW_SW 1
#if LV_USE_DRAW_SW == 1
    /** Set number of draw units. */
    #define LV_DRAW_SW_DRAW_UNIT_CNT    1

    /** Use complex renderer */
    #define LV_DRAW_SW_COMPLEX          1

    #if LV_DRAW_SW_COMPLEX == 1
        /** Shadow cache size */
        #define LV_DRAW_SW_SHADOW_CACHE_SIZE 0

        /** Circle cache size */
        #define LV_DRAW_SW_CIRCLE_CACHE_SIZE 4
    #endif
#endif

/*=======================
 * FEATURE CONFIGURATION
 *=======================*/

/*-------------
 * Logging
 *-----------*/

/** Enable log module */
#define LV_USE_LOG 0

/*-------------
 * Asserts
 *-----------*/

#define LV_USE_ASSERT_NULL          1   /**< Check if the parameter is NULL. */
#define LV_USE_ASSERT_MALLOC        1   /**< Checks is the memory is successfully allocated. */
#define LV_USE_ASSERT_STYLE         0   /**< Check if the styles are properly initialized. */
#define LV_USE_ASSERT_MEM_INTEGRITY 0   /**< Check the integrity of `lv_mem` after critical operations. */
#define LV_USE_ASSERT_OBJ           0   /**< Check the object's type and existence. */

/** Add a custom handler when assert happens */
#define LV_ASSERT_HANDLER_INCLUDE <stdint.h>
#define LV_ASSERT_HANDLER while(1);     /**< Halt by default */

/*-------------
 * Others
 *-----------*/

/** Default cache size in bytes. */
#define LV_CACHE_DEF_SIZE       0

/** Number of stops allowed per gradient. */
#define LV_GRADIENT_MAX_STOPS   2

/** Add 2 x 32-bit variables to each `lv_obj_t` to speed up getting style properties */
#define LV_OBJ_STYLE_CACHE      0

/** Add `id` field to `lv_obj_t` */
#define LV_USE_OBJ_ID           0

/** Use `float` as `lv_value_precise_t` */
#define LV_USE_FLOAT            0

/*==================
 *   FONT USAGE
 *===================*/

/* Montserrat fonts */
#define LV_FONT_MONTSERRAT_8  0
#define LV_FONT_MONTSERRAT_10 0
#define LV_FONT_MONTSERRAT_12 0
#define LV_FONT_MONTSERRAT_14 1
#define LV_FONT_MONTSERRAT_16 0
#define LV_FONT_MONTSERRAT_18 0
#define LV_FONT_MONTSERRAT_20 0
#define LV_FONT_MONTSERRAT_22 0
#define LV_FONT_MONTSERRAT_24 0
#define LV_FONT_MONTSERRAT_26 0
#define LV_FONT_MONTSERRAT_28 0
#define LV_FONT_MONTSERRAT_30 0
#define LV_FONT_MONTSERRAT_32 0
#define LV_FONT_MONTSERRAT_34 0
#define LV_FONT_MONTSERRAT_36 0
#define LV_FONT_MONTSERRAT_38 0
#define LV_FONT_MONTSERRAT_40 0
#define LV_FONT_MONTSERRAT_42 0
#define LV_FONT_MONTSERRAT_44 0
#define LV_FONT_MONTSERRAT_46 0
#define LV_FONT_MONTSERRAT_48 0

/** Always set a default font */
#define LV_FONT_DEFAULT &lv_font_montserrat_14

/** Enable handling large font and/or fonts with a lot of characters. */
#define LV_FONT_FMT_TXT_LARGE 0

/** Enable drawing placeholders when glyph dsc is not found. */
#define LV_USE_FONT_PLACEHOLDER 1

/*=================
 *  TEXT SETTINGS
 *=================*/

/**
 * Select a character encoding for strings.
 * - LV_TXT_ENC_UTF8
 * - LV_TXT_ENC_ASCII
 */
#define LV_TXT_ENC LV_TXT_ENC_UTF8

/** While rendering text strings, break (wrap) text on these chars. */
#define LV_TXT_BREAK_CHARS " ,.;:-_)]}"

/*The control character to use for signaling text recoloring*/
#define LV_TXT_COLOR_CMD "#"

/*==================
 * WIDGETS
 *================*/

/** Give default values at creation time. */
#define LV_WIDGETS_HAS_DEFAULT_VALUE  1

#define LV_USE_ANIMIMG    1
#define LV_USE_ARC        1
#define LV_USE_BAR        1
#define LV_USE_BUTTON        1
#define LV_USE_BUTTONMATRIX  1
#define LV_USE_CALENDAR   1
#define LV_USE_CANVAS     1
#define LV_USE_CHART      1
#define LV_USE_CHECKBOX   1
#define LV_USE_DROPDOWN   1   /**< Requires: lv_label */
#define LV_USE_IMAGE      1   /**< Requires: lv_label */
#define LV_USE_IMAGEBUTTON     1
#define LV_USE_KEYBOARD   1
#define LV_USE_LABEL      1
#define LV_USE_LED        1
#define LV_USE_LINE       1
#define LV_USE_LIST       1
#define LV_USE_MENU       1
#define LV_USE_MSGBOX     1
#define LV_USE_ROLLER     1   /**< Requires: lv_label */
#define LV_USE_SCALE      1
#define LV_USE_SLIDER     1   /**< Requires: lv_bar */
#define LV_USE_SPAN       1
#define LV_USE_SPINBOX    1
#define LV_USE_SPINNER    1
#define LV_USE_SWITCH     1
#define LV_USE_TABLE      1
#define LV_USE_TABVIEW    1
#define LV_USE_TEXTAREA   1   /**< Requires: lv_label */
#define LV_USE_TILEVIEW   1
#define LV_USE_WIN        1

/*==================
 * THEMES
 *==================*/

/** A simple, impressive and very complete theme */
#define LV_USE_THEME_DEFAULT 1
#if LV_USE_THEME_DEFAULT
    /** 0: Light mode; 1: Dark mode */
    #define LV_THEME_DEFAULT_DARK 0

    /** 1: Enable grow on press */
    #define LV_THEME_DEFAULT_GROW 1

    /** Default transition time in ms. */
    #define LV_THEME_DEFAULT_TRANSITION_TIME 80
#endif /*LV_USE_THEME_DEFAULT*/

/** A very simple theme that is a good starting point for a custom theme */
#define LV_USE_THEME_SIMPLE 1

/** A theme designed for monochrome displays */
#define LV_USE_THEME_MONO 1

/*==================
 * LAYOUTS
 *==================*/

/** A layout similar to Flexbox in CSS. */
#define LV_USE_FLEX 1

/** A layout similar to Grid in CSS. */
#define LV_USE_GRID 1

/*====================
 * 3RD PARTS LIBRARIES
 *====================*/

/** 1: Enable an observer pattern implementation */
#define LV_USE_OBSERVER 1

/*=====================
* BUILD OPTIONS
*======================*/

/** Enable examples to be built with the library. */
#define LV_BUILD_EXAMPLES 1

/*===================
 * DEMO USAGE
 ====================*/

/** Show some widgets. */
#define LV_USE_DEMO_WIDGETS 1

/** Demonstrate usage of encoder and keyboard. */
#define LV_USE_DEMO_KEYPAD_AND_ENCODER 0

/** Benchmark your system */
#define LV_USE_DEMO_BENCHMARK 0

/** Stress test for LVGL */
#define LV_USE_DEMO_STRESS 0

/** Music player demo */
#define LV_USE_DEMO_MUSIC 0

/*--END OF LV_CONF_H--*/

#endif /*LV_CONF_H*/

#endif /*End of "Content enable"*/
