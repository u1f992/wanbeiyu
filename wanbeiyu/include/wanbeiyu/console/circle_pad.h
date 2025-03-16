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

#include "../hal/idac.h"
#include "../hal/spst_switch.h"
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
typedef struct wanbeiyu_console_circle_pad_t {
  wanbeiyu_hal_idac_t *horizontal;
  wanbeiyu_hal_spst_switch_t *horizontal_switch;
  wanbeiyu_hal_idac_t *vertical;
  wanbeiyu_hal_spst_switch_t *vertical_switch;
} wanbeiyu_console_circle_pad_t;

static WANBEIYU_INLINE wanbeiyu_uint8_t
wanbeiyu_internal_map_127_to_255(wanbeiyu_uint8_t value) {
  assert(value <= 127);

  return (value * 255) / 127;
}

static WANBEIYU_INLINE void
wanbeiyu_console_circle_pad_hold(wanbeiyu_console_circle_pad_t *circle_pad,
                                 const wanbeiyu_circle_pad_state_t *state) {
  assert(circle_pad != NULL);
  assert(state != NULL);

  if (state->x != NULL) {
    if (*(state->x) < 128) {
      wanbeiyu_hal_idac_source(
          circle_pad->horizontal,
          wanbeiyu_internal_map_127_to_255(127 - *(state->x)));
    } else {
      wanbeiyu_hal_idac_sink(
          circle_pad->horizontal,
          wanbeiyu_internal_map_127_to_255(*(state->x) - 128));
    }
    wanbeiyu_hal_spst_switch_close(circle_pad->horizontal_switch);
  } else {
    wanbeiyu_hal_spst_switch_open(circle_pad->horizontal_switch);
  }

  if (state->y != NULL) {
    if (*(state->y) < 128) {
      wanbeiyu_hal_idac_sink(
          circle_pad->vertical,
          wanbeiyu_internal_map_127_to_255(127 - *(state->y)));
    } else {
      wanbeiyu_hal_idac_source(
          circle_pad->vertical,
          wanbeiyu_internal_map_127_to_255(*(state->y) - 128));
    }
    wanbeiyu_hal_spst_switch_close(circle_pad->vertical_switch);
  } else {
    wanbeiyu_hal_spst_switch_open(circle_pad->vertical_switch);
  }
}

static WANBEIYU_INLINE void
wanbeiyu_console_circle_pad_release(wanbeiyu_console_circle_pad_t *circle_pad) {
  assert(circle_pad != NULL);

  wanbeiyu_hal_spst_switch_open(circle_pad->horizontal_switch);
  wanbeiyu_hal_spst_switch_open(circle_pad->vertical_switch);
}

static WANBEIYU_INLINE void
wanbeiyu_console_circle_pad_init(wanbeiyu_console_circle_pad_t *circle_pad,
                                 wanbeiyu_hal_idac_t *horizontal,
                                 wanbeiyu_hal_spst_switch_t *horizontal_switch,
                                 wanbeiyu_hal_idac_t *vertical,
                                 wanbeiyu_hal_spst_switch_t *vertical_switch) {
  assert(circle_pad != NULL);
  assert(horizontal != NULL);
  assert(horizontal_switch != NULL);
  assert(vertical != NULL);
  assert(vertical_switch != NULL);

  circle_pad->horizontal = horizontal;
  circle_pad->horizontal_switch = horizontal_switch;
  circle_pad->vertical = vertical;
  circle_pad->vertical_switch = vertical_switch;

  (void)wanbeiyu_console_circle_pad_hold;
  (void)wanbeiyu_console_circle_pad_release;
}

#ifdef __cplusplus
}
#endif

#endif /* WANBEIYU_CONSOLE_CIRCLE_PAD_H */