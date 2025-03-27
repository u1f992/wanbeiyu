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

#ifndef WANBEIYU_STATE_H
#define WANBEIYU_STATE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "compat.h"

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

typedef struct wanbeiyu_state_t {
  wanbeiyu_uint16_t buttons;
  wanbeiyu_touch_screen_state_t *touch_screen;
  wanbeiyu_c_stick_state_t c_stick;
  wanbeiyu_circle_pad_state_t circle_pad;
  wanbeiyu_uint8_t reserved_0;
  wanbeiyu_uint8_t reserved_1;

  wanbeiyu_touch_screen_state_t stash_touch_screen;
  struct {
    wanbeiyu_uint8_t x;
    wanbeiyu_uint8_t y;
  } stash_c_stick;
  struct {
    wanbeiyu_uint8_t x;
    wanbeiyu_uint8_t y;
  } stash_circle_pad;
} wanbeiyu_state_t;

void wanbeiyu_state_reset(wanbeiyu_state_t *);
void wanbeiyu_state_deserialize(wanbeiyu_uint8_t const *, wanbeiyu_state_t *);
void wanbeiyu_state_serialize(wanbeiyu_state_t const *, wanbeiyu_uint8_t *);

#ifdef __cplusplus
}
#endif

#endif /* WANBEIYU_STATE_H */