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

#ifndef WANBEIYU_CONSOLE_STATE_H
#define WANBEIYU_CONSOLE_STATE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../compat.h"

/* clang-format off */
/*
 * This order is derived from devkitPro, and originally comes from the
 * representation in memory on the actual console.
 *
 * According to devkitPro and Citra, the console internally uses a range of -156
 * to 156 for the C Stick and -154 to 154 for the Circle Pad. The up-right
 * direction is considered positive, with the center at (0,0). These values
 * apply to the uncalibrated case; the actual range may vary depending on
 * calibration.
 *
 * - https://github.com/devkitPro/libctru/blob/1bafb08f347226fba439d14c7bb1f44e85d70978/libctru/include/3ds/services/hid.h#L10-L41
 * - http://3dbrew.org/wiki/HID_Shared_Memory
 *
 * | Byte | Bit | Description    |
 * | ---- | --- | -------------- |
 * |  0   |  7  | Power          | 0=release, 1=hold
 * |      |  6  | Home           |
 * |      |  5  | ZR             |
 * |      |  4  | ZL             |
 * |      |  3  | Y              |
 * |      |  2  | X              |
 * |      |  1  | L              |
 * |      |  0  | R              |
 * | ~~~~ | ~~~ | ~~~~~~~~~~~~~~ |
 * |  1   |  7  | Down           |
 * |      |  6  | Up             |
 * |      |  5  | Left           |
 * |      |  4  | Right          |
 * |      |  3  | Start          |
 * |      |  2  | Select         |
 * |      |  1  | B              |
 * |      |  0  | A              |
 * | ~~~~ | ~~~ | ~~~~~~~~~~~~~~ |
 * |  2   |  7  | Touch Screen   |
 * |      |  6  | C Stick X      |
 * |      |  5  | C Stick Y      |
 * |      |  4  | Circle Pad X   |
 * |      |  3  | Circle Pad Y   |
 * |      |  2  | (Reserved)     |
 * |      |  1  | (Reserved)     |
 * |      |  0  | \              |
 * | ~~~~ | ~~~ | ~\~~~~~~~~~~~~ |
 * |  3   |  7  |                |
 * |      |  6  | Touch Screen X |
 * |      |  5  |                |
 * |      |  4  | left-to-right, |
 * |      |  3  | clamped to 319 |
 * |      |  2  |                |
 * |      |  1  |  /             |
 * |      |  0  | /              |
 * | ~~~~ | ~~~ | ~~~~~~~~~~~~~~ |
 * |  4   |  7  | \              |
 * |      |  6  |                |
 * |      |  5  | Touch Screen Y |
 * |      |  4  |                |
 * |      |  3  | top-to-bottom, |
 * |      |  2  | clamped to 239 |
 * |      |  1  |                |
 * |      |  0  | /              |
 * | ~~~~ | ~~~ | ~~~~~~~~~~~~~~ |
 * |  5   |  7  | \              |
 * |      |  6  |                |
 * |      |  5  | C Stick X      |
 * |      |  4  |                |
 * |      |  3  | left-to-right  |
 * |      |  2  |                |
 * |      |  1  |  /             |
 * |      |  0  | /              |
 * | ~~~~ | ~~~ | ~~~~~~~~~~~~~~ |
 * |  6   |  7  | \              |
 * |      |  6  |                |
 * |      |  5  | C Stick Y      |
 * |      |  4  |                |
 * |      |  3  | bottom-to-top  |
 * |      |  2  |                |
 * |      |  1  |  /             |
 * |      |  0  | /              |
 * | ~~~~ | ~~~ | ~~~~~~~~~~~~~~ |
 * |  7   |  7  | \              |
 * |      |  6  |                |
 * |      |  5  | Circle Pad X   |
 * |      |  4  |                |
 * |      |  3  | left-to-right  |
 * |      |  2  |                |
 * |      |  1  |  /             |
 * |      |  0  | /              |
 * | ~~~~ | ~~~ | ~~~~~~~~~~~~~~ |
 * |  8   |  7  | \              |
 * |      |  6  |                |
 * |      |  5  | Circle Pad Y   |
 * |      |  4  |                |
 * |      |  3  | bottom-to-top  |
 * |      |  2  |                |
 * |      |  1  |  /             |
 * |      |  0  | /              |
 */
/* clang-format on */

typedef struct wanbeiyu_touch_screen_state_t {
  wanbeiyu_uint16_t x;
  wanbeiyu_uint8_t y;
} wanbeiyu_touch_screen_state_t;

typedef struct wanbeiyu_c_stick_state_t {
  wanbeiyu_uint8_t *x;
  wanbeiyu_uint8_t *y;
} wanbeiyu_c_stick_state_t;

typedef wanbeiyu_c_stick_state_t wanbeiyu_circle_pad_state_t;

typedef struct wanbeiyu_console_state_t {
  wanbeiyu_bool_t power;
  wanbeiyu_bool_t home;
  wanbeiyu_bool_t zr;
  wanbeiyu_bool_t zl;
  wanbeiyu_bool_t y;
  wanbeiyu_bool_t x;
  wanbeiyu_bool_t l;
  wanbeiyu_bool_t r;

  wanbeiyu_bool_t down;
  wanbeiyu_bool_t up;
  wanbeiyu_bool_t left;
  wanbeiyu_bool_t right;
  wanbeiyu_bool_t start;
  wanbeiyu_bool_t select;
  wanbeiyu_bool_t b;
  wanbeiyu_bool_t a;

  wanbeiyu_touch_screen_state_t *touch_screen;
  wanbeiyu_c_stick_state_t c_stick;
  wanbeiyu_circle_pad_state_t circle_pad;
  wanbeiyu_bool_t reserved_0;
  wanbeiyu_bool_t reserved_1;

  wanbeiyu_touch_screen_state_t touch_screen_state;
  struct {
    wanbeiyu_uint8_t x;
    wanbeiyu_uint8_t y;
  } c_stick_state;
  struct {
    wanbeiyu_uint8_t x;
    wanbeiyu_uint8_t y;
  } circle_pad_state;
} wanbeiyu_console_state_t;

static WANBEIYU_INLINE void
wanbeiyu_console_state_deserialize(const wanbeiyu_uint8_t *buffer,
                                   wanbeiyu_console_state_t *state) {

  assert(buffer != NULL);
  /* assert(sizeof(buffer) == 9); */
  assert(state != NULL);

  state->power = (buffer[0] >> 7) & 1;
  state->home = (buffer[0] >> 6) & 1;
  state->zr = (buffer[0] >> 5) & 1;
  state->zl = (buffer[0] >> 4) & 1;
  state->y = (buffer[0] >> 3) & 1;
  state->x = (buffer[0] >> 2) & 1;
  state->l = (buffer[0] >> 1) & 1;
  state->r = (buffer[0] >> 0) & 1;

  state->down = (buffer[1] >> 7) & 1;
  state->up = (buffer[1] >> 6) & 1;
  state->left = (buffer[1] >> 5) & 1;
  state->right = (buffer[1] >> 4) & 1;
  state->start = (buffer[1] >> 3) & 1;
  state->select = (buffer[1] >> 2) & 1;
  state->b = (buffer[1] >> 1) & 1;
  state->a = (buffer[1] >> 0) & 1;

  state->touch_screen =
      (buffer[2] >> 7) & 1 ? &(state->touch_screen_state) : NULL;
  state->c_stick.x = (buffer[2] >> 6) & 1 ? &(state->c_stick_state.x) : NULL;
  state->c_stick.y = (buffer[2] >> 5) & 1 ? &(state->c_stick_state.y) : NULL;
  state->circle_pad.x =
      (buffer[2] >> 4) & 1 ? &(state->circle_pad_state.x) : NULL;
  state->circle_pad.y =
      (buffer[2] >> 3) & 1 ? &(state->circle_pad_state.y) : NULL;
  state->reserved_0 = (buffer[2] >> 2) & 1;
  state->reserved_1 = (buffer[2] >> 1) & 1;

  state->touch_screen_state.x = ((buffer[2] & 1) << 8) | buffer[3];
  state->touch_screen_state.y = buffer[4];

  state->c_stick_state.x = buffer[5];
  state->c_stick_state.y = buffer[6];

  state->circle_pad_state.x = buffer[7];
  state->circle_pad_state.y = buffer[8];
}

static WANBEIYU_INLINE void
wanbeiyu_console_state_serialize(const wanbeiyu_console_state_t *state,
                                 wanbeiyu_uint8_t *buffer) {
  assert(state != NULL);
  assert(buffer != NULL);
  /* assert(sizeof(buffer) == 9); */

  buffer[0] = ((state->power & 1) << 7) | ((state->home & 1) << 6) |
              ((state->zr & 1) << 5) | ((state->zl & 1) << 4) |
              ((state->y & 1) << 3) | ((state->x & 1) << 2) |
              ((state->l & 1) << 1) | ((state->r & 1) << 0);

  buffer[1] = ((state->down & 1) << 7) | ((state->up & 1) << 6) |
              ((state->left & 1) << 5) | ((state->right & 1) << 4) |
              ((state->start & 1) << 3) | ((state->select & 1) << 2) |
              ((state->b & 1) << 1) | ((state->a & 1) << 0);

  buffer[2] = ((state->touch_screen != NULL ? 1 : 0) << 7) |
              ((state->c_stick.x != NULL ? 1 : 0) << 6) |
              ((state->c_stick.y != NULL ? 1 : 0) << 5) |
              ((state->circle_pad.x != NULL ? 1 : 0) << 4) |
              ((state->circle_pad.y != NULL ? 1 : 0) << 3) |
              ((state->reserved_0 & 1) << 2) | ((state->reserved_1 & 1) << 1) |
              (((state->touch_screen_state.x) >> 8) & 1);

  buffer[3] = state->touch_screen_state.x & 0xFF;
  buffer[4] = state->touch_screen_state.y;
  buffer[5] = state->c_stick_state.x;
  buffer[6] = state->c_stick_state.y;
  buffer[7] = state->circle_pad_state.x;
  buffer[8] = state->circle_pad_state.y;
}

#ifdef __cplusplus
}
#endif

#endif /* WANBEIYU_CONSOLE_STATE_H */