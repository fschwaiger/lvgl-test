#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>
#include "lvgl/lvgl.h"
#include "panels/rpms.h"

int main(void)
{
    lv_init();

    lv_display_t *disp = lv_sdl_window_create(480, 320);
    lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex3(0x000), LV_PART_MAIN);
    lv_obj_set_flex_flow(lv_screen_active(), LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(lv_screen_active(), LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    rpms_x6_subject_t rpm_subjects;
    for (int i = 0; i < 6; i++)
    {
        lv_subject_init_float(&rpm_subjects.rpms[i], 1300.0f);
    }

    av_create_rpms_panel(lv_scr_act(), &rpm_subjects);

    static int t = 0;
    while (1)
    {
        t++;
        if (t % 100 == 0)
        {
            // sine wave on the rpm from 400 to 1800
            float rpm_value = 1100.0f + 700.0f * sinf(t * 0.0001f);
            for (int i = 0; i < 6; i++)
            {
                lv_subject_set_float(&rpm_subjects.rpms[i], rpm_value);
            }
        }

        uint32_t sleep_time_ms = lv_timer_handler();
        usleep(sleep_time_ms);
    }

    return 0;
}