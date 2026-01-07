#include "rpm.h"

lv_color_t WHITE = {.red = 255, .green = 255, .blue = 255};
lv_color_t AMBER = {.red = 255, .green = 221, .blue = 0};
lv_color_t RED = {.red = 255, .green = 0, .blue = 0};

void av_bind_color(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *arc = (lv_obj_t *)lv_observer_get_user_data(observer);
    float v = lv_subject_get_float(subject);
    lv_color_t c = (v > 1750) ? RED : (v > 1500) ? AMBER
                                                 : WHITE;
    lv_obj_set_style_arc_color(arc, c, LV_PART_INDICATOR);
}

void av_tick_create(lv_obj_t *parent, lv_coord_t x, lv_coord_t y, int angle, lv_color_t color)
{
    lv_point_precise_t points[2] = {{.x = 48, .y = 0}, {.x = 56, .y = 0}};
    lv_obj_t *tick = lv_line_create(parent);
    lv_line_set_points(tick, points, 2);
    lv_obj_set_style_line_width(tick, 2, 0);
    lv_obj_set_style_line_color(tick, color, 0);
    lv_obj_set_style_line_rounded(tick, false, 0);
    lv_obj_set_pos(tick, x + 58, y + 58);
    lv_obj_set_style_transform_rotation(tick, angle * 10, 0);
}

void av_define_rpm_widget(lv_obj_t *parent, lv_coord_t x, lv_coord_t y, lv_subject_t *pSubject)
{
    lv_obj_t *arc = lv_arc_create(parent);
    lv_obj_set_pos(arc, x + 10, y + 10);
    lv_obj_set_size(arc, 96, 96);
    lv_obj_set_style_arc_width(arc, 24, LV_PART_MAIN);
    lv_obj_set_style_arc_rounded(arc, false, LV_PART_MAIN);
    lv_obj_set_style_arc_width(arc, 12, LV_PART_INDICATOR);
    lv_obj_set_style_arc_rounded(arc, false, LV_PART_INDICATOR);
    lv_obj_set_style_arc_color(arc, lv_color_hex3(0x555), LV_PART_MAIN);
    lv_obj_set_style_arc_color(arc, lv_color_hex3(0xAAA), LV_PART_INDICATOR);
    lv_obj_set_style_opa(arc, LV_OPA_0, LV_PART_KNOB); // hide the knob
    lv_arc_set_bg_angles(arc, 135, 360);
    lv_arc_set_angles(arc, 135, 135);
    lv_arc_set_range(arc, 0, 1800);
    lv_arc_bind_value(arc, pSubject);
    lv_subject_add_observer(pSubject, av_bind_color, arc);

    lv_obj_t *label = lv_label_create(parent);
    lv_obj_set_pos(label, x + 64, y + 70);
    lv_obj_set_size(label, 40, 20);
    lv_obj_set_style_text_font(label, &Roboto, 0);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_RIGHT, 0);
    lv_obj_set_style_text_color(label, WHITE, 0);
    lv_label_bind_text(label, pSubject, "%.0f");

    av_tick_create(parent, x, y, 340, AMBER);
    av_tick_create(parent, x, y, 350, RED);
    for (int angle = 135; angle <= 360; angle += 45)
    {
        av_tick_create(parent, x, y, angle, WHITE);
    }
}
