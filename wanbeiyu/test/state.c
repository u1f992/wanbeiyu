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

#undef __STDC_VERSION__
#include <wanbeiyu/state.h>

int main(void) {
  wanbeiyu_state_t state;

  wanbeiyu_uint8_t buffer[] = {0xaa, 0x55, 0xf8, 1, 2, 3, 4, 5, 6};

  wanbeiyu_state_deserialize(buffer, &state);
  assert(0xaa55 == state.buttons);
  assert(NULL != state.touch_screen);
  assert(1 == state.touch_screen->x);
  assert(2 == state.touch_screen->y);
  assert(NULL != state.c_stick.x);
  assert(3 == *(state.c_stick.x));
  assert(NULL != state.c_stick.y);
  assert(4 == *(state.c_stick.y));
  assert(NULL != state.circle_pad.x);
  assert(5 == *(state.circle_pad.x));
  assert(NULL != state.circle_pad.y);
  assert(6 == *(state.circle_pad.y));

  state.buttons = 0x55aa;
  state.touch_screen->x = 6;
  state.touch_screen->y = 5;
  *(state.c_stick.x) = 4;
  *(state.c_stick.y) = 3;
  *(state.circle_pad.x) = 2;
  *(state.circle_pad.y) = 1;
  wanbeiyu_state_serialize(&state, buffer);
  assert(0x55 == buffer[0]);
  assert(0xaa == buffer[1]);
  assert(0xf8 /* 0b11111000 */ == buffer[2]);
  assert(6 == buffer[3]);
  assert(5 == buffer[4]);
  assert(4 == buffer[5]);
  assert(3 == buffer[6]);
  assert(2 == buffer[7]);
  assert(1 == buffer[8]);

  wanbeiyu_state_reset(&state);
  assert(0 == state.buttons);
  assert(NULL == state.touch_screen);
  assert(NULL == state.c_stick.x);
  assert(NULL == state.c_stick.y);
  assert(NULL == state.circle_pad.x);
  assert(NULL == state.circle_pad.y);

  return 0;
}