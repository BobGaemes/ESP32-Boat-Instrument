#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "vars.h"
#include "ui.h"

#include <stdio.h>

#include <string.h>

objects_t objects;

screen_main_state_t screen_main_state;

// Global state variables

lv_style_t windDirectionScale_section_main_style;
static bool windDirectionScale_section_main_style_initialized;
lv_style_t windDirectionScale_section_items_style;
static bool windDirectionScale_section_items_style_initialized;
lv_style_t windDirectionScale_section_indicator_style;
static bool windDirectionScale_section_indicator_style_initialized;
lv_style_t windDirectionScale_section_main_style1;
static bool windDirectionScale_section_main_style1_initialized;
lv_style_t windDirectionScale_section_items_style1;
static bool windDirectionScale_section_items_style1_initialized;
lv_style_t windDirectionScale_section_indicator_style1;
static bool windDirectionScale_section_indicator_style1_initialized;
lv_style_t windDirectionScale_section_main_style2;
static bool windDirectionScale_section_main_style2_initialized;
lv_style_t windDirectionScale_section_items_style2;
static bool windDirectionScale_section_items_style2_initialized;
lv_style_t windDirectionScale_section_indicator_style2;
static bool windDirectionScale_section_indicator_style2_initialized;
lv_style_t heelTiltScale_section_main_style;
static bool heelTiltScale_section_main_style_initialized;
lv_style_t heelTiltScale_section_items_style;
static bool heelTiltScale_section_items_style_initialized;
lv_style_t heelTiltScale_section_indicator_style;
static bool heelTiltScale_section_indicator_style_initialized;
lv_style_t heelTiltScale_section_main_style1;
static bool heelTiltScale_section_main_style1_initialized;
lv_style_t heelTiltScale_section_items_style1;
static bool heelTiltScale_section_items_style1_initialized;
lv_style_t heelTiltScale_section_indicator_style1;
static bool heelTiltScale_section_indicator_style1_initialized;
lv_style_t rudderRotationScale_section_main_style;
static bool rudderRotationScale_section_main_style_initialized;

//
// Event handlers
//

lv_obj_t *tick_value_change_obj;

//
// Screens
//

void create_screen_main() {
    screen_main_state_t *state = &screen_main_state;
    (void)state;
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 1024, 600);
    {
        lv_obj_t *parent_obj = obj;
        {
            // windDirectionContainer
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.wind_direction_container = obj;
            lv_obj_set_pos(obj, 302, 80);
            lv_obj_set_size(obj, 420, 440);
            lv_obj_set_style_pad_left(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_right(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_bottom(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff212529), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 220, LV_PART_MAIN | LV_STATE_DEFAULT);
            // lv_obj_set_style_shadow_width(obj, 100, LV_PART_MAIN | LV_STATE_DEFAULT); // CAUSES HOGGING OF CPU
        }
        {
            // windDirectionScale
            lv_obj_t *obj = lv_scale_create(parent_obj);
            objects.wind_direction_scale = obj;
            lv_obj_set_pos(obj, 322, 100);
            lv_obj_set_size(obj, 380, 400);
            lv_scale_set_mode(obj, LV_SCALE_MODE_ROUND_INNER);
            lv_scale_set_range(obj, -180, 180);
            lv_scale_set_angle_range(obj, 360);
            lv_scale_set_rotation(obj, 90);
            lv_scale_set_total_tick_count(obj, 37);
            lv_scale_set_major_tick_every(obj, 3);
            lv_scale_set_label_show(obj, true);
            static const char *label_texts[13] = {
                "180",
                "-150",
                "-120",
                "-90",
                "-60",
                "-30",
                "0",
                "30",
                "60",
                "90",
                "120",
                "150",
                NULL
            };
            lv_scale_set_text_src(obj, label_texts);
            {
                state->scale_section = lv_scale_add_section(obj);
                lv_scale_section_set_range(state->scale_section, 22, 50);
                {
                    if (!windDirectionScale_section_main_style_initialized) {
                        lv_style_init(&windDirectionScale_section_main_style);
                        windDirectionScale_section_main_style_initialized = true;
                        lv_style_set_arc_width(&windDirectionScale_section_main_style, 5);
                        lv_style_set_arc_color(&windDirectionScale_section_main_style, lv_color_hex(0xff00e000));
                    }
                    lv_scale_set_section_style_main(obj, state->scale_section, &windDirectionScale_section_main_style);
                }
                {
                    if (!windDirectionScale_section_items_style_initialized) {
                        lv_style_init(&windDirectionScale_section_items_style);
                        windDirectionScale_section_items_style_initialized = true;
                        lv_style_set_line_color(&windDirectionScale_section_items_style, lv_color_hex(0xff00e000));
                    }
                    lv_scale_set_section_style_items(obj, state->scale_section, &windDirectionScale_section_items_style);
                }
                {
                    if (!windDirectionScale_section_indicator_style_initialized) {
                        lv_style_init(&windDirectionScale_section_indicator_style);
                        windDirectionScale_section_indicator_style_initialized = true;
                        lv_style_set_line_color(&windDirectionScale_section_indicator_style, lv_color_hex(0xff00e000));
                    }
                    lv_scale_set_section_style_indicator(obj, state->scale_section, &windDirectionScale_section_indicator_style);
                }
            }
            {
                state->scale_section1 = lv_scale_add_section(obj);
                lv_scale_section_set_range(state->scale_section1, -50, -22);
                {
                    if (!windDirectionScale_section_main_style1_initialized) {
                        lv_style_init(&windDirectionScale_section_main_style1);
                        windDirectionScale_section_main_style1_initialized = true;
                        lv_style_set_arc_width(&windDirectionScale_section_main_style1, 5);
                        lv_style_set_arc_color(&windDirectionScale_section_main_style1, lv_color_hex(0xffe00000));
                    }
                    lv_scale_set_section_style_main(obj, state->scale_section1, &windDirectionScale_section_main_style1);
                }
                {
                    if (!windDirectionScale_section_items_style1_initialized) {
                        lv_style_init(&windDirectionScale_section_items_style1);
                        windDirectionScale_section_items_style1_initialized = true;
                        lv_style_set_line_color(&windDirectionScale_section_items_style1, lv_color_hex(0xffe00000));
                    }
                    lv_scale_set_section_style_items(obj, state->scale_section1, &windDirectionScale_section_items_style1);
                }
                {
                    if (!windDirectionScale_section_indicator_style1_initialized) {
                        lv_style_init(&windDirectionScale_section_indicator_style1);
                        windDirectionScale_section_indicator_style1_initialized = true;
                        lv_style_set_line_color(&windDirectionScale_section_indicator_style1, lv_color_hex(0xffe00000));
                    }
                    lv_scale_set_section_style_indicator(obj, state->scale_section1, &windDirectionScale_section_indicator_style1);
                }
            }
            {
                state->scale_section2 = lv_scale_add_section(obj);
                lv_scale_section_set_range(state->scale_section2, 145, -145);
                {
                    if (!windDirectionScale_section_main_style2_initialized) {
                        lv_style_init(&windDirectionScale_section_main_style2);
                        windDirectionScale_section_main_style2_initialized = true;
                        lv_style_set_arc_width(&windDirectionScale_section_main_style2, 5);
                        lv_style_set_arc_color(&windDirectionScale_section_main_style2, lv_color_hex(0xffffa500));
                    }
                    lv_scale_set_section_style_main(obj, state->scale_section2, &windDirectionScale_section_main_style2);
                }
                {
                    if (!windDirectionScale_section_items_style2_initialized) {
                        lv_style_init(&windDirectionScale_section_items_style2);
                        windDirectionScale_section_items_style2_initialized = true;
                        lv_style_set_line_color(&windDirectionScale_section_items_style2, lv_color_hex(0xffffa500));
                    }
                    lv_scale_set_section_style_items(obj, state->scale_section2, &windDirectionScale_section_items_style2);
                }
                {
                    if (!windDirectionScale_section_indicator_style2_initialized) {
                        lv_style_init(&windDirectionScale_section_indicator_style2);
                        windDirectionScale_section_indicator_style2_initialized = true;
                        lv_style_set_line_color(&windDirectionScale_section_indicator_style2, lv_color_hex(0xffffa500));
                    }
                    lv_scale_set_section_style_indicator(obj, state->scale_section2, &windDirectionScale_section_indicator_style2);
                }
            }
            // lv_obj_set_style_bg_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            // lv_obj_set_style_bg_color(obj, lv_color_hex(0xff212529), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_transform_scale_y(obj, 268, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_radius(obj, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_pad_top(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_text_align(obj, LV_TEXT_ALIGN_RIGHT, LV_PART_INDICATOR | LV_STATE_DEFAULT);
            lv_obj_set_style_arc_width(obj, 0, LV_PART_MAIN);
            lv_obj_set_style_length(obj, 10, LV_PART_ITEMS);
            lv_obj_set_style_line_width(obj, 3, LV_PART_ITEMS);
            lv_obj_set_style_line_color(obj, lv_color_hex(0xff606060), LV_PART_ITEMS);
            lv_obj_set_style_length(obj, 20, LV_PART_INDICATOR);
            lv_obj_set_style_line_width(obj, 4, LV_PART_INDICATOR);
            lv_obj_set_style_line_color(obj, lv_color_hex(0xff7f7f7f), LV_PART_INDICATOR);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_16, LV_PART_INDICATOR);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // boatImage
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    objects.boat_image = obj;
                    lv_image_set_src(obj, &img_boat);
                    lv_obj_set_style_pad_top(obj, 200, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_pad_left(obj, 180, LV_PART_MAIN | LV_STATE_DEFAULT); // 200
                    lv_scale_set_image_needle_value(parent_obj, obj, 90);
                }
                {
                    // omaLine
                    lv_obj_t *obj = lv_line_create(parent_obj);
                    objects.owa_line = obj;
                    lv_obj_set_style_line_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_line_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_move_foreground(obj);
                    lv_scale_set_line_needle_value(parent_obj, obj, 150, 45);
                }
                {
                    // awaArrow
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    objects.awa_arrow = obj;
                    lv_image_set_src(obj, &img_apparent_arrow);
                    lv_obj_align(obj, LV_ALIGN_CENTER, 0, -10);
                }
                {
                    // twaArrow
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    objects.twa_arrow = obj;
                    lv_image_set_src(obj, &img_true_arrow);
                    lv_obj_align(obj, LV_ALIGN_CENTER, 0, -10);
                }
            }
        }
        {
            // heelTiltScale
            lv_obj_t *obj = lv_scale_create(parent_obj);
            objects.heel_tilt_scale = obj;
            lv_obj_set_pos(obj, 312, 47);
            lv_obj_set_size(obj, 400, 40);
            lv_scale_set_mode(obj, LV_SCALE_MODE_HORIZONTAL_BOTTOM);
            lv_scale_set_range(obj, -45, 45);
            lv_scale_set_angle_range(obj, 270);
            lv_scale_set_rotation(obj, 135);
            lv_scale_set_total_tick_count(obj, 31);
            lv_scale_set_major_tick_every(obj, 5);
            lv_scale_set_label_show(obj, true);
            {
                state->scale_section3 = lv_scale_add_section(obj);
                lv_scale_section_set_range(state->scale_section3, -45, -16);
                {
                    if (!heelTiltScale_section_main_style_initialized) {
                        lv_style_init(&heelTiltScale_section_main_style);
                        heelTiltScale_section_main_style_initialized = true;
                        lv_style_set_line_width(&heelTiltScale_section_main_style, 3);
                        lv_style_set_line_color(&heelTiltScale_section_main_style, lv_color_hex(0xffffa500));
                    }
                    lv_scale_set_section_style_main(obj, state->scale_section3, &heelTiltScale_section_main_style);
                }
                {
                    if (!heelTiltScale_section_items_style_initialized) {
                        lv_style_init(&heelTiltScale_section_items_style);
                        heelTiltScale_section_items_style_initialized = true;
                        lv_style_set_line_color(&heelTiltScale_section_items_style, lv_color_hex(0xffffa500));
                    }
                    lv_scale_set_section_style_items(obj, state->scale_section3, &heelTiltScale_section_items_style);
                }
                {
                    if (!heelTiltScale_section_indicator_style_initialized) {
                        lv_style_init(&heelTiltScale_section_indicator_style);
                        heelTiltScale_section_indicator_style_initialized = true;
                        lv_style_set_line_color(&heelTiltScale_section_indicator_style, lv_color_hex(0xffffa500));
                    }
                    lv_scale_set_section_style_indicator(obj, state->scale_section3, &heelTiltScale_section_indicator_style);
                }
            }
            {
                state->scale_section4 = lv_scale_add_section(obj);
                lv_scale_section_set_range(state->scale_section4, 16, 45);
                {
                    if (!heelTiltScale_section_main_style1_initialized) {
                        lv_style_init(&heelTiltScale_section_main_style1);
                        heelTiltScale_section_main_style1_initialized = true;
                        lv_style_set_line_width(&heelTiltScale_section_main_style1, 3);
                        lv_style_set_line_color(&heelTiltScale_section_main_style1, lv_color_hex(0xffffa500));
                    }
                    lv_scale_set_section_style_main(obj, state->scale_section4, &heelTiltScale_section_main_style1);
                }
                {
                    if (!heelTiltScale_section_items_style1_initialized) {
                        lv_style_init(&heelTiltScale_section_items_style1);
                        heelTiltScale_section_items_style1_initialized = true;
                        lv_style_set_line_color(&heelTiltScale_section_items_style1, lv_color_hex(0xffffa500));
                    }
                    lv_scale_set_section_style_items(obj, state->scale_section4, &heelTiltScale_section_items_style1);
                }
                {
                    if (!heelTiltScale_section_indicator_style1_initialized) {
                        lv_style_init(&heelTiltScale_section_indicator_style1);
                        heelTiltScale_section_indicator_style1_initialized = true;
                        lv_style_set_line_color(&heelTiltScale_section_indicator_style1, lv_color_hex(0xffffa500));
                    }
                    lv_scale_set_section_style_indicator(obj, state->scale_section4, &heelTiltScale_section_indicator_style1);
                }
            }
            {
                lv_obj_t *parent_obj = obj;
                {
                    // heelTiltBar
                    lv_obj_t *obj = lv_bar_create(parent_obj);
                    objects.heel_tilt_bar = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 400, 4);
                    lv_bar_set_range(obj, -45, 45);
                    lv_bar_set_mode(obj, LV_BAR_MODE_SYMMETRICAL);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff0000), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // rudderRotationScale
            lv_obj_t *obj = lv_scale_create(parent_obj);
            objects.rudder_rotation_scale = obj;
            lv_obj_set_pos(obj, 312, 548);
            lv_obj_set_size(obj, 400, 25);
            lv_scale_set_mode(obj, LV_SCALE_MODE_HORIZONTAL_BOTTOM);
            lv_scale_set_range(obj, -45, 45);
            lv_scale_set_angle_range(obj, 270);
            lv_scale_set_rotation(obj, 135);
            lv_scale_set_total_tick_count(obj, 31);
            lv_scale_set_major_tick_every(obj, 5);
            lv_scale_set_label_show(obj, true);
            {
                state->scale_section5 = lv_scale_add_section(obj);
                lv_scale_section_set_range(state->scale_section5, -10, 10);
                {
                    if (!rudderRotationScale_section_main_style_initialized) {
                        lv_style_init(&rudderRotationScale_section_main_style);
                        rudderRotationScale_section_main_style_initialized = true;
                        lv_style_set_line_width(&rudderRotationScale_section_main_style, 3);
                        lv_style_set_line_color(&rudderRotationScale_section_main_style, lv_color_hex(0xff00e000));
                    }
                    lv_scale_set_section_style_main(obj, state->scale_section5, &rudderRotationScale_section_main_style);
                }
            }
            {
                lv_obj_t *parent_obj = obj;
                {
                    // rudderRotationBar
                    lv_obj_t *obj = lv_bar_create(parent_obj);
                    objects.rudder_rotation_bar = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, 400, 4);
                    lv_bar_set_range(obj, -45, 45);
                    lv_bar_set_mode(obj, LV_BAR_MODE_SYMMETRICAL);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff0000), LV_PART_INDICATOR | LV_STATE_DEFAULT);
                    lv_obj_set_style_radius(obj, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
                    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                }
            }
        }
        {
            // awsLabel
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.aws_label = obj;
            lv_obj_set_pos(obj, 424, 310);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "APPARENT WIND SPEED");
        }
        {
            // awsValueLabel
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.aws_value_label = obj;
            // lv_obj_set_pos(obj, 455, 326);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_align(obj, LV_ALIGN_CENTER, 0, 60);
            lv_obj_set_style_text_font(obj, &ui_font_montserrat, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // awsUnitLabel
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.aws_unit_label = obj;
            lv_obj_set_pos(obj, 499, 394);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "m/s");
        }
        {
            // boatStatusLabel
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.boat_status_label = obj;
            // lv_obj_set_pos(obj, 484, 16);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_align(obj, LV_ALIGN_CENTER, 0, -284);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // stwLabel
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.stw_label = obj;
            lv_obj_set_pos(obj, 813, 114);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "SPEED THRU WATER");
        }
        {
            // stwValueLabel
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.stw_value_label = obj;
            lv_obj_set_pos(obj, 813, 130);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_montserrat, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // stwUnitLabel
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.stw_unit_label = obj;
            lv_obj_set_pos(obj, 956, 172);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "kts");
        }
        {
            // stwLine
            lv_obj_t *obj = lv_line_create(parent_obj);
            objects.stw_line = obj;
            lv_obj_set_pos(obj, 800, 133);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            static lv_point_precise_t line_points[] = {
                { 0, 0 },
                { 224, 0 }
            };
            lv_line_set_points(obj, line_points, 2);
            lv_obj_set_style_line_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // sogLabel
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.sog_label = obj;
            lv_obj_set_pos(obj, 813, 214);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "SPEED OVER GROUND");
        }
        {
            // sogValueLabel
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.sog_value_label = obj;
            lv_obj_set_pos(obj, 813, 230);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_montserrat, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // sogUnitLabel
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.sog_unit_label = obj;
            lv_obj_set_pos(obj, 956, 272);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "kts");
        }
        {
            // sogLine
            lv_obj_t *obj = lv_line_create(parent_obj);
            objects.sog_line = obj;
            lv_obj_set_pos(obj, 800, 233);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            static lv_point_precise_t line_points[] = {
                { 0, 0 },
                { 224, 0 }
            };
            lv_line_set_points(obj, line_points, 2);
            lv_obj_set_style_line_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // vmgLabel
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.vmg_label = obj;
            lv_obj_set_pos(obj, 813, 313);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "VELOCITY MADE GOOD");
        }
        {
            // vmgValueLabel
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.vmg_value_label = obj;
            lv_obj_set_pos(obj, 813, 329);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_montserrat, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // vmgUnitLabel
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.vmg_unit_label = obj;
            lv_obj_set_pos(obj, 956, 371);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "kts");
        }
        {
            // vmgLine
            lv_obj_t *obj = lv_line_create(parent_obj);
            objects.vmg_line = obj;
            lv_obj_set_pos(obj, 800, 332);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            static lv_point_precise_t line_points[] = {
                { 0, 0 },
                { 224, 0 }
            };
            lv_line_set_points(obj, line_points, 2);
            lv_obj_set_style_line_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // polarRatioLabel
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.polar_ratio_label = obj;
            lv_obj_set_pos(obj, 813, 402);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "POLAR PERFORMANCE");
        }
        {
            // polarRatioValueLabel
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.polar_ratio_value_label = obj;
            lv_obj_set_pos(obj, 813, 422);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_montserrat, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // polarRatioUnitLabel
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.polar_ratio_unit_label = obj;
            lv_obj_set_pos(obj, 956, 460);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "%");
        }
        {
            // polarRatioLine
            lv_obj_t *obj = lv_line_create(parent_obj);
            objects.polar_ratio_line = obj;
            lv_obj_set_pos(obj, 800, 421);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            static lv_point_precise_t line_points[] = {
                { 0, 0 },
                { 224, 0 }
            };
            lv_line_set_points(obj, line_points, 2);
            lv_obj_set_style_line_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // awaLabel
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.awa_label = obj;
            lv_obj_set_pos(obj, 46, 114);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "APPARENT WIND ANGLE");
        }
        {
            // awaValueLabel
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.awa_value_label = obj;
            lv_obj_set_pos(obj, 43, 130);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_montserrat, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // awaUnitLabel
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.awa_unit_label = obj;
            lv_obj_set_pos(obj, 186, 130);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_montserrat, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "°");
        }
        {
            // awaLine
            lv_obj_t *obj = lv_line_create(parent_obj);
            objects.awa_line = obj;
            lv_obj_set_pos(obj, 0, 133);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            static lv_point_precise_t line_points[] = {
                { 0, 0 },
                { 224, 0 }
            };
            lv_line_set_points(obj, line_points, 2);
            lv_obj_set_style_line_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // twaLabel
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.twa_label = obj;
            lv_obj_set_pos(obj, 46, 214);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "TRUE WIND ANGLE");
        }
        {
            // twaValueLabel
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.twa_value_label = obj;
            lv_obj_set_pos(obj, 43, 230);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_montserrat, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // twaUnitLabel
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.twa_unit_label = obj;
            lv_obj_set_pos(obj, 186, 230);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_montserrat, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "°");
        }
        {
            // twaLine
            lv_obj_t *obj = lv_line_create(parent_obj);
            objects.twa_line = obj;
            lv_obj_set_pos(obj, 0, 233);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            static lv_point_precise_t line_points[] = {
                { 0, 0 },
                { 224, 0 }
            };
            lv_line_set_points(obj, line_points, 2);
            lv_obj_set_style_line_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // twsLabel
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.tws_label = obj;
            lv_obj_set_pos(obj, 46, 313);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "TRUE WIND SPEED");
        }
        {
            // twsValueLabel
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.tws_value_label = obj;
            lv_obj_set_pos(obj, 43, 329);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_montserrat, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // twsUnitLabel
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.tws_unit_label = obj;
            lv_obj_set_pos(obj, 186, 371);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "m/s");
        }
        {
            // twsLine
            lv_obj_t *obj = lv_line_create(parent_obj);
            objects.tws_line = obj;
            lv_obj_set_pos(obj, 0, 332);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            static lv_point_precise_t line_points[] = {
                { 0, 0 },
                { 224, 0 }
            };
            lv_line_set_points(obj, line_points, 2);
            lv_obj_set_style_line_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // cogLabel
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.cog_label = obj;
            lv_obj_set_pos(obj, 46, 402);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "COURSE OVER GROUND");
        }
        {
            // cogValueLabel
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.cog_value_label = obj;
            lv_obj_set_pos(obj, 43, 418);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_montserrat, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // cogUnitLabel
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.cog_unit_label = obj;
            lv_obj_set_pos(obj, 186, 418);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_montserrat, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "°");
        }
        {
            // cogLine
            lv_obj_t *obj = lv_line_create(parent_obj);
            objects.cog_line = obj;
            lv_obj_set_pos(obj, 0, 421);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            static lv_point_precise_t line_points[] = {
                { 0, 0 },
                { 224, 0 }
            };
            lv_line_set_points(obj, line_points, 2);
            lv_obj_set_style_line_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
    }
    
    tick_screen_main();
}

void tick_screen_main() {
    screen_main_state_t *state = &screen_main_state;
    (void)state;
    {
        int32_t new_val = get_var_apparent_wind_angle_raw();
        lv_scale_set_image_needle_value(lv_obj_get_parent(objects.awa_arrow), objects.awa_arrow, new_val);
    }
    {
        int32_t new_val = get_var_true_wind_angle_raw();
        lv_scale_set_image_needle_value(lv_obj_get_parent(objects.twa_arrow), objects.twa_arrow, new_val);
    }
    {
        int32_t new_val = get_var_optimum_wind_angle_value();
        lv_scale_set_line_needle_value(lv_obj_get_parent(objects.owa_line), objects.owa_line, 150, new_val);
    }
    {
        int32_t new_val = get_var_heel_scale_value();
        int32_t cur_val = lv_bar_get_value(objects.heel_tilt_bar);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.heel_tilt_bar;
            lv_bar_set_value(objects.heel_tilt_bar, new_val, LV_ANIM_ON);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = get_var_rudder_scale_value();
        int32_t cur_val = lv_bar_get_value(objects.rudder_rotation_bar);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.rudder_rotation_bar;
            lv_bar_set_value(objects.rudder_rotation_bar, new_val, LV_ANIM_ON);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_apparent_wind_speed_value();
        const char *cur_val = lv_label_get_text(objects.aws_value_label);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.aws_value_label;
            lv_label_set_text(objects.aws_value_label, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_boat_status_value();
        const char *cur_val = lv_label_get_text(objects.boat_status_label);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.boat_status_label;
            lv_label_set_text(objects.boat_status_label, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_speed_through_water_value();
        const char *cur_val = lv_label_get_text(objects.stw_value_label);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.stw_value_label;
            lv_label_set_text(objects.stw_value_label, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_speed_over_ground_value();
        const char *cur_val = lv_label_get_text(objects.sog_value_label);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.sog_value_label;
            lv_label_set_text(objects.sog_value_label, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_velocity_made_good_value();
        const char *cur_val = lv_label_get_text(objects.vmg_value_label);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.vmg_value_label;
            lv_label_set_text(objects.vmg_value_label, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_polar_performance_ratio_value();
        const char *cur_val = lv_label_get_text(objects.polar_ratio_value_label);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.polar_ratio_value_label;
            lv_label_set_text(objects.polar_ratio_value_label, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_apparent_wind_angle_value();
        const char *cur_val = lv_label_get_text(objects.awa_value_label);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.awa_value_label;
            lv_label_set_text(objects.awa_value_label, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_true_wind_angle_value();
        const char *cur_val = lv_label_get_text(objects.twa_value_label);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.twa_value_label;
            lv_label_set_text(objects.twa_value_label, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_true_wind_speed_value();
        const char *cur_val = lv_label_get_text(objects.tws_value_label);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.tws_value_label;
            lv_label_set_text(objects.tws_value_label, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_course_over_ground_value();
        const char *cur_val = lv_label_get_text(objects.cog_value_label);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.cog_value_label;
            lv_label_set_text(objects.cog_value_label, new_val);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_highlights() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.highlights = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 1024, 600);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 390, 60);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_34, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Trip Summary");
        }
        {
            // stwLabel_1
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.stw_label_1 = obj;
            lv_obj_set_pos(obj, 813, 114);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "DISTANCE");
        }
        {
            // stwValueLabel_1
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.stw_value_label_1 = obj;
            lv_obj_set_pos(obj, 813, 130);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_montserrat, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // stwUnitLabel_1
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.stw_unit_label_1 = obj;
            lv_obj_set_pos(obj, 956, 172);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "nm");
        }
        {
            // stwLine_1
            lv_obj_t *obj = lv_line_create(parent_obj);
            objects.stw_line_1 = obj;
            lv_obj_set_pos(obj, 800, 133);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            static lv_point_precise_t line_points[] = {
                { 0, 0 },
                { 224, 0 }
            };
            lv_line_set_points(obj, line_points, 2);
            lv_obj_set_style_line_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // sogLabel_1
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.sog_label_1 = obj;
            lv_obj_set_pos(obj, 813, 214);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "DURATION");
        }
        {
            // sogValueLabel_1
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.sog_value_label_1 = obj;
            lv_obj_set_pos(obj, 813, 230);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_montserrat, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // sogUnitLabel_1
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.sog_unit_label_1 = obj;
            lv_obj_set_pos(obj, 956, 272);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "h");
        }
        {
            // sogLine_1
            lv_obj_t *obj = lv_line_create(parent_obj);
            objects.sog_line_1 = obj;
            lv_obj_set_pos(obj, 800, 233);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            static lv_point_precise_t line_points[] = {
                { 0, 0 },
                { 224, 0 }
            };
            lv_line_set_points(obj, line_points, 2);
            lv_obj_set_style_line_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // vmgLabel_1
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.vmg_label_1 = obj;
            lv_obj_set_pos(obj, 813, 313);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "FUEL BURNED");
        }
        {
            // vmgValueLabel_1
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.vmg_value_label_1 = obj;
            lv_obj_set_pos(obj, 813, 329);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_montserrat, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // vmgUnitLabel_1
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.vmg_unit_label_1 = obj;
            lv_obj_set_pos(obj, 956, 371);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "L");
        }
        {
            // vmgLine_1
            lv_obj_t *obj = lv_line_create(parent_obj);
            objects.vmg_line_1 = obj;
            lv_obj_set_pos(obj, 800, 332);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            static lv_point_precise_t line_points[] = {
                { 0, 0 },
                { 224, 0 }
            };
            lv_line_set_points(obj, line_points, 2);
            lv_obj_set_style_line_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // polarRatioLabel_1
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.polar_ratio_label_1 = obj;
            lv_obj_set_pos(obj, 813, 400);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "ENGINE TIME");
        }
        {
            // polarRatioValueLabel_1
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.polar_ratio_value_label_1 = obj;
            lv_obj_set_pos(obj, 813, 422);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_montserrat, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // polarRatioUnitLabel_1
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.polar_ratio_unit_label_1 = obj;
            lv_obj_set_pos(obj, 956, 460);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "h");
        }
        {
            // polarRatioLine_1
            lv_obj_t *obj = lv_line_create(parent_obj);
            objects.polar_ratio_line_1 = obj;
            lv_obj_set_pos(obj, 800, 421);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            static lv_point_precise_t line_points[] = {
                { 0, 0 },
                { 224, 0 }
            };
            lv_line_set_points(obj, line_points, 2);
            lv_obj_set_style_line_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // awaLabel_1
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.awa_label_1 = obj;
            lv_obj_set_pos(obj, 46, 114);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "TOP SPEED");
        }
        {
            // awaValueLabel_1
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.awa_value_label_1 = obj;
            lv_obj_set_pos(obj, 43, 130);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_montserrat, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // awaLine_1
            lv_obj_t *obj = lv_line_create(parent_obj);
            objects.awa_line_1 = obj;
            lv_obj_set_pos(obj, 0, 133);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            static lv_point_precise_t line_points[] = {
                { 0, 0 },
                { 224, 0 }
            };
            lv_line_set_points(obj, line_points, 2);
            lv_obj_set_style_line_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // twaLabel_1
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.twa_label_1 = obj;
            lv_obj_set_pos(obj, 46, 214);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "AVERAGE SPEED");
        }
        {
            // twaValueLabel_1
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.twa_value_label_1 = obj;
            lv_obj_set_pos(obj, 43, 230);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_montserrat, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // twaLine_1
            lv_obj_t *obj = lv_line_create(parent_obj);
            objects.twa_line_1 = obj;
            lv_obj_set_pos(obj, 0, 233);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            static lv_point_precise_t line_points[] = {
                { 0, 0 },
                { 224, 0 }
            };
            lv_line_set_points(obj, line_points, 2);
            lv_obj_set_style_line_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // twsLabel_1
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.tws_label_1 = obj;
            lv_obj_set_pos(obj, 46, 313);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "TOP WIND SPEED");
        }
        {
            // twsValueLabel_1
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.tws_value_label_1 = obj;
            lv_obj_set_pos(obj, 43, 329);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_montserrat, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // twsUnitLabel_1
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.tws_unit_label_1 = obj;
            lv_obj_set_pos(obj, 186, 371);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "m/s");
        }
        {
            // twsLine_1
            lv_obj_t *obj = lv_line_create(parent_obj);
            objects.tws_line_1 = obj;
            lv_obj_set_pos(obj, 0, 332);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            static lv_point_precise_t line_points[] = {
                { 0, 0 },
                { 224, 0 }
            };
            lv_line_set_points(obj, line_points, 2);
            lv_obj_set_style_line_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // cogLabel_1
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.cog_label_1 = obj;
            lv_obj_set_pos(obj, 46, 402);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "AVERAGE WIND SPEED");
        }
        {
            // cogValueLabel_1
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.cog_value_label_1 = obj;
            lv_obj_set_pos(obj, 43, 418);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &ui_font_montserrat, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            // cogLine_1
            lv_obj_t *obj = lv_line_create(parent_obj);
            objects.cog_line_1 = obj;
            lv_obj_set_pos(obj, 0, 421);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            static lv_point_precise_t line_points[] = {
                { 0, 0 },
                { 224, 0 }
            };
            lv_line_set_points(obj, line_points, 2);
            lv_obj_set_style_line_width(obj, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // twsUnitLabel_2
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.tws_unit_label_2 = obj;
            lv_obj_set_pos(obj, 186, 172);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "kts");
        }
        {
            // twsUnitLabel_3
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.tws_unit_label_3 = obj;
            lv_obj_set_pos(obj, 186, 272);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "kts");
        }
        {
            // twsUnitLabel_4
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.tws_unit_label_4 = obj;
            lv_obj_set_pos(obj, 186, 460);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "m/s");
        }
    }
    
    tick_screen_highlights();
}

void tick_screen_highlights() {
    {
        const char *new_val = get_var_distance_traveled_value();
        const char *cur_val = lv_label_get_text(objects.stw_value_label_1);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.stw_value_label_1;
            lv_label_set_text(objects.stw_value_label_1, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_time_sailed_value();
        const char *cur_val = lv_label_get_text(objects.sog_value_label_1);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.sog_value_label_1;
            lv_label_set_text(objects.sog_value_label_1, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_fuel_burned_value();
        const char *cur_val = lv_label_get_text(objects.vmg_value_label_1);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.vmg_value_label_1;
            lv_label_set_text(objects.vmg_value_label_1, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_engine_time_value();
        const char *cur_val = lv_label_get_text(objects.polar_ratio_value_label_1);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.polar_ratio_value_label_1;
            lv_label_set_text(objects.polar_ratio_value_label_1, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_top_speed_value();
        const char *cur_val = lv_label_get_text(objects.awa_value_label_1);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.awa_value_label_1;
            lv_label_set_text(objects.awa_value_label_1, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_average_speed_value();
        const char *cur_val = lv_label_get_text(objects.twa_value_label_1);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.twa_value_label_1;
            lv_label_set_text(objects.twa_value_label_1, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_top_wind_speed_value();
        const char *cur_val = lv_label_get_text(objects.tws_value_label_1);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.tws_value_label_1;
            lv_label_set_text(objects.tws_value_label_1, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_average_wind_speed_value();
        const char *cur_val = lv_label_get_text(objects.cog_value_label_1);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.cog_value_label_1;
            lv_label_set_text(objects.cog_value_label_1, new_val);
            tick_value_change_obj = NULL;
        }
    }
}

typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_main,
    tick_screen_highlights,
};
void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen_funcs[screenId - 1]();
}

//
// Fonts
//

ext_font_desc_t fonts[] = {
    { "Montserrat", &ui_font_montserrat },
#if LV_FONT_MONTSERRAT_8
    { "MONTSERRAT_8", &lv_font_montserrat_8 },
#endif
#if LV_FONT_MONTSERRAT_10
    { "MONTSERRAT_10", &lv_font_montserrat_10 },
#endif
#if LV_FONT_MONTSERRAT_12
    { "MONTSERRAT_12", &lv_font_montserrat_12 },
#endif
#if LV_FONT_MONTSERRAT_14
    { "MONTSERRAT_14", &lv_font_montserrat_14 },
#endif
#if LV_FONT_MONTSERRAT_16
    { "MONTSERRAT_16", &lv_font_montserrat_16 },
#endif
#if LV_FONT_MONTSERRAT_18
    { "MONTSERRAT_18", &lv_font_montserrat_18 },
#endif
#if LV_FONT_MONTSERRAT_20
    { "MONTSERRAT_20", &lv_font_montserrat_20 },
#endif
#if LV_FONT_MONTSERRAT_22
    { "MONTSERRAT_22", &lv_font_montserrat_22 },
#endif
#if LV_FONT_MONTSERRAT_24
    { "MONTSERRAT_24", &lv_font_montserrat_24 },
#endif
#if LV_FONT_MONTSERRAT_26
    { "MONTSERRAT_26", &lv_font_montserrat_26 },
#endif
#if LV_FONT_MONTSERRAT_28
    { "MONTSERRAT_28", &lv_font_montserrat_28 },
#endif
#if LV_FONT_MONTSERRAT_30
    { "MONTSERRAT_30", &lv_font_montserrat_30 },
#endif
#if LV_FONT_MONTSERRAT_32
    { "MONTSERRAT_32", &lv_font_montserrat_32 },
#endif
#if LV_FONT_MONTSERRAT_34
    { "MONTSERRAT_34", &lv_font_montserrat_34 },
#endif
#if LV_FONT_MONTSERRAT_36
    { "MONTSERRAT_36", &lv_font_montserrat_36 },
#endif
#if LV_FONT_MONTSERRAT_38
    { "MONTSERRAT_38", &lv_font_montserrat_38 },
#endif
#if LV_FONT_MONTSERRAT_40
    { "MONTSERRAT_40", &lv_font_montserrat_40 },
#endif
#if LV_FONT_MONTSERRAT_42
    { "MONTSERRAT_42", &lv_font_montserrat_42 },
#endif
#if LV_FONT_MONTSERRAT_44
    { "MONTSERRAT_44", &lv_font_montserrat_44 },
#endif
#if LV_FONT_MONTSERRAT_46
    { "MONTSERRAT_46", &lv_font_montserrat_46 },
#endif
#if LV_FONT_MONTSERRAT_48
    { "MONTSERRAT_48", &lv_font_montserrat_48 },
#endif
};

//
// Color themes
//

uint32_t active_theme_index = 0;

//
//
//

void create_screens() {

// Set default LVGL theme
    lv_display_t *dispp = lv_display_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), true, LV_FONT_DEFAULT);
    lv_display_set_theme(dispp, theme);
    
    // Initialize screens
    // Create screens
    create_screen_main();
    create_screen_highlights();
}