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

#ifndef WANBEIYU_CONSOLE_CIRCLE_PAD_H
#define WANBEIYU_CONSOLE_CIRCLE_PAD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../hal.h"
#include "state.h"

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

extern void wanbeiyu_hal_circle_pad_horizontal_set(wanbeiyu_hal_idac_mode_t,
                                                   wanbeiyu_uint8_t);
extern void wanbeiyu_hal_circle_pad_horizontal_switch_set(
    wanbeiyu_hal_spst_switch_state_t);
extern void wanbeiyu_hal_circle_pad_vertical_set(wanbeiyu_hal_idac_mode_t,
                                                 wanbeiyu_uint8_t);
extern void wanbeiyu_hal_circle_pad_vertical_switch_set(
    wanbeiyu_hal_spst_switch_state_t);

static WANBEIYU_INLINE wanbeiyu_uint8_t
wanbeiyu_internal_map_127_to_255(wanbeiyu_uint8_t value) {
  assert(value <= 127);

  return (value * 255) / 127;
}

static WANBEIYU_INLINE void
wanbeiyu_console_circle_pad_set(const wanbeiyu_circle_pad_state_t *state) {
  assert(state != NULL);

  if (state->x != NULL) {
    if (*(state->x) < 128) {
      wanbeiyu_hal_circle_pad_horizontal_set(
          WANBEIYU_HAL_IDAC_SOURCE,
          wanbeiyu_internal_map_127_to_255(127 - *(state->x)));
    } else {
      wanbeiyu_hal_circle_pad_horizontal_set(
          WANBEIYU_HAL_IDAC_SINK,
          wanbeiyu_internal_map_127_to_255(*(state->x) - 128));
    }
    wanbeiyu_hal_circle_pad_horizontal_switch_set(
        WANBEIYU_HAL_SPST_SWITCH_CLOSE);
  } else {
    wanbeiyu_hal_circle_pad_horizontal_switch_set(
        WANBEIYU_HAL_SPST_SWITCH_OPEN);
  }

  if (state->y != NULL) {
    if (*(state->y) < 128) {
      wanbeiyu_hal_circle_pad_vertical_set(
          WANBEIYU_HAL_IDAC_SINK,
          wanbeiyu_internal_map_127_to_255(127 - *(state->y)));
    } else {
      wanbeiyu_hal_circle_pad_vertical_set(
          WANBEIYU_HAL_IDAC_SOURCE,
          wanbeiyu_internal_map_127_to_255(*(state->y) - 128));
    }
    wanbeiyu_hal_circle_pad_vertical_switch_set(WANBEIYU_HAL_SPST_SWITCH_CLOSE);
  } else {
    wanbeiyu_hal_circle_pad_vertical_switch_set(WANBEIYU_HAL_SPST_SWITCH_OPEN);
  }
}

#ifdef __cplusplus
}
#endif

#endif /* WANBEIYU_CONSOLE_CIRCLE_PAD_H */