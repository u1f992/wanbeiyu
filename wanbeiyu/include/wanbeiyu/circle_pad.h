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

#ifndef WANBEIYU_CIRCLE_PAD_H
#define WANBEIYU_CIRCLE_PAD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "hal.h"
#include "helper.h"
#include "state.h"

extern void wanbeiyu_hal_idac_circle_pad_pin_2_set(wanbeiyu_hal_idac_mode_t,
                                                   wanbeiyu_uint8_t);
extern void wanbeiyu_hal_spst_switch_circle_pad_pin_2_set(
    wanbeiyu_hal_spst_switch_state_t);
extern void wanbeiyu_hal_idac_circle_pad_pin_4_set(wanbeiyu_hal_idac_mode_t,
                                                   wanbeiyu_uint8_t);
extern void wanbeiyu_hal_spst_switch_circle_pad_pin_4_set(
    wanbeiyu_hal_spst_switch_state_t);

/**
 *   ^ 1v8
 *   |
 *   o-------------o
 *   |             |
 *   |            .-.
 *   |            | |<-- Y
 *   |            '-'
 *   |     ___     |
 *   o----|___|----o
 *          ^      |
 *          |      v GND
 *          X
 *
 *           4+
 *           |
 *           |
 *  2+ ------+------ 2-
 *           |
 *           |
 *           4-
 * +: source, -: sink
 *
 * 1: GND; 2: X; 3: 1v8; 4: Y
 * (Pin numbers of Molex 5014610491)
 */
static WANBEIYU_INLINE void
wanbeiyu_circle_pad_set(const wanbeiyu_state_t *state) {
  const wanbeiyu_circle_pad_state_t *circle_pad;
  assert(state != NULL);
  circle_pad = &(state->circle_pad);

  if (circle_pad->x != NULL) {
    if (*(circle_pad->x) < 128) {
      wanbeiyu_hal_idac_circle_pad_pin_2_set(
          WANBEIYU_HAL_IDAC_SOURCE,
          wanbeiyu_helper_map_127_to_255(127 - *(circle_pad->x)));
    } else {
      wanbeiyu_hal_idac_circle_pad_pin_2_set(
          WANBEIYU_HAL_IDAC_SINK,
          wanbeiyu_helper_map_127_to_255(*(circle_pad->x) - 128));
    }
    wanbeiyu_hal_spst_switch_circle_pad_pin_2_set(
        WANBEIYU_HAL_SPST_SWITCH_CLOSE);
  } else {
    wanbeiyu_hal_spst_switch_circle_pad_pin_2_set(
        WANBEIYU_HAL_SPST_SWITCH_OPEN);
  }

  if (circle_pad->y != NULL) {
    if (*(circle_pad->y) < 128) {
      wanbeiyu_hal_idac_circle_pad_pin_4_set(
          WANBEIYU_HAL_IDAC_SINK,
          wanbeiyu_helper_map_127_to_255(127 - *(circle_pad->y)));
    } else {
      wanbeiyu_hal_idac_circle_pad_pin_4_set(
          WANBEIYU_HAL_IDAC_SOURCE,
          wanbeiyu_helper_map_127_to_255(*(circle_pad->y) - 128));
    }
    wanbeiyu_hal_spst_switch_circle_pad_pin_4_set(
        WANBEIYU_HAL_SPST_SWITCH_CLOSE);
  } else {
    wanbeiyu_hal_spst_switch_circle_pad_pin_4_set(
        WANBEIYU_HAL_SPST_SWITCH_OPEN);
  }
}

#ifdef __cplusplus
}
#endif

#endif /* WANBEIYU_CIRCLE_PAD_H */