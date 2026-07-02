#include "ui.h"
#include "screens.h"
#include "images.h"
#include "vars.h"
#include <stdio.h>

#include <string.h>

static int16_t currentScreen = -1;

static lv_obj_t *log_overlay = NULL;
static lv_obj_t *log_label = NULL;


static lv_obj_t *getLvglObjectFromIndex(int32_t index) {
    if (index == -1) {
        return 0;
    }
    return ((lv_obj_t **)&objects)[index];
}

void ui_log_level(const char *msg, ui_log_level_t level)
{
    if (!log_overlay)
    {
        log_overlay = lv_obj_create(lv_layer_top());
        lv_obj_set_size(log_overlay, LV_PCT(100), LV_PCT(100));
        lv_obj_set_style_bg_color(log_overlay, lv_color_black(), 0);
        lv_obj_set_style_bg_opa(log_overlay, LV_OPA_COVER, 0);
        lv_obj_set_style_border_width(log_overlay, 0, 0);
        lv_obj_set_flex_flow(log_overlay, LV_FLEX_FLOW_COLUMN);
        lv_obj_set_flex_align(log_overlay, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
        lv_obj_set_style_pad_all(log_overlay, 8, 0);
        lv_obj_set_style_pad_row(log_overlay, 2, 0);
    }

    lv_color_t color;
    switch (level)
    {
    case UI_LOG_ERROR:
        color = lv_color_hex(0xFF4444);
        break;
    case UI_LOG_WARN:
        color = lv_color_hex(0xFFCC00);
        break;
    default:
        color = lv_color_hex(0x44ff44);
        break;
    }

    lv_obj_t *line = lv_label_create(log_overlay);
    lv_obj_set_width(line, LV_PCT(95));
    lv_label_set_long_mode(line, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_color(line, color, 0);
    lv_obj_set_style_text_font(line, &lv_font_montserrat_14, 0);
    lv_obj_set_style_pad_top(line, 2, 0);
    lv_label_set_text(line, msg);
}

void ui_log(const char *msg)
{
    ui_log_level(msg, UI_LOG_INFO);
}

void ui_hide_log(void)
{
    if (log_overlay)
    {
        lv_obj_del(log_overlay);
        log_overlay = NULL;
    }
}

void loadScreen(enum ScreensEnum screenId) {
    currentScreen = screenId - 1;
    lv_obj_t *screen = getLvglObjectFromIndex(currentScreen);
    lv_scr_load_anim(screen, LV_SCR_LOAD_ANIM_FADE_IN, 200, 0, false);
}

void ui_init() {
    create_screens();
    loadScreen(SCREEN_ID_MAIN);

}

void ui_tick() {
    tick_screen(currentScreen);
}