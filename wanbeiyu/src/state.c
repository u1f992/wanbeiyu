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

#include <wanbeiyu/state.h>

void wanbeiyu_state_reset(wanbeiyu_state_t *state) {
  assert(state != NULL);

  state->buttons = 0;
  state->touch_screen = NULL;
  state->c_stick.x = NULL;
  state->c_stick.y = NULL;
  state->circle_pad.x = NULL;
  state->circle_pad.y = NULL;
  state->reserved_0 = 0;
  state->reserved_1 = 0;

  state->stash_touch_screen.x = 0;
  state->stash_touch_screen.y = 0;
  state->stash_c_stick.x = 0;
  state->stash_c_stick.y = 0;
  state->stash_circle_pad.x = 0;
  state->stash_circle_pad.y = 0;
}

void wanbeiyu_state_deserialize(wanbeiyu_uint8_t const *buffer,
                                wanbeiyu_state_t *state) {

  assert(buffer != NULL);
  /* assert(sizeof(buffer) == 9); */
  assert(state != NULL);

  state->buttons = ((wanbeiyu_uint16_t)buffer[0] << 8) | buffer[1];
  state->touch_screen =
      (buffer[2] >> 7) & 1 ? &(state->stash_touch_screen) : NULL;
  state->c_stick.x = (buffer[2] >> 6) & 1 ? &(state->stash_c_stick.x) : NULL;
  state->c_stick.y = (buffer[2] >> 5) & 1 ? &(state->stash_c_stick.y) : NULL;
  state->circle_pad.x =
      (buffer[2] >> 4) & 1 ? &(state->stash_circle_pad.x) : NULL;
  state->circle_pad.y =
      (buffer[2] >> 3) & 1 ? &(state->stash_circle_pad.y) : NULL;
  state->reserved_0 = (buffer[2] >> 2) & 1;
  state->reserved_1 = (buffer[2] >> 1) & 1;

  state->stash_touch_screen.x = ((buffer[2] & 1) << 8) | buffer[3];
  state->stash_touch_screen.y = buffer[4];

  state->stash_c_stick.x = buffer[5];
  state->stash_c_stick.y = buffer[6];

  state->stash_circle_pad.x = buffer[7];
  state->stash_circle_pad.y = buffer[8];
}

void wanbeiyu_state_serialize(wanbeiyu_state_t const *state,
                              wanbeiyu_uint8_t *buffer) {
  assert(state != NULL);
  assert(buffer != NULL);
  /* assert(sizeof(buffer) == 9); */

  buffer[0] = (wanbeiyu_uint8_t)(state->buttons >> 8);
  buffer[1] = (wanbeiyu_uint8_t)(state->buttons & 0xFF);

  buffer[2] = ((state->touch_screen != NULL ? 1 : 0) << 7) |
              ((state->c_stick.x != NULL ? 1 : 0) << 6) |
              ((state->c_stick.y != NULL ? 1 : 0) << 5) |
              ((state->circle_pad.x != NULL ? 1 : 0) << 4) |
              ((state->circle_pad.y != NULL ? 1 : 0) << 3) |
              ((state->reserved_0 & 1) << 2) | ((state->reserved_1 & 1) << 1) |
              (((state->stash_touch_screen.x) >> 8) & 1);

  buffer[3] = state->stash_touch_screen.x & 0xFF;
  buffer[4] = state->stash_touch_screen.y;
  buffer[5] = state->stash_c_stick.x;
  buffer[6] = state->stash_c_stick.y;
  buffer[7] = state->stash_circle_pad.x;
  buffer[8] = state->stash_circle_pad.y;
}