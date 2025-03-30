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

#include "project.h"

#include <wanbeiyu.h>

void wanbeiyu_hook(void) {}

void wanbeiyu_hal_uart_read(wanbeiyu_uint8_t *buffer, size_t *length) {
  assert(buffer != NULL);
  assert(length != NULL);
  (void)buffer;
  (void)length;
  assert(*length <= WANBEIYU_HAL_UART_BUFFER_SIZE);
}

void wanbeiyu_hal_uart_write(const wanbeiyu_uint8_t *buffer, size_t length) {
  assert(buffer != NULL);
  (void)buffer;
  (void)length;
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

void wanbeiyu_hal_rdac_touch_screen_pin_2_4_set(wanbeiyu_uint16_t position) {
  assert(position < 320);
  (void)position;
}
void wanbeiyu_hal_rdac_touch_screen_pin_3_1_set(wanbeiyu_uint8_t position) {
  assert(position < 240);
  (void)position;
}
void wanbeiyu_hal_spst_switch_touch_screen_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  (void)state;
}

void wanbeiyu_hal_idac_c_stick_pin_1_set(wanbeiyu_hal_idac_mode_t mode,
                                         wanbeiyu_uint8_t value) {
  (void)mode;
  (void)value;
}
void wanbeiyu_hal_spst_switch_c_stick_pin_1_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  (void)state;
}
void wanbeiyu_hal_idac_c_stick_pin_3_set(wanbeiyu_hal_idac_mode_t mode,
                                         wanbeiyu_uint8_t value) {
  (void)mode;
  (void)value;
}
void wanbeiyu_hal_spst_switch_c_stick_pin_3_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  (void)state;
}

void wanbeiyu_hal_idac_circle_pad_pin_2_set(wanbeiyu_hal_idac_mode_t mode,
                                            wanbeiyu_uint8_t value) {
  (void)mode;
  (void)value;
}
void wanbeiyu_hal_spst_switch_circle_pad_pin_2_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  (void)state;
}
void wanbeiyu_hal_idac_circle_pad_pin_4_set(wanbeiyu_hal_idac_mode_t mode,
                                            wanbeiyu_uint8_t value) {
  (void)mode;
  (void)value;
}
void wanbeiyu_hal_spst_switch_circle_pad_pin_4_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  (void)state;
}

int main(void) {
  CyGlobalIntEnable; /* Enable global interrupts. */

  wanbeiyu_init();

  for (;;) {
    wanbeiyu_loop();
  }
}

/* [] END OF FILE */
