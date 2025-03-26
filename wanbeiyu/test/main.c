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

void wanbeiyu_hal_uart_write(const wanbeiyu_uint8_t *buffer, size_t length) {
  size_t i;
  for (i = 0; i < length; i++) {
    fprintf(stderr, "%02x ", buffer[i]);
  }
  fprintf(stderr, "\n");
}

void wanbeiyu_hal_spst_switch_buttons_power_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  (void)state;
}
void wanbeiyu_hal_spst_switch_buttons_home_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  (void)state;
}
void wanbeiyu_hal_spst_switch_buttons_zr_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  (void)state;
}
void wanbeiyu_hal_spst_switch_buttons_zl_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  (void)state;
}
void wanbeiyu_hal_spst_switch_buttons_y_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  (void)state;
}
void wanbeiyu_hal_spst_switch_buttons_x_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  (void)state;
}
void wanbeiyu_hal_spst_switch_buttons_l_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  (void)state;
}
void wanbeiyu_hal_spst_switch_buttons_r_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  (void)state;
}
void wanbeiyu_hal_spst_switch_buttons_down_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  (void)state;
}
void wanbeiyu_hal_spst_switch_buttons_up_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  (void)state;
}
void wanbeiyu_hal_spst_switch_buttons_left_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  (void)state;
}
void wanbeiyu_hal_spst_switch_buttons_right_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  (void)state;
}
void wanbeiyu_hal_spst_switch_buttons_start_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  (void)state;
}
void wanbeiyu_hal_spst_switch_buttons_select_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  (void)state;
}
void wanbeiyu_hal_spst_switch_buttons_b_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  (void)state;
}
void wanbeiyu_hal_spst_switch_buttons_a_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  (void)state;
}

void wanbeiyu_hal_rdac_touch_screen_horizontal_set(wanbeiyu_uint16_t position) {
  assert(position < 320);
  (void)position;
}
void wanbeiyu_hal_rdac_touch_screen_vertical_set(wanbeiyu_uint8_t position) {
  assert(position < 240);
  (void)position;
}
void wanbeiyu_hal_spst_switch_touch_screen_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  (void)state;
}

void wanbeiyu_hal_idac_c_stick_positive_slope_set(wanbeiyu_hal_idac_mode_t mode,
                                                  wanbeiyu_uint8_t value) {
  (void)mode;
  (void)value;
}
void wanbeiyu_hal_spst_switch_c_stick_positive_slope_switch_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  (void)state;
}
void wanbeiyu_hal_idac_c_stick_negative_slope_set(wanbeiyu_hal_idac_mode_t mode,
                                                  wanbeiyu_uint8_t value) {
  (void)mode;
  (void)value;
}
void wanbeiyu_hal_spst_switch_c_stick_negative_slope_switch_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  (void)state;
}

void wanbeiyu_hal_idac_circle_pad_horizontal_set(wanbeiyu_hal_idac_mode_t mode,
                                                 wanbeiyu_uint8_t value) {
  (void)mode;
  (void)value;
}
void wanbeiyu_hal_spst_switch_circle_pad_horizontal_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  (void)state;
}
void wanbeiyu_hal_idac_circle_pad_vertical_set(wanbeiyu_hal_idac_mode_t mode,
                                               wanbeiyu_uint8_t value) {
  (void)mode;
  (void)value;
}
void wanbeiyu_hal_spst_switch_circle_pad_vertical_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  (void)state;
}

int main(void) {
  wanbeiyu_t wanbeiyu;

  wanbeiyu_uint8_t input[10] = {
      WANBEIYU_COMMAND_SET_CONSOLE_STATE, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  wanbeiyu_init(&wanbeiyu);

  wanbeiyu_loop(&wanbeiyu, input, sizeof(input));
  return 0;
}