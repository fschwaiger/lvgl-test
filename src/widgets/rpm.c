#include "widgets/rpm.h"

static lv_color_t WHITE = {.red = 255, .green = 255, .blue = 255};
static lv_color_t AMBER = {.red = 255, .green = 221, .blue = 0};
static lv_color_t RED = {.red = 255, .green = 0, .blue = 0};
static lv_point_precise_t POINTS[2] = {{.x = 48, .y = 0}, {.x = 56, .y = 0}};

static lv_obj_t *av_create_group(lv_obj_t *parent)
{
    lv_obj_t *group = lv_obj_create(parent);
    lv_obj_set_style_border_width(group, 0, 0);
    lv_obj_set_style_bg_opa(group, LV_OPA_TRANSP, 0);
    lv_obj_set_scrollbar_mode(group, LV_SCROLLBAR_MODE_OFF);
    return group;
}

static void av_bind_color(lv_observer_t *observer, lv_subject_t *subject)
{
    lv_obj_t *arc = (lv_obj_t *)lv_observer_get_user_data(observer);
    float v = lv_subject_get_float(subject);
    lv_color_t c = (v > 1750) ? RED : (v > 1500) ? AMBER
                                                 : WHITE;
    lv_obj_set_style_arc_color(arc, c, LV_PART_INDICATOR);
}

static void av_create_arc_dial(lv_obj_t *parent, lv_subject_t *pSubject)
{
    lv_obj_t *arc = lv_arc_create(parent);
    lv_obj_set_size(arc, 96, 96);
    lv_obj_set_style_arc_width(arc, 30, LV_PART_MAIN);
    lv_obj_set_style_arc_rounded(arc, false, LV_PART_MAIN);
    lv_obj_set_style_arc_width(arc, 16, LV_PART_INDICATOR);
    lv_obj_set_style_arc_rounded(arc, false, LV_PART_INDICATOR);
    lv_obj_set_style_arc_color(arc, lv_color_hex3(0x555), LV_PART_MAIN);
    lv_obj_set_style_arc_color(arc, lv_color_hex3(0xAAA), LV_PART_INDICATOR);
    lv_obj_set_style_opa(arc, LV_OPA_0, LV_PART_KNOB); // hide the knob
    lv_arc_set_bg_angles(arc, 135, 360);
    lv_arc_set_angles(arc, 135, 135);
    lv_arc_set_range(arc, 0, 1800);
    lv_arc_bind_value(arc, pSubject);
    lv_subject_add_observer(pSubject, av_bind_color, arc);
}

static void av_create_label(lv_obj_t *parent, lv_subject_t *pSubject)
{
    lv_obj_t *label = lv_label_create(parent);
    lv_obj_set_pos(label, 56, 70);
    lv_obj_set_size(label, 40, 20);
    lv_obj_set_style_text_font(label, &Roboto, 0);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_RIGHT, 0);
    lv_obj_set_style_text_color(label, WHITE, 0);
    lv_label_bind_text(label, pSubject, "%.0f");
}

static void av_create_tick(lv_obj_t *parent, int angle, lv_color_t color)
{
    lv_obj_t *tick = lv_line_create(parent);
    lv_line_set_points(tick, POINTS, 2);
    lv_obj_set_style_line_width(tick, 2, 0);
    lv_obj_set_style_line_color(tick, color, 0);
    lv_obj_set_style_line_rounded(tick, false, 0);
    lv_obj_set_pos(tick, 48, 48);
    lv_obj_set_style_transform_rotation(tick, angle * 10, 0);
}

void av_create_rpm_widget(lv_obj_t *parent, lv_subject_t *pSubject)
{
    lv_obj_t *group = av_create_group(parent);
    av_create_arc_dial(group, pSubject);
    av_create_label(group, pSubject);
    av_create_tick(group, 340, AMBER);
    av_create_tick(group, 350, RED);
    for (int angle = 135; angle <= 360; angle += 45)
    {
        av_create_tick(group, angle, WHITE);
    }
}
