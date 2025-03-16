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

typedef struct wanbeiyu_console_t {
  wanbeiyu_console_button_t power;
  wanbeiyu_console_button_t home;
  wanbeiyu_console_button_t zr;
  wanbeiyu_console_button_t zl;
  wanbeiyu_console_button_t y;
  wanbeiyu_console_button_t x;
  wanbeiyu_console_button_t l;
  wanbeiyu_console_button_t r;
  wanbeiyu_console_button_t down;
  wanbeiyu_console_button_t up;
  wanbeiyu_console_button_t left;
  wanbeiyu_console_button_t right;
  wanbeiyu_console_button_t start;
  wanbeiyu_console_button_t select;
  wanbeiyu_console_button_t b;
  wanbeiyu_console_button_t a;
  wanbeiyu_console_touch_screen_t touch_screen;
  wanbeiyu_console_c_stick_t c_stick;
  wanbeiyu_console_circle_pad_t circle_pad;
} wanbeiyu_console_t;

static WANBEIYU_INLINE void wanbeiyu_console_init(wanbeiyu_console_t *console,
                                                  wanbeiyu_hal_t *hal) {
  assert(console != NULL);
  assert(hal != NULL);

  wanbeiyu_console_button_init(&(console->power), hal->power);
  wanbeiyu_console_button_init(&(console->home), hal->home);
  wanbeiyu_console_button_init(&(console->zr), hal->zr);
  wanbeiyu_console_button_init(&(console->zl), hal->zl);
  wanbeiyu_console_button_init(&(console->y), hal->y);
  wanbeiyu_console_button_init(&(console->x), hal->x);
  wanbeiyu_console_button_init(&(console->l), hal->l);
  wanbeiyu_console_button_init(&(console->r), hal->r);
  wanbeiyu_console_button_init(&(console->down), hal->down);
  wanbeiyu_console_button_init(&(console->up), hal->up);
  wanbeiyu_console_button_init(&(console->left), hal->left);
  wanbeiyu_console_button_init(&(console->right), hal->right);
  wanbeiyu_console_button_init(&(console->start), hal->start);
  wanbeiyu_console_button_init(&(console->select), hal->select);
  wanbeiyu_console_button_init(&(console->b), hal->b);
  wanbeiyu_console_button_init(&(console->a), hal->a);
  wanbeiyu_console_touch_screen_init(
      &(console->touch_screen), hal->touch_screen.horizontal,
      hal->touch_screen.vertical, hal->touch_screen.switch_);
  wanbeiyu_console_c_stick_init(&(console->c_stick), hal->c_stick.axis1,
                                hal->c_stick.axis1_switch, hal->c_stick.axis3,
                                hal->c_stick.axis3_switch);
  wanbeiyu_console_circle_pad_init(
      &(console->circle_pad), hal->circle_pad.horizontal,
      hal->circle_pad.horizontal_switch, hal->circle_pad.vertical,
      hal->circle_pad.vertical_switch);
}

static WANBEIYU_INLINE void
wanbeiyu_console_set(wanbeiyu_console_t *console,
                     const wanbeiyu_console_state_t *state) {
  assert(console != NULL);
  assert(state != NULL);

  (state->power ? wanbeiyu_console_button_hold
                : wanbeiyu_console_button_release)(&(console->power));
  (state->home ? wanbeiyu_console_button_hold
               : wanbeiyu_console_button_release)(&(console->home));
  (state->zr ? wanbeiyu_console_button_hold
             : wanbeiyu_console_button_release)(&(console->zr));
  (state->zl ? wanbeiyu_console_button_hold
             : wanbeiyu_console_button_release)(&(console->zl));
  (state->y ? wanbeiyu_console_button_hold
            : wanbeiyu_console_button_release)(&(console->y));
  (state->x ? wanbeiyu_console_button_hold
            : wanbeiyu_console_button_release)(&(console->x));
  (state->l ? wanbeiyu_console_button_hold
            : wanbeiyu_console_button_release)(&(console->l));
  (state->r ? wanbeiyu_console_button_hold
            : wanbeiyu_console_button_release)(&(console->r));
  (state->down ? wanbeiyu_console_button_hold
               : wanbeiyu_console_button_release)(&(console->down));
  (state->up ? wanbeiyu_console_button_hold
             : wanbeiyu_console_button_release)(&(console->up));
  (state->left ? wanbeiyu_console_button_hold
               : wanbeiyu_console_button_release)(&(console->left));
  (state->right ? wanbeiyu_console_button_hold
                : wanbeiyu_console_button_release)(&(console->right));
  (state->start ? wanbeiyu_console_button_hold
                : wanbeiyu_console_button_release)(&(console->start));
  (state->select ? wanbeiyu_console_button_hold
                 : wanbeiyu_console_button_release)(&(console->select));
  (state->b ? wanbeiyu_console_button_hold
            : wanbeiyu_console_button_release)(&(console->b));
  (state->a ? wanbeiyu_console_button_hold
            : wanbeiyu_console_button_release)(&(console->a));

  if (state->touch_screen != NULL) {
    wanbeiyu_console_touch_screen_hold(&(console->touch_screen),
                                       state->touch_screen);
  } else {
    wanbeiyu_console_touch_screen_release(&(console->touch_screen));
  }

  wanbeiyu_console_c_stick_hold(&(console->c_stick), &(state->c_stick));
  wanbeiyu_console_circle_pad_hold(&(console->circle_pad),
                                   &(state->circle_pad));
}

#ifdef __cplusplus
}
#endif

#endif /* WANBEIYU_CONSOLE_H */