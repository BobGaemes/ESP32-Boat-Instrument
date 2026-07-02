#ifndef EEZ_LVGL_UI_GUI_H
#define EEZ_LVGL_UI_GUI_H

#include <lvgl.h>

#include "screens.h"

#ifdef __cplusplus
extern "C" {
#endif
    typedef enum
    {
        UI_LOG_INFO,
        UI_LOG_WARN,
        UI_LOG_ERROR,
    } ui_log_level_t;

    void ui_log(const char *msg);
    void ui_log_level(const char *msg, ui_log_level_t level);
    void ui_hide_log(void);
    void ui_init();
    void ui_tick();

    void loadScreen(enum ScreensEnum screenId);

#ifdef __cplusplus
}
#endif

#endif // EEZ_LVGL_UI_GUI_H