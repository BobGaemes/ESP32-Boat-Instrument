#include "vars.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

/* -----------------------------------------------------------------------
 * UNIT CONVERSION CONFIGURATION
 *
 * Set each CONV_* to match what your SignalK server actually sends.
 * Multiply raw SignalK value by this to get the display unit.
 *
 * SignalK standard units (spec default):
 *   Angles    radians   -> use UNIT_RAD_TO_DEG
 *   Speed     m/s       -> use UNIT_MS_TO_KT
 *   Distance  m         -> use UNIT_M_TO_NM
 *   Time      s         -> use UNIT_S_TO_H
 *   Depth     m         -> use UNIT_M_TO_M
 *
 * Available multipliers are defined in vars.h.
 * SignalK paths are noted as comments for reference.
 * ----------------------------------------------------------------------- */

#define CONV_HEEL UNIT_RAD_TO_DEG   /* navigation.attitude.roll          */
#define CONV_RUDDER UNIT_RAD_TO_DEG /* steering.rudderAngle              */
#define CONV_OWA UNIT_RAD_TO_DEG    /* performance.optimumWindAngle      */
#define CONV_AWA UNIT_RAD_TO_DEG    /* environment.wind.angleApparent    */
#define CONV_TWA UNIT_RAD_TO_DEG    /* environment.wind.angleTrueWater   */
#define CONV_TWS UNIT_MS_TO_MS      /* environment.wind.speedTrue        */
#define CONV_STW UNIT_MS_TO_KT      /* navigation.speedThroughWater      */
#define CONV_SOG UNIT_MS_TO_KT      /* navigation.speedOverGround        */
#define CONV_VMG UNIT_MS_TO_KT      /* performance.velocityMadeGood      */
#define CONV_POLAR UNIT_PERCENT     /* ratio, multiply by 100            */
#define CONV_DEPTH UNIT_M_TO_M      /* environment.depth.belowKeel       */
#define CONV_COG UNIT_RAD_TO_DEG    /* navigation.courseOverGroundTrue   */
#define CONV_AWS UNIT_MS_TO_MS      /* environment.wind.speedApparent    */
#define CONV_TOP_SPEED UNIT_MS_TO_KT
#define CONV_AVG_SPEED UNIT_MS_TO_KT
#define CONV_TOP_WIND UNIT_MS_TO_KT
#define CONV_AVG_WIND UNIT_MS_TO_KT
#define CONV_DISTANCE UNIT_M_TO_NM   /* navigation.log                    */
#define CONV_TIME_SAILED UNIT_S_TO_H /* propulsion.*.runTime or similar   */
#define CONV_FUEL UNIT_L_TO_L        /* propulsion.*.fuel.used            */
#define CONV_ENGINE_TIME UNIT_S_TO_H /* propulsion.*.runTime              */

/* -----------------------------------------------------------------------
 * NUMBER FORMAT CONFIGURATION
 *
 * Each FMT_* picks a formatter for that variable.
 * Available formatters:
 *
 *   fmt_angle      3-digit zero-padded integer, supports negative.
 *                  1 -> "001"   45 -> "045"   180 -> "180"   -12 -> "-012"
 *
 *   fmt_speed      Adaptive 3 significant digits.
 *                  >= 100 -> "123"   >= 10 -> "12.3"   else -> "1.23"
 *
 *   fmt_wind       Always 1 decimal.
 *                  12.3 -> "12.3"   0.5 -> "0.5"
 *
 *   fmt_time       Adaptive hours, 1 decimal.
 *                  >= 100 -> "123"   else -> "12.3" or "1.2"
 *
 *   fmt_fixed0     No decimal.      123.4 -> "123"
 *   fmt_fixed1     1 decimal.       12.34 -> "12.3" >= 100 -> 123, not 123.0
 *   fmt_fixed2     2 decimals.      1.234 -> "1.23"
 *
 * Note: heel and rudder have no FMT_* — they are stored as int32_t.
 * ----------------------------------------------------------------------- */

#define FMT_AWA fmt_angle
#define FMT_TWA fmt_angle
#define FMT_TWS fmt_wind
#define FMT_STW fmt_speed
#define FMT_SOG fmt_speed
#define FMT_POLAR fmt_fixed1
#define FMT_DEPTH fmt_speed
#define FMT_COG fmt_angle_cog
#define FMT_AWS fmt_wind
#define FMT_TOP_SPEED fmt_speed
#define FMT_AVG_SPEED fmt_speed
#define FMT_TOP_WIND fmt_wind
#define FMT_AVG_WIND fmt_wind
#define FMT_DISTANCE fmt_speed
#define FMT_TIME_SAILED fmt_time
#define FMT_FUEL fmt_fixed1
#define FMT_ENGINE_TIME fmt_time

/* -----------------------------------------------------------------------
 * Storage
 * Default values are shown on screen before SignalK data arrives.
 * heel/rudder are int32_t (no string needed).
 * awa/twa store both a formatted string and a raw int for the needle.
 * ----------------------------------------------------------------------- */

#define MAX_VAR_LEN 16

static int32_t var_heel_scale = 0;
static int32_t var_rudder_scale = 0;
static int32_t var_optimum_wind_angle = 0;
static char var_apparent_wind_angle[MAX_VAR_LEN] = "000";
static int32_t var_apparent_wind_angle_raw = 0;
static char var_true_wind_angle[MAX_VAR_LEN] = "000";
static int32_t var_true_wind_angle_raw = 0;
static char var_true_wind_speed[MAX_VAR_LEN] = "0.0";
static char var_speed_through_water[MAX_VAR_LEN] = "0.00";
static char var_speed_over_ground[MAX_VAR_LEN] = "0.00";
static char var_velocity_made_good[MAX_VAR_LEN] = "0.00";
static char var_polar_performance_ratio[MAX_VAR_LEN] = "0.0";
static char var_depth[MAX_VAR_LEN] = "0.00";
static char var_course_over_ground[MAX_VAR_LEN] = "000";
static char var_apparent_wind_speed[MAX_VAR_LEN] = "0.0";
static char var_top_speed[MAX_VAR_LEN] = "0.00";
static char var_average_speed[MAX_VAR_LEN] = "0.00";
static char var_top_wind_speed[MAX_VAR_LEN] = "0.0";
static char var_average_wind_speed[MAX_VAR_LEN] = "0.0";
static char var_distance_traveled[MAX_VAR_LEN] = "0.00";
static char var_time_sailed[MAX_VAR_LEN] = "0.0";
static char var_fuel_burned[MAX_VAR_LEN] = "0.0";
static char var_engine_time[MAX_VAR_LEN] = "0.0";
static char var_boat_status[MAX_VAR_LEN] = "MOORING";

/* -----------------------------------------------------------------------
 * Formatters
 * ----------------------------------------------------------------------- */

static void fmt_angle(char *buf, float value)
{
    int v = (int)roundf(fabsf(value));
    v = fmaxf(0.0f, fminf(180.0f, v));
    snprintf(buf, MAX_VAR_LEN, "%03d", v);
}

static void fmt_angle_cog(char *buf, float value)
{
    int v = (int)roundf(value);
    v = ((v % 360) + 360) % 360; // normalisera till 0-360
    snprintf(buf, MAX_VAR_LEN, "%03d", v);
}

static void fmt_speed(char *buf, float value)
{
    float a = fabsf(value);
    a = fmaxf(0.0f, fminf(100.0f, a));
    if (a >= 10.0f)
    {
        snprintf(buf, MAX_VAR_LEN, "%.1f", a);
    }
    else
    {
        snprintf(buf, MAX_VAR_LEN, "%.2f", a);
    }
}

static void fmt_wind(char *buf, float value)
{
    value = fmaxf(0.0f, fminf(100.0f, value));
    snprintf(buf, MAX_VAR_LEN, "%.1f", fabsf(value));
}

static void fmt_time(char *buf, float value)
{
    float a = fabsf(value);
    a = fmaxf(0.0f, fminf(100.0f, a));
    if (a >= 10.0f)
    {
        snprintf(buf, MAX_VAR_LEN, "%.1f", a);
    }
    else
    {
        snprintf(buf, MAX_VAR_LEN, "%.2f", a);
    }
}

static void fmt_fixed1(char *buf, float value) {
    value = fmaxf(0.0f, fminf(999.9f, value));
    if (value >= 100.0f)
    {
        snprintf(buf, MAX_VAR_LEN, "%.0f", fabsf(value));
    } else {
        snprintf(buf, MAX_VAR_LEN, "%.1f", fabsf(value));
    }
}
// static void fmt_fixed0(char *buf, float value) { snprintf(buf, MAX_VAR_LEN, "%.0f", fabsf(value)); }
// static void fmt_fixed2(char *buf, float value) { snprintf(buf, MAX_VAR_LEN, "%.2f", fabsf(value)); }

/* -----------------------------------------------------------------------
 * Getters / Setters
 * ----------------------------------------------------------------------- */

/* Heel — int32_t, no formatting */
int32_t get_var_heel_scale_value(void) { return var_heel_scale; }
void set_var_heel_scale_value(float value) { var_heel_scale = (int32_t)roundf(value * CONV_HEEL); }

/* Rudder — int32_t, no formatting */
int32_t get_var_rudder_scale_value(void) { return var_rudder_scale; }
void set_var_rudder_scale_value(float value) { var_rudder_scale = (int32_t)roundf(value * CONV_RUDDER); }

/* OWA — int32_t, no formatting */
int32_t get_var_optimum_wind_angle_value(void) { return var_optimum_wind_angle; }
void set_var_optimum_wind_angle_value(float value) { var_optimum_wind_angle = (int32_t)roundf(value * CONV_OWA); }

/* AWA — string for label + raw int for needle */
const char *get_var_apparent_wind_angle_value(void) { return var_apparent_wind_angle; }
int32_t get_var_apparent_wind_angle_raw(void)
{
    int32_t v = var_apparent_wind_angle_raw + 90;
    // normalisera till -180 till 180
    if (v >= 180) v -= 360;
    if (v <= -180) v += 360;
    return v;
}
void set_var_apparent_wind_angle_value(float value)
{
    float converted = value * CONV_AWA;
    var_apparent_wind_angle_raw = (int32_t)roundf(converted);
    FMT_AWA(var_apparent_wind_angle, converted);
}

/* TWA — string for label + raw int for needle */
const char *get_var_true_wind_angle_value(void) { return var_true_wind_angle; }
int32_t get_var_true_wind_angle_raw(void)
{
    int32_t v = var_true_wind_angle_raw + 90;
    if (v >= 180) v -= 360;
    if (v <= -180) v += 360;
    return v;
}
void set_var_true_wind_angle_value(float value)
{
    float converted = value * CONV_TWA;
    var_true_wind_angle_raw = (int32_t)roundf(converted);
    FMT_TWA(var_true_wind_angle, converted);
}

const char *get_var_true_wind_speed_value(void) { return var_true_wind_speed; }
void set_var_true_wind_speed_value(float value) { FMT_TWS(var_true_wind_speed, value * CONV_TWS); }

const char *get_var_speed_through_water_value(void) { return var_speed_through_water; }
void set_var_speed_through_water_value(float value) { FMT_STW(var_speed_through_water, value * CONV_STW); }

const char *get_var_speed_over_ground_value(void) { return var_speed_over_ground; }
void set_var_speed_over_ground_value(float value) { FMT_SOG(var_speed_over_ground, value * CONV_SOG); }

const char *get_var_velocity_made_good_value(void) { return var_velocity_made_good; }
void set_var_velocity_made_good_value(float value) { FMT_SOG(var_velocity_made_good, value * CONV_SOG); }

const char *get_var_polar_performance_ratio_value(void) { return var_polar_performance_ratio; }
void set_var_polar_performance_ratio_value(float value) { FMT_POLAR(var_polar_performance_ratio, value * CONV_POLAR); }

const char *get_var_depth_value(void) { return var_depth; }
void set_var_depth_value(float value) { FMT_DEPTH(var_depth, value * CONV_DEPTH); }

const char *get_var_course_over_ground_value(void) { return var_course_over_ground; }
void set_var_course_over_ground_value(float value) { FMT_COG(var_course_over_ground, value * CONV_COG); }

const char *get_var_apparent_wind_speed_value(void) { return var_apparent_wind_speed; }
void set_var_apparent_wind_speed_value(float value) { FMT_AWS(var_apparent_wind_speed, value * CONV_AWS); }

const char *get_var_top_speed_value(void) { return var_top_speed; }
void set_var_top_speed_value(float value) { FMT_TOP_SPEED(var_top_speed, value * CONV_TOP_SPEED); }

const char *get_var_average_speed_value(void) { return var_average_speed; }
void set_var_average_speed_value(float value) { FMT_AVG_SPEED(var_average_speed, value * CONV_AVG_SPEED); }

const char *get_var_top_wind_speed_value(void) { return var_top_wind_speed; }
void set_var_top_wind_speed_value(float value) { FMT_TOP_WIND(var_top_wind_speed, value * CONV_TOP_WIND); }

const char *get_var_average_wind_speed_value(void) { return var_average_wind_speed; }
void set_var_average_wind_speed_value(float value) { FMT_AVG_WIND(var_average_wind_speed, value * CONV_AVG_WIND); }

const char *get_var_distance_traveled_value(void) { return var_distance_traveled; }
void set_var_distance_traveled_value(float value) { FMT_DISTANCE(var_distance_traveled, value * CONV_DISTANCE); }

const char *get_var_time_sailed_value(void) { return var_time_sailed; }
void set_var_time_sailed_value(float value) { FMT_TIME_SAILED(var_time_sailed, value * CONV_TIME_SAILED); }

const char *get_var_fuel_burned_value(void) { return var_fuel_burned; }
void set_var_fuel_burned_value(float value) { FMT_FUEL(var_fuel_burned, value * CONV_FUEL); }

const char *get_var_engine_time_value(void) { return var_engine_time; }
void set_var_engine_time_value(float value) { FMT_ENGINE_TIME(var_engine_time, value * CONV_ENGINE_TIME); }

const char *get_var_boat_status_value(void) { return var_boat_status; }
void set_var_boat_status_value(const char *value) { snprintf(var_boat_status, MAX_VAR_LEN, "%s", value); }