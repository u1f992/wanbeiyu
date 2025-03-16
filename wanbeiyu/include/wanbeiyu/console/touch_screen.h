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

#include "../hal/rdac_240_steps.h"
#include "../hal/rdac_320_steps.h"
#include "../hal/spst_switch.h"
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
typedef struct wanbeiyu_console_touch_screen_t {
  wanbeiyu_hal_rdac_320_steps_t *horizontal;
  wanbeiyu_hal_rdac_240_steps_t *vertical;
  wanbeiyu_hal_spst_switch_t *switch_;
} wanbeiyu_console_touch_screen_t;

static WANBEIYU_INLINE void wanbeiyu_console_touch_screen_init(
    wanbeiyu_console_touch_screen_t *touch_screen,
    wanbeiyu_hal_rdac_320_steps_t *horizontal,
    wanbeiyu_hal_rdac_240_steps_t *vertical,
    wanbeiyu_hal_spst_switch_t *switch_) {
  assert(touch_screen != NULL);
  assert(horizontal != NULL);
  assert(vertical != NULL);
  assert(switch_ != NULL);

  touch_screen->horizontal = horizontal;
  touch_screen->vertical = vertical;
  touch_screen->switch_ = switch_;
}

static WANBEIYU_INLINE void wanbeiyu_console_touch_screen_release(
    wanbeiyu_console_touch_screen_t *touch_screen) {
  assert(touch_screen != NULL);

  wanbeiyu_hal_spst_switch_open(touch_screen->switch_);
}

static WANBEIYU_INLINE void wanbeiyu_console_touch_screen_hold(
    wanbeiyu_console_touch_screen_t *touch_screen,
    const wanbeiyu_touch_screen_state_t *state) {
  assert(touch_screen != NULL);
  assert(state != NULL);

  wanbeiyu_hal_rdac_320_steps_set_wiper_position(
      touch_screen->horizontal, state->x < 320 ? state->x : 319);
  wanbeiyu_hal_rdac_240_steps_set_wiper_position(
      touch_screen->vertical, state->y < 240 ? state->y : 239);
  wanbeiyu_hal_spst_switch_close(touch_screen->switch_);
}

#ifdef __cplusplus
}
#endif

#endif /* WANBEIYU_CONSOLE_TOUCH_SCREEN_H */