#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "lvgl/lvgl.h"

uint32_t av_tick_get(void);
void av_flush_cb(lv_display_t *disp, const lv_area_t *area, uint8_t *px_buf);

int main(void)
{
    lv_init();

    lv_group_set_default(lv_group_create());

    lv_display_t *disp = lv_sdl_window_create(256, 256);

    /* Create a simple label */
    lv_obj_t *label = lv_label_create(lv_screen_active());
    lv_label_set_text(label, "Hello LVGL!");
    lv_obj_center(label);

    /* Main loop */
    while (1)
    {
        uint32_t sleep_time_ms = lv_timer_handler();
        usleep(sleep_time_ms * 1000);
    }

    return 0;
}