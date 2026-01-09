#pragma once
#include "lvgl/lvgl.h"

typedef struct rpms_x6_subject_s
{
    lv_subject_t rpms[6];
} rpms_x6_subject_t;

void av_create_rpms_panel(lv_obj_t *parent, rpms_x6_subject_t *subject);