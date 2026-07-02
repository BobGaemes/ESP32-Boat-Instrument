#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

/* -----------------------------------------------------------------------
 * vars.h
 *
 * Return types by variable:
 *
 *   heel, rudder          -> int32_t   (used by lv_bar_set_value)
 *
 *   awa, twa              -> const char* for label display
 *                         -> int32_t   via get_var_*_raw() for needle
 *
 *   everything else       -> const char* only
 *
 * All set_* functions take a raw float from SignalK.
 * boat_status takes const char*.
 * ----------------------------------------------------------------------- */

/* Multiplier constants (used in vars.c CONV_* block) */
#define UNIT_RAD_TO_DEG (57.295779513f)
#define UNIT_DEG_TO_DEG (1.0f)
#define UNIT_MS_TO_KT (1.943844f)
#define UNIT_KT_TO_KT (1.0f)
#define UNIT_MS_TO_KMH (3.6f)
#define UNIT_M_TO_NM (0.000539957f)
#define UNIT_NM_TO_NM (1.0f)
#define UNIT_M_TO_M (1.0f)
#define UNIT_S_TO_H (0.000277778f)
#define UNIT_MIN_TO_H (0.016666667f)
#define UNIT_H_TO_H (1.0f)
#define UNIT_L_TO_L (1.0f)
#define UNIT_M3_TO_L (1000.0f)
#define UNIT_PERCENT (100.0f)
#define UNIT_MS_TO_MS (1.0f)

    /* --- Heel / Rudder (int32_t, used by lv_bar) --- */
    int32_t get_var_heel_scale_value(void);
    void set_var_heel_scale_value(float value);

    int32_t get_var_rudder_scale_value(void);
    void set_var_rudder_scale_value(float value);

    /* --- Optimum Wind Angle (int32_t for needle) --- */
    int32_t get_var_optimum_wind_angle_value(void);
    void set_var_optimum_wind_angle_value(float value);

    /* --- Apparent Wind Angle (char* for label, int32_t for needle) --- */
    const char *get_var_apparent_wind_angle_value(void);
    int32_t get_var_apparent_wind_angle_raw(void);
    void set_var_apparent_wind_angle_value(float value);

    /* --- True Wind Angle (char* for label, int32_t for needle) --- */
    const char *get_var_true_wind_angle_value(void);
    int32_t get_var_true_wind_angle_raw(void);
    void set_var_true_wind_angle_value(float value);

    /* --- All others (const char*) --- */
    const char *get_var_true_wind_speed_value(void);
    void set_var_true_wind_speed_value(float value);

    const char *get_var_speed_through_water_value(void);
    void set_var_speed_through_water_value(float value);

    const char *get_var_speed_over_ground_value(void);
    void set_var_speed_over_ground_value(float value);

    const char *get_var_velocity_made_good_value(void);
    void set_var_velocity_made_good_value(float value);

    const char *get_var_polar_performance_ratio_value(void);
    void set_var_polar_performance_ratio_value(float value);

    const char *get_var_depth_value(void);
    void set_var_depth_value(float value);

    const char *get_var_course_over_ground_value(void);
    void set_var_course_over_ground_value(float value);

    const char *get_var_apparent_wind_speed_value(void);
    void set_var_apparent_wind_speed_value(float value);

    const char *get_var_top_speed_value(void);
    void set_var_top_speed_value(float value);

    const char *get_var_average_speed_value(void);
    void set_var_average_speed_value(float value);

    const char *get_var_top_wind_speed_value(void);
    void set_var_top_wind_speed_value(float value);

    const char *get_var_average_wind_speed_value(void);
    void set_var_average_wind_speed_value(float value);

    const char *get_var_distance_traveled_value(void);
    void set_var_distance_traveled_value(float value);

    const char *get_var_time_sailed_value(void);
    void set_var_time_sailed_value(float value);

    const char *get_var_fuel_burned_value(void);
    void set_var_fuel_burned_value(float value);

    const char *get_var_engine_time_value(void);
    void set_var_engine_time_value(float value);

    const char *get_var_boat_status_value(void);
    void set_var_boat_status_value(const char *value);

#ifdef __cplusplus
}
#endif