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
#include <wanbeiyu/c_stick.h>

static struct {
  wanbeiyu_hal_idac_mode_t pin_1_mode;
  wanbeiyu_uint8_t pin_1_value;
  wanbeiyu_hal_spst_switch_state_t pin_1_state;

  wanbeiyu_hal_idac_mode_t pin_3_mode;
  wanbeiyu_uint8_t pin_3_value;
  wanbeiyu_hal_spst_switch_state_t pin_3_state;
} test_state;

void wanbeiyu_hal_idac_c_stick_pin_1_set(wanbeiyu_hal_idac_mode_t mode,
                                         wanbeiyu_uint8_t value) {
  test_state.pin_1_mode = mode;
  test_state.pin_1_value = value;
}
void wanbeiyu_hal_spst_switch_c_stick_pin_1_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  test_state.pin_1_state = state;
}
void wanbeiyu_hal_idac_c_stick_pin_3_set(wanbeiyu_hal_idac_mode_t mode,
                                         wanbeiyu_uint8_t value) {
  test_state.pin_3_mode = mode;
  test_state.pin_3_value = value;
}
void wanbeiyu_hal_spst_switch_c_stick_pin_3_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  test_state.pin_3_state = state;
}

int main(void) {
  wanbeiyu_state_t state;

  state.c_stick.x = NULL;
  state.c_stick.y = NULL;
  wanbeiyu_c_stick_set(&state);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.pin_1_state);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.pin_3_state);

  state.stash_c_stick.x = 0;
  state.stash_c_stick.y = 0;
  state.c_stick.x = &(state.stash_c_stick.x);
  state.c_stick.y = &(state.stash_c_stick.y);
  wanbeiyu_c_stick_set(&state);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.pin_1_state);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == test_state.pin_3_state);
  assert(WANBEIYU_HAL_IDAC_SINK == test_state.pin_3_mode);
  assert(255 == test_state.pin_3_value);

  state.stash_c_stick.x = 0;
  state.c_stick.x = &(state.stash_c_stick.x);
  state.c_stick.y = NULL;
  wanbeiyu_c_stick_set(&state);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == test_state.pin_1_state);
  assert(WANBEIYU_HAL_IDAC_SOURCE == test_state.pin_1_mode);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == test_state.pin_3_state);
  assert(WANBEIYU_HAL_IDAC_SINK == test_state.pin_3_mode);
  assert(test_state.pin_1_value == test_state.pin_3_value);

  state.stash_c_stick.x = 0;
  state.stash_c_stick.y = 255;
  state.c_stick.x = &(state.stash_c_stick.x);
  state.c_stick.y = &(state.stash_c_stick.y);
  wanbeiyu_c_stick_set(&state);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == test_state.pin_1_state);
  assert(WANBEIYU_HAL_IDAC_SOURCE == test_state.pin_1_mode);
  assert(255 == test_state.pin_1_value);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.pin_3_state);

  state.stash_c_stick.y = 255;
  state.c_stick.x = NULL;
  state.c_stick.y = &(state.stash_c_stick.y);
  wanbeiyu_c_stick_set(&state);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == test_state.pin_1_state);
  assert(WANBEIYU_HAL_IDAC_SOURCE == test_state.pin_1_mode);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == test_state.pin_3_state);
  assert(WANBEIYU_HAL_IDAC_SOURCE == test_state.pin_3_mode);
  assert(test_state.pin_1_value == test_state.pin_3_value);

  state.stash_c_stick.x = 255;
  state.stash_c_stick.y = 255;
  state.c_stick.x = &(state.stash_c_stick.x);
  state.c_stick.y = &(state.stash_c_stick.y);
  wanbeiyu_c_stick_set(&state);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.pin_1_state);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == test_state.pin_3_state);
  assert(WANBEIYU_HAL_IDAC_SOURCE == test_state.pin_3_mode);
  assert(255 == test_state.pin_3_value);

  state.stash_c_stick.x = 255;
  state.c_stick.x = &(state.stash_c_stick.x);
  state.c_stick.y = NULL;
  wanbeiyu_c_stick_set(&state);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == test_state.pin_1_state);
  assert(WANBEIYU_HAL_IDAC_SINK == test_state.pin_1_mode);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == test_state.pin_3_state);
  assert(WANBEIYU_HAL_IDAC_SOURCE == test_state.pin_3_mode);
  assert(test_state.pin_1_value == test_state.pin_3_value);

  state.stash_c_stick.x = 255;
  state.stash_c_stick.y = 0;
  state.c_stick.x = &(state.stash_c_stick.x);
  state.c_stick.y = &(state.stash_c_stick.y);
  wanbeiyu_c_stick_set(&state);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == test_state.pin_1_state);
  assert(WANBEIYU_HAL_IDAC_SINK == test_state.pin_1_mode);
  assert(255 == test_state.pin_1_value);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.pin_3_state);

  state.stash_c_stick.y = 0;
  state.c_stick.x = NULL;
  state.c_stick.y = &(state.stash_c_stick.y);
  wanbeiyu_c_stick_set(&state);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == test_state.pin_1_state);
  assert(WANBEIYU_HAL_IDAC_SINK == test_state.pin_1_mode);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == test_state.pin_3_state);
  assert(WANBEIYU_HAL_IDAC_SINK == test_state.pin_3_mode);
  assert(test_state.pin_1_value == test_state.pin_3_value);

  state.stash_c_stick.x = 87;
  state.stash_c_stick.y = 25;
  state.c_stick.x = &(state.stash_c_stick.x);
  state.c_stick.y = &(state.stash_c_stick.y);
  wanbeiyu_c_stick_set(&state);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == test_state.pin_3_state);
  assert(WANBEIYU_HAL_IDAC_SINK == test_state.pin_1_mode);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == test_state.pin_3_state);
  assert(WANBEIYU_HAL_IDAC_SINK == test_state.pin_3_mode);

  return 0;
}