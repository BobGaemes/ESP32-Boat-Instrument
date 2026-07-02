#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

// Screens

enum ScreensEnum {
    _SCREEN_ID_FIRST = 1,
    SCREEN_ID_MAIN = 1,
    SCREEN_ID_HIGHLIGHTS = 2,
    _SCREEN_ID_LAST = 2
};

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *highlights;
    lv_obj_t *wind_direction_container;
    lv_obj_t *wind_direction_scale;
    lv_obj_t *boat_image;
    lv_obj_t *owa_line;
    lv_obj_t *awa_arrow;
    lv_obj_t *twa_arrow;
    lv_obj_t *heel_tilt_scale;
    lv_obj_t *heel_tilt_bar;
    lv_obj_t *rudder_rotation_scale;
    lv_obj_t *rudder_rotation_bar;
    lv_obj_t *aws_label;
    lv_obj_t *aws_value_label;
    lv_obj_t *aws_unit_label;
    lv_obj_t *boat_status_label;
    lv_obj_t *stw_label;
    lv_obj_t *stw_value_label;
    lv_obj_t *stw_unit_label;
    lv_obj_t *stw_line;
    lv_obj_t *sog_label;
    lv_obj_t *sog_value_label;
    lv_obj_t *sog_unit_label;
    lv_obj_t *sog_line;
    lv_obj_t *vmg_label;
    lv_obj_t *vmg_value_label;
    lv_obj_t *vmg_unit_label;
    lv_obj_t *vmg_line;
    lv_obj_t *polar_ratio_label;
    lv_obj_t *polar_ratio_value_label;
    lv_obj_t *polar_ratio_unit_label;
    lv_obj_t *polar_ratio_line;
    lv_obj_t *awa_label;
    lv_obj_t *awa_value_label;
    lv_obj_t *awa_unit_label;
    lv_obj_t *awa_line;
    lv_obj_t *twa_label;
    lv_obj_t *twa_value_label;
    lv_obj_t *twa_unit_label;
    lv_obj_t *twa_line;
    lv_obj_t *tws_label;
    lv_obj_t *tws_value_label;
    lv_obj_t *tws_unit_label;
    lv_obj_t *tws_line;
    lv_obj_t *cog_label;
    lv_obj_t *cog_value_label;
    lv_obj_t *cog_unit_label;
    lv_obj_t *cog_line;
    lv_obj_t *stw_label_1;
    lv_obj_t *stw_value_label_1;
    lv_obj_t *stw_unit_label_1;
    lv_obj_t *stw_line_1;
    lv_obj_t *sog_label_1;
    lv_obj_t *sog_value_label_1;
    lv_obj_t *sog_unit_label_1;
    lv_obj_t *sog_line_1;
    lv_obj_t *vmg_label_1;
    lv_obj_t *vmg_value_label_1;
    lv_obj_t *vmg_unit_label_1;
    lv_obj_t *vmg_line_1;
    lv_obj_t *polar_ratio_label_1;
    lv_obj_t *polar_ratio_value_label_1;
    lv_obj_t *polar_ratio_unit_label_1;
    lv_obj_t *polar_ratio_line_1;
    lv_obj_t *awa_label_1;
    lv_obj_t *awa_value_label_1;
    lv_obj_t *awa_line_1;
    lv_obj_t *twa_label_1;
    lv_obj_t *twa_value_label_1;
    lv_obj_t *twa_line_1;
    lv_obj_t *tws_label_1;
    lv_obj_t *tws_value_label_1;
    lv_obj_t *tws_unit_label_1;
    lv_obj_t *tws_line_1;
    lv_obj_t *cog_label_1;
    lv_obj_t *cog_value_label_1;
    lv_obj_t *cog_line_1;
    lv_obj_t *tws_unit_label_2;
    lv_obj_t *tws_unit_label_3;
    lv_obj_t *tws_unit_label_4;
} objects_t;

extern objects_t objects;

typedef struct {
    lv_scale_section_t *scale_section;
    lv_scale_section_t *scale_section1;
    lv_scale_section_t *scale_section2;
    lv_scale_section_t *scale_section3;
    lv_scale_section_t *scale_section4;
    lv_scale_section_t *scale_section5;
} screen_main_state_t;

extern screen_main_state_t screen_main_state;

void create_screen_main();
void tick_screen_main();

void create_screen_highlights();
void tick_screen_highlights();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();

// Global state variables

extern lv_style_t windDirectionScale_section_main_style;
extern lv_style_t windDirectionScale_section_items_style;
extern lv_style_t windDirectionScale_section_indicator_style;
extern lv_style_t windDirectionScale_section_main_style1;
extern lv_style_t windDirectionScale_section_items_style1;
extern lv_style_t windDirectionScale_section_indicator_style1;
extern lv_style_t windDirectionScale_section_main_style2;
extern lv_style_t windDirectionScale_section_items_style2;
extern lv_style_t windDirectionScale_section_indicator_style2;
extern lv_style_t heelTiltScale_section_main_style;
extern lv_style_t heelTiltScale_section_items_style;
extern lv_style_t heelTiltScale_section_indicator_style;
extern lv_style_t heelTiltScale_section_main_style1;
extern lv_style_t heelTiltScale_section_items_style1;
extern lv_style_t heelTiltScale_section_indicator_style1;
extern lv_style_t rudderRotationScale_section_main_style;

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/