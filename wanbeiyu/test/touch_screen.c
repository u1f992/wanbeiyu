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
#include <wanbeiyu/touch_screen.h>

static struct {
  wanbeiyu_uint16_t pin_2_4_position;
  wanbeiyu_uint8_t pin_3_1_position;
  wanbeiyu_hal_spst_switch_state_t switch_;
} test_state;

void wanbeiyu_hal_rdac_touch_screen_pin_2_4_set(wanbeiyu_uint16_t position) {
  assert(position < 320);
  test_state.pin_2_4_position = position;
}
void wanbeiyu_hal_rdac_touch_screen_pin_3_1_set(wanbeiyu_uint8_t position) {
  assert(position < 240);
  test_state.pin_3_1_position = position;
}
void wanbeiyu_hal_spst_switch_touch_screen_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  test_state.switch_ = state;
}

int main(void) {
  wanbeiyu_state_t state;

  state.touch_screen = NULL;
  wanbeiyu_touch_screen_set(&state);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.switch_);

  state.stash_touch_screen.x = 0;
  state.stash_touch_screen.y = 0;
  state.touch_screen = &(state.stash_touch_screen);
  wanbeiyu_touch_screen_set(&state);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == test_state.switch_);
  assert(0 == test_state.pin_2_4_position);
  assert(0 == test_state.pin_3_1_position);

  state.stash_touch_screen.x = 319;
  state.stash_touch_screen.y = 239;
  state.touch_screen = &(state.stash_touch_screen);
  wanbeiyu_touch_screen_set(&state);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == test_state.switch_);
  assert(319 == test_state.pin_2_4_position);
  assert(239 == test_state.pin_3_1_position);

  return 0;
}