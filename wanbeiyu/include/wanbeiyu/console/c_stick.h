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

#include "../hal/idac.h"
#include "../hal/spst_switch.h"
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
typedef struct wanbeiyu_console_c_stick_t {
  wanbeiyu_hal_idac_t *axis1;
  wanbeiyu_hal_spst_switch_t *axis1_switch;
  wanbeiyu_hal_idac_t *axis3;
  wanbeiyu_hal_spst_switch_t *axis3_switch;
} wanbeiyu_console_c_stick_t;

static WANBEIYU_INLINE int wanbeiyu_internal_abs(int value) {
  assert(INT_MIN + 1 <= value);

  return value > 0 ? value : -value;
}

static WANBEIYU_INLINE void
wanbeiyu_console_c_stick_hold(wanbeiyu_console_c_stick_t *c_stick,
                              const wanbeiyu_c_stick_state_t *state) {
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

  assert(c_stick != NULL);
  assert(state != NULL);
  assert(-255 <= d1 && d1 <= 255);
  assert(-255 <= d3 && d3 <= 255);

  if (d1 > 0) {
    wanbeiyu_hal_idac_source(c_stick->axis1,
                             (wanbeiyu_uint8_t)wanbeiyu_internal_abs(d1));
  } else {
    wanbeiyu_hal_idac_sink(c_stick->axis1,
                           (wanbeiyu_uint8_t)wanbeiyu_internal_abs(d1));
  }
  if (d1 == 0 && x == y) {
    wanbeiyu_hal_spst_switch_open(c_stick->axis1_switch);
  } else {
    wanbeiyu_hal_spst_switch_close(c_stick->axis1_switch);
  }

  if (d3 > 0) {
    wanbeiyu_hal_idac_source(c_stick->axis3,
                             (wanbeiyu_uint8_t)wanbeiyu_internal_abs(d3));
  } else {
    wanbeiyu_hal_idac_sink(c_stick->axis3,
                           (wanbeiyu_uint8_t)wanbeiyu_internal_abs(d3));
  }
  if (d3 == 0 && 255 - x == y) {
    wanbeiyu_hal_spst_switch_open(c_stick->axis3_switch);
  } else {
    wanbeiyu_hal_spst_switch_close(c_stick->axis3_switch);
  }
}

static WANBEIYU_INLINE void
wanbeiyu_console_c_stick_release(wanbeiyu_console_c_stick_t *c_stick) {
  assert(c_stick != NULL);

  wanbeiyu_hal_spst_switch_open(c_stick->axis1_switch);
  wanbeiyu_hal_spst_switch_open(c_stick->axis3_switch);
}

static WANBEIYU_INLINE void wanbeiyu_console_c_stick_init(
    wanbeiyu_console_c_stick_t *c_stick, wanbeiyu_hal_idac_t *axis1,
    wanbeiyu_hal_spst_switch_t *axis1_switch, wanbeiyu_hal_idac_t *axis3,
    wanbeiyu_hal_spst_switch_t *axis3_switch) {
  assert(c_stick != NULL);
  assert(axis1 != NULL);
  assert(axis1_switch != NULL);
  assert(axis3 != NULL);
  assert(axis3_switch != NULL);

  c_stick->axis1 = axis1;
  c_stick->axis1_switch = axis1_switch;
  c_stick->axis3 = axis3;
  c_stick->axis3_switch = axis3_switch;

  (void)wanbeiyu_console_c_stick_hold;
  (void)wanbeiyu_console_c_stick_release;
}

#ifdef __cplusplus
}
#endif

#endif /* WANBEIYU_CONSOLE_C_STICK_H */