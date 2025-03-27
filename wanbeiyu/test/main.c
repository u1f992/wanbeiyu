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
#include <wanbeiyu.h>

#include <stdio.h>

void wanbeiyu_hal_uart_read(wanbeiyu_uint8_t *buffer, size_t *length) {
  static const wanbeiyu_uint8_t input[] = {
      WANBEIYU_COMMAND_SET_STATE, 0xaa, 0x55, 0xf8, 1, 2, 3, 4, 5, 6,
      WANBEIYU_COMMAND_GET_STATE};
  static wanbeiyu_uint8_t sent = 0;

  assert(buffer != NULL);
  assert(length != NULL);

  if (!sent) {
    size_t i;
    for (i = 0; i < sizeof(input); i++) {
      buffer[i] = input[i];
    }
    *length = sizeof(input);
    sent = 1;
  } else {
    *length = 0;
  }

  assert(*length <= WANBEIYU_BUFFER_SIZE);
}

void wanbeiyu_hal_uart_write(const wanbeiyu_uint8_t *buffer, size_t length) {
  size_t i;
  for (i = 0; i < length; i++) {
    fprintf(stderr, "%02x ", buffer[i]);
  }
  fprintf(stderr, "\n");
}

static wanbeiyu_hal_spst_switch_state_t power_state;
static wanbeiyu_hal_spst_switch_state_t home_state;
static wanbeiyu_hal_spst_switch_state_t zr_state;
static wanbeiyu_hal_spst_switch_state_t zl_state;
static wanbeiyu_hal_spst_switch_state_t y_state;
static wanbeiyu_hal_spst_switch_state_t x_state;
static wanbeiyu_hal_spst_switch_state_t l_state;
static wanbeiyu_hal_spst_switch_state_t r_state;
static wanbeiyu_hal_spst_switch_state_t down_state;
static wanbeiyu_hal_spst_switch_state_t up_state;
static wanbeiyu_hal_spst_switch_state_t left_state;
static wanbeiyu_hal_spst_switch_state_t right_state;
static wanbeiyu_hal_spst_switch_state_t start_state;
static wanbeiyu_hal_spst_switch_state_t select_state;
static wanbeiyu_hal_spst_switch_state_t b_state;
static wanbeiyu_hal_spst_switch_state_t a_state;

void wanbeiyu_hal_spst_switch_buttons_power_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  power_state = state;
}
void wanbeiyu_hal_spst_switch_buttons_home_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  home_state = state;
}
void wanbeiyu_hal_spst_switch_buttons_zr_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  zr_state = state;
}
void wanbeiyu_hal_spst_switch_buttons_zl_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  zl_state = state;
}
void wanbeiyu_hal_spst_switch_buttons_y_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  y_state = state;
}
void wanbeiyu_hal_spst_switch_buttons_x_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  x_state = state;
}
void wanbeiyu_hal_spst_switch_buttons_l_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  l_state = state;
}
void wanbeiyu_hal_spst_switch_buttons_r_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  r_state = state;
}
void wanbeiyu_hal_spst_switch_buttons_down_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  down_state = state;
}
void wanbeiyu_hal_spst_switch_buttons_up_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  up_state = state;
}
void wanbeiyu_hal_spst_switch_buttons_left_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  left_state = state;
}
void wanbeiyu_hal_spst_switch_buttons_right_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  right_state = state;
}
void wanbeiyu_hal_spst_switch_buttons_start_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  start_state = state;
}
void wanbeiyu_hal_spst_switch_buttons_select_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  select_state = state;
}
void wanbeiyu_hal_spst_switch_buttons_b_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  b_state = state;
}
void wanbeiyu_hal_spst_switch_buttons_a_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  a_state = state;
}

static wanbeiyu_hal_spst_switch_state_t touch_screen_state;

void wanbeiyu_hal_rdac_touch_screen_pin_3_1_set(wanbeiyu_uint16_t position) {
  assert(position < 320);
  (void)position;
}
void wanbeiyu_hal_rdac_touch_screen_pin_2_4_set(wanbeiyu_uint8_t position) {
  assert(position < 240);
  (void)position;
}
void wanbeiyu_hal_spst_switch_touch_screen_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  touch_screen_state = state;
}

static wanbeiyu_hal_spst_switch_state_t c_stick_pin_1_state;
static wanbeiyu_hal_spst_switch_state_t c_stick_pin_3_state;

void wanbeiyu_hal_idac_c_stick_pin_1_set(wanbeiyu_hal_idac_mode_t mode,
                                         wanbeiyu_uint8_t value) {
  (void)mode;
  (void)value;
}
void wanbeiyu_hal_spst_switch_c_stick_pin_1_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  c_stick_pin_1_state = state;
}
void wanbeiyu_hal_idac_c_stick_pin_3_set(wanbeiyu_hal_idac_mode_t mode,
                                         wanbeiyu_uint8_t value) {
  (void)mode;
  (void)value;
}
void wanbeiyu_hal_spst_switch_c_stick_pin_3_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  c_stick_pin_3_state = state;
}

static wanbeiyu_hal_spst_switch_state_t circle_pad_pin_2_state;
static wanbeiyu_hal_spst_switch_state_t circle_pad_pin_4_state;

void wanbeiyu_hal_idac_circle_pad_pin_2_set(wanbeiyu_hal_idac_mode_t mode,
                                            wanbeiyu_uint8_t value) {
  (void)mode;
  (void)value;
}
void wanbeiyu_hal_spst_switch_circle_pad_pin_2_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  circle_pad_pin_2_state = state;
}
void wanbeiyu_hal_idac_circle_pad_pin_4_set(wanbeiyu_hal_idac_mode_t mode,
                                            wanbeiyu_uint8_t value) {
  (void)mode;
  (void)value;
}
void wanbeiyu_hal_spst_switch_circle_pad_pin_4_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  circle_pad_pin_4_state = state;
}

int main(void) {
  wanbeiyu_t wanbeiyu;

  wanbeiyu_init(&wanbeiyu);
  wanbeiyu_loop(&wanbeiyu);

  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == power_state);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == home_state);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == zr_state);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == zl_state);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == y_state);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == x_state);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == l_state);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == r_state);

  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == down_state);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == up_state);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == left_state);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == right_state);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == start_state);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == select_state);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == b_state);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == a_state);

  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == touch_screen_state);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == c_stick_pin_1_state);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == c_stick_pin_3_state);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == circle_pad_pin_2_state);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == circle_pad_pin_4_state);

  return 0;
}