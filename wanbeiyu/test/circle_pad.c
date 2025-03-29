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
#include <wanbeiyu/circle_pad.h>

static struct {
  wanbeiyu_hal_idac_mode_t pin_2_mode;
  wanbeiyu_uint8_t pin_2_value;
  wanbeiyu_hal_spst_switch_state_t pin_2_state;

  wanbeiyu_hal_idac_mode_t pin_4_mode;
  wanbeiyu_uint8_t pin_4_value;
  wanbeiyu_hal_spst_switch_state_t pin_4_state;
} test_state;

void wanbeiyu_hal_idac_circle_pad_pin_2_set(wanbeiyu_hal_idac_mode_t mode,
                                            wanbeiyu_uint8_t value) {
  test_state.pin_2_mode = mode;
  test_state.pin_2_value = value;
}
void wanbeiyu_hal_spst_switch_circle_pad_pin_2_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  test_state.pin_2_state = state;
}
void wanbeiyu_hal_idac_circle_pad_pin_4_set(wanbeiyu_hal_idac_mode_t mode,
                                            wanbeiyu_uint8_t value) {
  test_state.pin_4_mode = mode;
  test_state.pin_4_value = value;
}
void wanbeiyu_hal_spst_switch_circle_pad_pin_4_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  test_state.pin_4_state = state;
}

int main(void) {
  wanbeiyu_state_t state;

  state.circle_pad.x = NULL;
  state.circle_pad.y = NULL;
  wanbeiyu_circle_pad_set(&state);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.pin_2_state);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.pin_4_state);

  state.stash_circle_pad.x = 0;
  state.stash_circle_pad.y = 0;
  state.circle_pad.x = &(state.stash_circle_pad.x);
  state.circle_pad.y = &(state.stash_circle_pad.y);
  wanbeiyu_circle_pad_set(&state);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == test_state.pin_2_state);
  assert(WANBEIYU_HAL_IDAC_SOURCE == test_state.pin_2_mode);
  assert(255 == test_state.pin_2_value);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == test_state.pin_4_state);
  assert(WANBEIYU_HAL_IDAC_SINK == test_state.pin_4_mode);
  assert(255 == test_state.pin_4_value);

  state.stash_circle_pad.x = 0;
  state.circle_pad.x = &(state.stash_circle_pad.x);
  state.circle_pad.y = NULL;
  wanbeiyu_circle_pad_set(&state);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == test_state.pin_2_state);
  assert(WANBEIYU_HAL_IDAC_SOURCE == test_state.pin_2_mode);
  assert(255 == test_state.pin_2_value);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.pin_4_state);

  state.stash_circle_pad.x = 0;
  state.stash_circle_pad.y = 255;
  state.circle_pad.x = &(state.stash_circle_pad.x);
  state.circle_pad.y = &(state.stash_circle_pad.y);
  wanbeiyu_circle_pad_set(&state);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == test_state.pin_2_state);
  assert(WANBEIYU_HAL_IDAC_SOURCE == test_state.pin_2_mode);
  assert(255 == test_state.pin_2_value);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == test_state.pin_4_state);
  assert(WANBEIYU_HAL_IDAC_SOURCE == test_state.pin_4_mode);
  assert(255 == test_state.pin_4_value);

  state.stash_circle_pad.y = 255;
  state.circle_pad.x = NULL;
  state.circle_pad.y = &(state.stash_circle_pad.y);
  wanbeiyu_circle_pad_set(&state);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.pin_2_state);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == test_state.pin_4_state);
  assert(WANBEIYU_HAL_IDAC_SOURCE == test_state.pin_4_mode);
  assert(255 == test_state.pin_4_value);

  state.stash_circle_pad.x = 255;
  state.stash_circle_pad.y = 255;
  state.circle_pad.x = &(state.stash_circle_pad.x);
  state.circle_pad.y = &(state.stash_circle_pad.y);
  wanbeiyu_circle_pad_set(&state);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == test_state.pin_2_state);
  assert(WANBEIYU_HAL_IDAC_SINK == test_state.pin_2_mode);
  assert(255 == test_state.pin_2_value);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == test_state.pin_4_state);
  assert(WANBEIYU_HAL_IDAC_SOURCE == test_state.pin_4_mode);
  assert(255 == test_state.pin_4_value);

  state.stash_circle_pad.x = 255;
  state.circle_pad.x = &(state.stash_circle_pad.x);
  state.circle_pad.y = NULL;
  wanbeiyu_circle_pad_set(&state);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == test_state.pin_2_state);
  assert(WANBEIYU_HAL_IDAC_SINK == test_state.pin_2_mode);
  assert(255 == test_state.pin_2_value);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.pin_4_state);

  state.stash_circle_pad.x = 255;
  state.stash_circle_pad.y = 0;
  state.circle_pad.x = &(state.stash_circle_pad.x);
  state.circle_pad.y = &(state.stash_circle_pad.y);
  wanbeiyu_circle_pad_set(&state);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == test_state.pin_2_state);
  assert(WANBEIYU_HAL_IDAC_SINK == test_state.pin_2_mode);
  assert(255 == test_state.pin_2_value);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == test_state.pin_4_state);
  assert(WANBEIYU_HAL_IDAC_SINK == test_state.pin_4_mode);
  assert(255 == test_state.pin_4_value);

  state.stash_circle_pad.y = 0;
  state.circle_pad.x = NULL;
  state.circle_pad.y = &(state.stash_circle_pad.y);
  wanbeiyu_circle_pad_set(&state);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.pin_2_state);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == test_state.pin_4_state);
  assert(WANBEIYU_HAL_IDAC_SINK == test_state.pin_4_mode);
  assert(255 == test_state.pin_4_value);

  return 0;
}