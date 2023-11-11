#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>

#include <lvgl.h>

#include "util.h"

extern SemaphoreHandle_t lvgl_semaphore;

////

// static lv_obj_t *meter;
// static lv_meter_indicator_t *indic;

lv_obj_t * bar{};

////

static void ui(void*)
{
    message("start ui loop");
    extern volatile uint16_t adc_value;
    for (;;)
    {
        // int v = ((float) adc_value / 0xff) * 100;
        xSemaphoreTake(lvgl_semaphore, portMAX_DELAY);
        // lv_meter_set_indicator_value(meter, indic, adc_value);
        lv_bar_set_value(bar, adc_value, LV_ANIM_OFF);
        xSemaphoreGive(lvgl_semaphore);
        vTaskDelay(10);
    }
}

void ui_init()
{
    // meter = lv_meter_create(lv_scr_act());
    // lv_obj_center(meter);
    // lv_obj_set_size(meter, 320, 320); 

    // lv_meter_scale_t * scale = lv_meter_add_scale(meter);
    // lv_meter_set_scale_ticks(meter, scale, 41, 2, 10, lv_palette_main(LV_PALETTE_GREY));
    // lv_meter_set_scale_major_ticks(meter, scale, 8, 4, 15, lv_color_black(), 10);
    // lv_meter_set_scale_range(meter, scale, 0, 255, 275, 0);

    // /*Add a blue arc to the start*/
    // indic = lv_meter_add_arc(meter, scale, 3, lv_palette_main(LV_PALETTE_BLUE), 0);
    // lv_meter_set_indicator_start_value(meter, indic, 0);
    // lv_meter_set_indicator_end_value(meter, indic, 20);

    // /*Make the tick lines blue at the start of the scale*/
    // indic = lv_meter_add_scale_lines(meter, scale, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_BLUE),
    //                                  false, 0);
    // lv_meter_set_indicator_start_value(meter, indic, 0);
    // lv_meter_set_indicator_end_value(meter, indic, 20);

    // /*Add a red arc to the end*/
    // indic = lv_meter_add_arc(meter, scale, 3, lv_palette_main(LV_PALETTE_RED), 0);
    // lv_meter_set_indicator_start_value(meter, indic, 80);
    // lv_meter_set_indicator_end_value(meter, indic, 100);

    // /*Make the tick lines red at the end of the scale*/
    // indic = lv_meter_add_scale_lines(meter, scale, lv_palette_main(LV_PALETTE_RED), lv_palette_main(LV_PALETTE_RED), false,
    //                                  0);
    // lv_meter_set_indicator_start_value(meter, indic, 80);
    // lv_meter_set_indicator_end_value(meter, indic, 100);

    // /*Add a needle line indicator*/
    // indic = lv_meter_add_needle_line(meter, scale, 4, lv_palette_main(LV_PALETTE_GREY), -10);

    // auto *s = lv_spinner_create(lv_scr_act(), 2500, 45);
    // lv_obj_set_size(s, 320, 320);
    // lv_obj_center(s);

    bar = lv_bar_create(lv_scr_act());
    lv_bar_set_range(bar, 0, 255);
    lv_obj_set_size(bar, 200, 20);
    lv_obj_center(bar);

    xSemaphoreGive(lvgl_semaphore);

    xTaskCreate(ui, "ui", 256, NULL, tskIDLE_PRIORITY + 2, NULL);
}
