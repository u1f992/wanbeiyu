/*
 * Copyright (C) 2025  Koutaro Mukai
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef WANBEIYU_CONSOLE_C_STICK_H
#define WANBEIYU_CONSOLE_C_STICK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../hal.h"
#include "state.h"

/**
 *   1+         3+
 *     \_     _/
 *       \_ _/
 *        _X_
 *      _/   \_
 *     /       \
 *   3-         1-
 * +: source, -: sink
 *
 * (Pin numbers of Hirose FH33-4S-1SH(10))
 */

extern void wanbeiyu_hal_c_stick_positive_slope_set(wanbeiyu_hal_idac_mode_t,
                                                    wanbeiyu_uint8_t);
extern void wanbeiyu_hal_c_stick_positive_slope_switch_set(
    wanbeiyu_hal_spst_switch_state_t);
extern void wanbeiyu_hal_c_stick_negative_slope_set(wanbeiyu_hal_idac_mode_t,
                                                    wanbeiyu_uint8_t);
extern void wanbeiyu_hal_c_stick_negative_slope_switch_set(
    wanbeiyu_hal_spst_switch_state_t);

static WANBEIYU_INLINE int wanbeiyu_internal_abs(int value) {
  assert(INT_MIN + 1 <= value);

  return value > 0 ? value : -value;
}

static WANBEIYU_INLINE void
wanbeiyu_console_c_stick_set(const wanbeiyu_c_stick_state_t *state) {
  /*
   * d1 = signed_distance_to(y=x) / DISTANCE_MAX * UINT8_MAX
   * d3 = signed_distance_to(y=-x+255) / DISTANCE_MAX * UINT8_MAX
   *
   * signed_distance_to(y=ax+b) (-a*x+y-b)/sqrt(a^2+1)
   * positive=above, negative=below
   * While a=1,-1 thus sqrt(a^2+1) is always sqrt(2).
   *
   * DISTANCE_MAX=UINT8_MAX/2*sqrt(2)
   *
   * ((-a*x+y-b)/sqrt(2)) / (UINT8_MAX/2*sqrt(2)) * UINT8_MAX
   * = -a*x+y-b
   */
  wanbeiyu_uint8_t x = state->x != NULL ? *(state->x) : 0x80;
  wanbeiyu_uint8_t y = state->y != NULL ? *(state->y) : 0x80;
  int d1 = -x + y;
  int d3 = x + y - 255;

  assert(state != NULL);
  assert(-255 <= d1 && d1 <= 255);
  assert(-255 <= d3 && d3 <= 255);

  if (d1 > 0) {
    wanbeiyu_hal_c_stick_negative_slope_set(
        WANBEIYU_HAL_IDAC_SOURCE, (wanbeiyu_uint8_t)wanbeiyu_internal_abs(d1));
  } else {
    wanbeiyu_hal_c_stick_negative_slope_set(
        WANBEIYU_HAL_IDAC_SINK, (wanbeiyu_uint8_t)wanbeiyu_internal_abs(d1));
  }
  if (d1 == 0 && x == y) {
    wanbeiyu_hal_c_stick_negative_slope_switch_set(
        WANBEIYU_HAL_SPST_SWITCH_OPEN);
  } else {
    wanbeiyu_hal_c_stick_negative_slope_switch_set(
        WANBEIYU_HAL_SPST_SWITCH_CLOSE);
  }

  if (d3 > 0) {
    wanbeiyu_hal_c_stick_positive_slope_set(
        WANBEIYU_HAL_IDAC_SOURCE, (wanbeiyu_uint8_t)wanbeiyu_internal_abs(d3));
  } else {
    wanbeiyu_hal_c_stick_positive_slope_set(
        WANBEIYU_HAL_IDAC_SINK, (wanbeiyu_uint8_t)wanbeiyu_internal_abs(d3));
  }
  if (d3 == 0 && 255 - x == y) {
    wanbeiyu_hal_c_stick_positive_slope_switch_set(
        WANBEIYU_HAL_SPST_SWITCH_OPEN);
  } else {
    wanbeiyu_hal_c_stick_positive_slope_switch_set(
        WANBEIYU_HAL_SPST_SWITCH_CLOSE);
  }
}

#ifdef __cplusplus
}
#endif

#endif /* WANBEIYU_CONSOLE_C_STICK_H */