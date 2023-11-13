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

void backlight(bool on);

static void cb_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    if(code == LV_EVENT_VALUE_CHANGED) {
        backlight(lv_obj_get_state(obj) & LV_STATE_CHECKED);
    }
}

static void ui(void*)
{
    message("start ui loop");
    extern volatile uint16_t adc_value;
    for (;;)
    {
        // int v = ((float) adc_value / 0xff) * 100;
        xSemaphoreTake(lvgl_semaphore, portMAX_DELAY);
        // lv_meter_set_indicator_value(meter, indic, adc_value);
        // lv_bar_set_value(bar, adc_value, LV_ANIM_OFF);
        xSemaphoreGive(lvgl_semaphore);
        vTaskDelay(10);
    }
}

void ui_init()
{
    lv_obj_set_flex_flow(lv_scr_act(), LV_FLEX_FLOW_COLUMN);

    auto *cb = lv_checkbox_create(lv_scr_act());
    lv_checkbox_set_text(cb, "hehe?");
    cb = lv_checkbox_create(lv_scr_act());
    lv_checkbox_set_text(cb, "not hehe?");

    cb = lv_checkbox_create(lv_scr_act());
    lv_obj_add_state(cb, LV_STATE_CHECKED);
    lv_obj_add_event_cb(cb, cb_handler, LV_EVENT_ALL, NULL);
    lv_checkbox_set_text(cb, "backlight on?");

    auto *s =  lv_slider_create(lv_scr_act());
    lv_slider_set_range(s, 0, 100);

    xSemaphoreGive(lvgl_semaphore);

    xTaskCreate(ui, "ui", 256, NULL, tskIDLE_PRIORITY + 2, NULL);
}
