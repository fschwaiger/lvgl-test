#include "panels/rpms.h"
#include "widgets/rpm.h"

void av_create_rpms_panel(lv_obj_t *parent, rpms_x6_subject_t *subject)
{
    // a box with 2px grey frame and 10px rounded corders, 2px margin, 4px padding, and 3x2 rpm widgets inside
    lv_obj_t *box = lv_obj_create(parent);
    lv_obj_set_size(box, 450, 308);
    lv_obj_set_style_radius(box, 10, 0);
    lv_obj_set_style_border_width(box, 2, 0);
    lv_obj_set_style_border_color(box, lv_color_hex3(0x888), 0);
    lv_obj_set_style_bg_color(box, lv_color_black(), 0);
    lv_obj_set_flex_flow(box, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_flex_align(box, LV_FLEX_ALIGN_SPACE_AROUND, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    for (int i = 0; i < 6; i++)
    {
        lv_subject_t *subj = subject->rpms + i;
        av_create_rpm_widget(box, subj);
    }
}