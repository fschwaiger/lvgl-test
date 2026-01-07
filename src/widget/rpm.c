#include "rpm.h"

void av_bind_color(lv_observer_t *observer, lv_subject_t *subject)
{
    // if above 1500 rpm, set arc color to red, else to white
    lv_obj_t *arc = (lv_obj_t *)lv_observer_get_user_data(observer);
    float rpm_value = lv_subject_get_float(subject);
    if (rpm_value > 1750.0f)
    {
        lv_obj_set_style_arc_color(arc, lv_color_hex3(0xF00), LV_PART_INDICATOR);
    }
    else if (rpm_value > 1500.0f)
    {
        lv_obj_set_style_arc_color(arc, lv_color_hex3(0xFD0), LV_PART_INDICATOR);
    }
    else
    {
        lv_obj_set_style_arc_color(arc, lv_color_hex3(0xAAA), LV_PART_INDICATOR);
    }
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

    // and a label bottom right
    lv_obj_t *label = lv_label_create(parent);
    lv_obj_set_pos(label, x + 50, y + 70);
    lv_label_bind_text(label, pSubject, "%.0f");

    lv_point_precise_t points[2] = {{.x = 48, .y = 0}, {.x = 56, .y = 0}};
    lv_obj_t *tick;
    for (int angle = 135; angle <= 360; angle += 45)
    {
        tick = lv_line_create(parent);
        lv_line_set_points(tick, points, 2);
        lv_obj_set_style_line_width(tick, 2, 0);
        lv_obj_set_style_line_color(tick, lv_color_white(), 0);
        lv_obj_set_style_line_rounded(tick, false, 0);
        lv_obj_set_pos(tick, x + 58, y + 58);
        lv_obj_set_style_transform_rotation(tick, angle * 10, 0);
    }

    tick = lv_line_create(parent);
    lv_line_set_points(tick, points, 2);
    lv_obj_set_style_line_width(tick, 2, 0);
    lv_obj_set_style_line_color(tick, lv_color_hex3(0xFF0), 0);
    lv_obj_set_style_line_rounded(tick, false, 0);
    lv_obj_set_pos(tick, x + 58, y + 58);
    lv_obj_set_style_transform_rotation(tick, 340 * 10, 0);

    tick = lv_line_create(parent);
    lv_line_set_points(tick, points, 2);
    lv_obj_set_style_line_width(tick, 2, 0);
    lv_obj_set_style_line_color(tick, lv_color_hex3(0xF00), 0);
    lv_obj_set_style_line_rounded(tick, false, 0);
    lv_obj_set_pos(tick, x + 58, y + 58);
    lv_obj_set_style_transform_rotation(tick, 350 * 10, 0);
}
