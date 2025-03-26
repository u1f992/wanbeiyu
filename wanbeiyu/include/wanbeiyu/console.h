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

#ifndef WANBEIYU_CONSOLE_H
#define WANBEIYU_CONSOLE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "console/button.h"
#include "console/c_stick.h"
#include "console/circle_pad.h"
#include "console/state.h"
#include "console/touch_screen.h"
#include "hal.h"

static WANBEIYU_INLINE void
wanbeiyu_console_set(const wanbeiyu_console_state_t *state) {
  assert(state != NULL);

  wanbeiyu_console_buttons_set(state->buttons);
  wanbeiyu_console_touch_screen_set(state->touch_screen);
  wanbeiyu_console_c_stick_set(&(state->c_stick));
  wanbeiyu_console_circle_pad_set(&(state->circle_pad));
}

#ifdef __cplusplus
}
#endif

#endif /* WANBEIYU_CONSOLE_H */