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

#ifndef WANBEIYU_CONSOLE_TOUCH_SCREEN_H
#define WANBEIYU_CONSOLE_TOUCH_SCREEN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../hal.h"
#include "state.h"

/**
 *   | Y_{B}
 *  .-.     _|_
 *  | |<----o o-.
 *  '-'         |
 *   | Y_{A}    |
 *             _v_
 *        ----|___|----
 *      X_{B}       X_{A}
 *
 * 1: Y_{A}; 2: X_{B}; 3: Y_{B}; 4: X_{A}
 * (Pin numbers of Molex 5014610491)
 */

extern void wanbeiyu_hal_touch_screen_horizontal_set(wanbeiyu_uint16_t);
extern void wanbeiyu_hal_touch_screen_vertical_set(wanbeiyu_uint8_t);
extern void
    wanbeiyu_hal_touch_screen_switch_set(wanbeiyu_hal_spst_switch_state_t);

static WANBEIYU_INLINE void
wanbeiyu_console_touch_screen_set(const wanbeiyu_touch_screen_state_t *state) {
  if (state == NULL) {
    wanbeiyu_hal_touch_screen_switch_set(WANBEIYU_HAL_SPST_SWITCH_OPEN);
  } else {
    wanbeiyu_hal_touch_screen_horizontal_set(state->x < 320 ? state->x : 319);
    wanbeiyu_hal_touch_screen_vertical_set(state->y < 240 ? state->y : 239);
    wanbeiyu_hal_touch_screen_switch_set(WANBEIYU_HAL_SPST_SWITCH_CLOSE);
  }
}

#ifdef __cplusplus
}
#endif

#endif /* WANBEIYU_CONSOLE_TOUCH_SCREEN_H */