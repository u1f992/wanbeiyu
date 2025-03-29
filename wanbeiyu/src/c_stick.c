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

#include <wanbeiyu/c_stick.h>

void wanbeiyu_hal_idac_c_stick_pin_1_set(wanbeiyu_hal_idac_mode_t,
                                         wanbeiyu_uint8_t);
void wanbeiyu_hal_spst_switch_c_stick_pin_1_set(
    wanbeiyu_hal_spst_switch_state_t);
void wanbeiyu_hal_idac_c_stick_pin_3_set(wanbeiyu_hal_idac_mode_t,
                                         wanbeiyu_uint8_t);
void wanbeiyu_hal_spst_switch_c_stick_pin_3_set(
    wanbeiyu_hal_spst_switch_state_t);

#define map_127_to_254(x) ((x) * 2)

void wanbeiyu_c_stick_set(wanbeiyu_state_t const *state) {
  const wanbeiyu_c_stick_state_t *c_stick;

  assert(state != NULL);

  c_stick = &(state->c_stick);

  if (c_stick->x == NULL && c_stick->y == NULL) {
    wanbeiyu_hal_spst_switch_c_stick_pin_1_set(WANBEIYU_HAL_SPST_SWITCH_OPEN);
    wanbeiyu_hal_spst_switch_c_stick_pin_3_set(WANBEIYU_HAL_SPST_SWITCH_OPEN);

  } else if (c_stick->x != NULL && c_stick->y != NULL) {
    wanbeiyu_uint8_t x = *(c_stick->x);
    wanbeiyu_uint8_t y = *(c_stick->y);

    if (y == x) {
      wanbeiyu_hal_spst_switch_c_stick_pin_1_set(WANBEIYU_HAL_SPST_SWITCH_OPEN);
      if (x < 128) {
        wanbeiyu_hal_idac_c_stick_pin_3_set(WANBEIYU_HAL_IDAC_SINK,
                                            255 - map_127_to_254(x));
      } else {
        wanbeiyu_hal_idac_c_stick_pin_3_set(WANBEIYU_HAL_IDAC_SOURCE,
                                            1 + map_127_to_254(x - 128));
      }
      wanbeiyu_hal_spst_switch_c_stick_pin_3_set(
          WANBEIYU_HAL_SPST_SWITCH_CLOSE);

    } else if (y == 255 - x) {
      wanbeiyu_hal_spst_switch_c_stick_pin_3_set(WANBEIYU_HAL_SPST_SWITCH_OPEN);
      if (x < 128) {
        wanbeiyu_hal_idac_c_stick_pin_1_set(WANBEIYU_HAL_IDAC_SOURCE,
                                            255 - map_127_to_254(x));
      } else {
        wanbeiyu_hal_idac_c_stick_pin_1_set(WANBEIYU_HAL_IDAC_SINK,
                                            1 + map_127_to_254(x - 128));
      }
      wanbeiyu_hal_spst_switch_c_stick_pin_1_set(
          WANBEIYU_HAL_SPST_SWITCH_CLOSE);

    } else {
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
      int d1 = -x + y;
      int d3 = x + y - 255;
      assert(-255 <= d1 && d1 <= 255);
      assert(-255 <= d3 && d3 <= 255);

      wanbeiyu_hal_idac_c_stick_pin_1_set(
          d1 > 0 ? WANBEIYU_HAL_IDAC_SOURCE : WANBEIYU_HAL_IDAC_SINK,
          (wanbeiyu_uint8_t)wanbeiyu_helper_abs(d1));
      wanbeiyu_hal_spst_switch_c_stick_pin_1_set(
          WANBEIYU_HAL_SPST_SWITCH_CLOSE);

      wanbeiyu_hal_idac_c_stick_pin_3_set(
          d3 > 0 ? WANBEIYU_HAL_IDAC_SOURCE : WANBEIYU_HAL_IDAC_SINK,
          (wanbeiyu_uint8_t)wanbeiyu_helper_abs(d3));
      wanbeiyu_hal_spst_switch_c_stick_pin_3_set(
          WANBEIYU_HAL_SPST_SWITCH_CLOSE);
    }
  } else {
    wanbeiyu_uint8_t value;
    if (c_stick->x == NULL) {
      assert(c_stick->y != NULL);
      value = *(c_stick->y);

      if (value < 128) {
        wanbeiyu_hal_idac_c_stick_pin_1_set(WANBEIYU_HAL_IDAC_SINK,
                                            127 - value);
      } else {
        wanbeiyu_hal_idac_c_stick_pin_1_set(WANBEIYU_HAL_IDAC_SOURCE,
                                            value - 128);
      }
      wanbeiyu_hal_spst_switch_c_stick_pin_1_set(
          WANBEIYU_HAL_SPST_SWITCH_CLOSE);

      if (value < 128) {
        wanbeiyu_hal_idac_c_stick_pin_3_set(WANBEIYU_HAL_IDAC_SINK,
                                            127 - value);
      } else {
        wanbeiyu_hal_idac_c_stick_pin_3_set(WANBEIYU_HAL_IDAC_SOURCE,
                                            value - 128);
      }
      wanbeiyu_hal_spst_switch_c_stick_pin_3_set(
          WANBEIYU_HAL_SPST_SWITCH_CLOSE);

    } else {
      assert(c_stick->y == NULL);
      value = *(c_stick->x);

      if (value < 128) {
        wanbeiyu_hal_idac_c_stick_pin_1_set(WANBEIYU_HAL_IDAC_SOURCE,
                                            127 - value);
      } else {
        wanbeiyu_hal_idac_c_stick_pin_1_set(WANBEIYU_HAL_IDAC_SINK,
                                            value - 128);
      }
      wanbeiyu_hal_spst_switch_c_stick_pin_1_set(
          WANBEIYU_HAL_SPST_SWITCH_CLOSE);

      if (value < 128) {
        wanbeiyu_hal_idac_c_stick_pin_3_set(WANBEIYU_HAL_IDAC_SINK,
                                            127 - value);
      } else {
        wanbeiyu_hal_idac_c_stick_pin_3_set(WANBEIYU_HAL_IDAC_SOURCE,
                                            value - 128);
      }
      wanbeiyu_hal_spst_switch_c_stick_pin_3_set(
          WANBEIYU_HAL_SPST_SWITCH_CLOSE);
    }
  }
}