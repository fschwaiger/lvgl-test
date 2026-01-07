#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>
#include "lvgl/lvgl.h"
#include "widget/rpm.h"

int main(void)
{
    lv_init();

    lv_display_t *disp = lv_sdl_window_create(256, 256);

    lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex3(0x000), LV_PART_MAIN);

    lv_subject_t rpm_subject;
    lv_subject_init_float(&rpm_subject, 1300.0f);

    av_define_rpm_widget(lv_scr_act(), 10, 10, &rpm_subject);
    av_define_rpm_widget(lv_scr_act(), 10, 110, &rpm_subject);

    static int t = 0;
    while (1)
    {
        t++;
        if (t % 100 == 0)
        {
            // sine wave on the rpm from 400 to 1800
            float rpm_value = 1100.0f + 700.0f * sinf(t * 0.0001f);
            lv_subject_set_float(&rpm_subject, rpm_value);
        }

        uint32_t sleep_time_ms = lv_timer_handler();
        usleep(sleep_time_ms);
    }

    return 0;
}