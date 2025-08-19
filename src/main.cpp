/* LVGL + Arduino + FT3168 Touch integration
 * Optimized: one circle + crosshair lines follow the touch point
 */

 #include <Arduino.h>
 #include <lvgl.h>
 #include <Wire.h>
 #include <Arduino_GFX_Library.h>
 
 /*******************************************************************************
  * Arduino_GFX setting for Waveshare ESP32-S3-Touch-AMOLED-1.64
  ******************************************************************************/
 #define GFX_DEV_DEVICE WAVESHARE_ESP32_S3_TOUCH_AMOLED_1_64
 Arduino_DataBus *bus = new Arduino_ESP32QSPI(
     9 /* CS */, 10 /* SCK */, 11 /* D0 */, 12 /* D1 */, 13 /* D2 */, 14 /* D3 */);
 Arduino_GFX *g = new Arduino_CO5300(
     bus, 21 /* RST */, 0 /* rotation */, 280 /* width */, 456 /* height */,
     20 /* col offset 1 */, 0 /* row offset 1 */, 180 /* col_offset2 */, 24 /* row_offset2 */);
 Arduino_Canvas *gfx = new Arduino_Canvas(
     280 /* width */, 456 /* height */, g, 0, 0, 0);
 
 /*******************************************************************************
  * FT3168 Touch driver (minimal, single finger)
  ******************************************************************************/
 #define FT3168_ADDR 0x38
 #define FT3168_REG_NUM_TOUCHES 0x02
 
 static uint16_t touch_last_x = 0;
 static uint16_t touch_last_y = 0;
 static bool touch_pressed = false;
 
 static void ft3168_init()
 {
   Wire.begin(47, 48); // SDA, SCL pins
   Wire.setClock(300000);
 }
 
 static void ft3168_poll()
 {
   uint8_t buf[5] = {0};
 
   Wire.beginTransmission(FT3168_ADDR);
   Wire.write(FT3168_REG_NUM_TOUCHES);
   Wire.endTransmission(false);
   if (Wire.requestFrom(FT3168_ADDR, 5) == 5)
   {
     for (int i = 0; i < 5; i++)
       buf[i] = Wire.read();
 
     uint8_t touches = buf[0] & 0x0F;
     if (touches > 0)
     {
       uint16_t x = ((buf[1] & 0x0F) << 8) | buf[2];
       uint16_t y = ((buf[3] & 0x0F) << 8) | buf[4];
       touch_last_x = x;
       touch_last_y = y;
       touch_pressed = true;
     }
     else
     {
       touch_pressed = false;
     }
   }
   else
   {
     touch_pressed = false;
   }
 }
 
 /*******************************************************************************
  * LVGL objects for visualization
  ******************************************************************************/
 static lv_obj_t *circle;
 static lv_obj_t *hline;
 static lv_obj_t *vline;
 
 static void create_touch_markers(lv_obj_t *parent)
 {
   // Circle
   circle = lv_obj_create(parent);
   lv_obj_set_size(circle, 20, 20);
   lv_obj_set_style_radius(circle, LV_RADIUS_CIRCLE, 0);
   lv_obj_set_style_bg_color(circle, lv_color_hex(0xFF0000), 0);
   lv_obj_set_style_border_opa(circle, LV_OPA_TRANSP, 0);
   lv_obj_add_flag(circle, LV_OBJ_FLAG_HIDDEN);
 
   // Horizontal line
   hline = lv_obj_create(parent);
   lv_obj_set_size(hline, lv_display_get_horizontal_resolution(lv_display_get_default()), 2);
   lv_obj_set_style_bg_color(hline, lv_color_hex(0x00FF00), 0);
   lv_obj_set_style_border_opa(hline, LV_OPA_TRANSP, 0);
   lv_obj_add_flag(hline, LV_OBJ_FLAG_HIDDEN);
 
   // Vertical line
   vline = lv_obj_create(parent);
   lv_obj_set_size(vline, 2, lv_display_get_vertical_resolution(lv_display_get_default()));
   lv_obj_set_style_bg_color(vline, lv_color_hex(0x00FF00), 0);
   lv_obj_set_style_border_opa(vline, LV_OPA_TRANSP, 0);
   lv_obj_add_flag(vline, LV_OBJ_FLAG_HIDDEN);
 }
 
 /*Read the touchpad for LVGL*/
 void my_touchpad_read(lv_indev_t *indev, lv_indev_data_t *data)
 {
   ft3168_poll();
 
   if (touch_pressed)
   {
     data->state = LV_INDEV_STATE_PRESSED;
     data->point.x = touch_last_x;
     data->point.y = touch_last_y;
 
     // Move markers
     lv_obj_clear_flag(circle, LV_OBJ_FLAG_HIDDEN);
     lv_obj_set_pos(circle, touch_last_x - 10, touch_last_y - 10);
 
     lv_obj_clear_flag(hline, LV_OBJ_FLAG_HIDDEN);
     lv_obj_set_y(hline, touch_last_y - 1);
 
     lv_obj_clear_flag(vline, LV_OBJ_FLAG_HIDDEN);
     lv_obj_set_x(vline, touch_last_x - 1);
   }
   else
   {
     data->state = LV_INDEV_STATE_RELEASED;
 
     // Hide markers
     lv_obj_add_flag(circle, LV_OBJ_FLAG_HIDDEN);
     lv_obj_add_flag(hline, LV_OBJ_FLAG_HIDDEN);
     lv_obj_add_flag(vline, LV_OBJ_FLAG_HIDDEN);
   }
 }
 
 /*******************************************************************************
  * LVGL glue
  ******************************************************************************/
 
 uint32_t screenWidth;
 uint32_t screenHeight;
 uint32_t bufSize;
 lv_display_t *disp;
 lv_color_t *disp_draw_buf;
 
 uint32_t millis_cb(void) { return millis(); }
 
 void my_disp_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map)
 {
   uint32_t w = lv_area_get_width(area);
   uint32_t h = lv_area_get_height(area);
 
   gfx->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t *)px_map, w, h);
 
   lv_disp_flush_ready(disp);
 }
 
 void setup()
 {
   Serial.begin(115200);
   Serial.println("Arduino_GFX + LVGL + FT3168 example (optimized)");
 
   // Init Display
   if (!gfx->begin())
   {
     Serial.println("gfx->begin() failed!");
   }
   gfx->fillScreen(RGB565_BLACK);
 
   // Init LVGL
   lv_init();
   lv_tick_set_cb(millis_cb);
 
   screenWidth = gfx->width();
   screenHeight = gfx->height();
   bufSize = screenWidth * 40;
   disp_draw_buf = (lv_color_t *)heap_caps_malloc(bufSize * 2, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
   if (!disp_draw_buf)
     disp_draw_buf = (lv_color_t *)heap_caps_malloc(bufSize * 2, MALLOC_CAP_8BIT);
   
   disp = lv_display_create(screenWidth, screenHeight);
   lv_display_set_flush_cb(disp, my_disp_flush);
   lv_display_set_buffers(disp, disp_draw_buf, NULL, bufSize * 2, LV_DISPLAY_RENDER_MODE_PARTIAL);
 
   // Init touch
   ft3168_init();
   lv_indev_t *indev = lv_indev_create();
   lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
   lv_indev_set_read_cb(indev, my_touchpad_read);
 
   // UI
   lv_obj_t *label = lv_label_create(lv_scr_act());
   lv_label_set_text(label, "Touch to see circle + crosshair");
   lv_obj_center(label);
 
   // Create markers
   create_touch_markers(lv_scr_act());
 
   Serial.println("Setup done");
 }
 
 void loop()
 {
   lv_task_handler();
   gfx->flush();
   delay(5);
 }