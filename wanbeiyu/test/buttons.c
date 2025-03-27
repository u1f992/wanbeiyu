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
#include <wanbeiyu/buttons.h>

static struct {
  wanbeiyu_hal_spst_switch_state_t power;
  wanbeiyu_hal_spst_switch_state_t home;
  wanbeiyu_hal_spst_switch_state_t zr;
  wanbeiyu_hal_spst_switch_state_t zl;
  wanbeiyu_hal_spst_switch_state_t y;
  wanbeiyu_hal_spst_switch_state_t x;
  wanbeiyu_hal_spst_switch_state_t l;
  wanbeiyu_hal_spst_switch_state_t r;
  wanbeiyu_hal_spst_switch_state_t down;
  wanbeiyu_hal_spst_switch_state_t up;
  wanbeiyu_hal_spst_switch_state_t left;
  wanbeiyu_hal_spst_switch_state_t right;
  wanbeiyu_hal_spst_switch_state_t start;
  wanbeiyu_hal_spst_switch_state_t select;
  wanbeiyu_hal_spst_switch_state_t b;
  wanbeiyu_hal_spst_switch_state_t a;
} test_state;

void wanbeiyu_hal_spst_switch_buttons_power_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  test_state.power = state;
}
void wanbeiyu_hal_spst_switch_buttons_home_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  test_state.home = state;
}
void wanbeiyu_hal_spst_switch_buttons_zr_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  test_state.zr = state;
}
void wanbeiyu_hal_spst_switch_buttons_zl_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  test_state.zl = state;
}
void wanbeiyu_hal_spst_switch_buttons_y_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  test_state.y = state;
}
void wanbeiyu_hal_spst_switch_buttons_x_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  test_state.x = state;
}
void wanbeiyu_hal_spst_switch_buttons_l_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  test_state.l = state;
}
void wanbeiyu_hal_spst_switch_buttons_r_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  test_state.r = state;
}
void wanbeiyu_hal_spst_switch_buttons_down_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  test_state.down = state;
}
void wanbeiyu_hal_spst_switch_buttons_up_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  test_state.up = state;
}
void wanbeiyu_hal_spst_switch_buttons_left_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  test_state.left = state;
}
void wanbeiyu_hal_spst_switch_buttons_right_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  test_state.right = state;
}
void wanbeiyu_hal_spst_switch_buttons_start_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  test_state.start = state;
}
void wanbeiyu_hal_spst_switch_buttons_select_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  test_state.select = state;
}
void wanbeiyu_hal_spst_switch_buttons_b_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  test_state.b = state;
}
void wanbeiyu_hal_spst_switch_buttons_a_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  test_state.a = state;
}

int main(void) {
  wanbeiyu_state_t state;

  state.buttons = 1 << 15;
  wanbeiyu_buttons_set(&state);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == test_state.power);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.home);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.zr);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.zl);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.y);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.x);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.l);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.r);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.down);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.up);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.left);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.right);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.start);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.select);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.b);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.a);

  state.buttons = 1 << 14;
  wanbeiyu_buttons_set(&state);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.power);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == test_state.home);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.zr);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.zl);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.y);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.x);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.l);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.r);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.down);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.up);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.left);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.right);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.start);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.select);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.b);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.a);

  state.buttons = 1 << 13;
  wanbeiyu_buttons_set(&state);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.power);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.home);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == test_state.zr);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.zl);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.y);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.x);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.l);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.r);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.down);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.up);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.left);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.right);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.start);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.select);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.b);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.a);

  state.buttons = 1 << 12;
  wanbeiyu_buttons_set(&state);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.power);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.home);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.zr);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == test_state.zl);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.y);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.x);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.l);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.r);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.down);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.up);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.left);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.right);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.start);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.select);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.b);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.a);

  state.buttons = 1 << 11;
  wanbeiyu_buttons_set(&state);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.power);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.home);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.zr);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.zl);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == test_state.y);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.x);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.l);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.r);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.down);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.up);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.left);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.right);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.start);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.select);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.b);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.a);

  state.buttons = 1 << 10;
  wanbeiyu_buttons_set(&state);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.power);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.home);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.zr);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.zl);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.y);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == test_state.x);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.l);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.r);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.down);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.up);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.left);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.right);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.start);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.select);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.b);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.a);

  state.buttons = 1 << 9;
  wanbeiyu_buttons_set(&state);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.power);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.home);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.zr);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.zl);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.y);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.x);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == test_state.l);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.r);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.down);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.up);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.left);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.right);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.start);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.select);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.b);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.a);

  state.buttons = 1 << 8;
  wanbeiyu_buttons_set(&state);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.power);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.home);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.zr);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.zl);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.y);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.x);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.l);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == test_state.r);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.down);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.up);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.left);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.right);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.start);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.select);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.b);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.a);

  state.buttons = 1 << 7;
  wanbeiyu_buttons_set(&state);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.power);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.home);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.zr);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.zl);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.y);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.x);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.l);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.r);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == test_state.down);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.up);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.left);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.right);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.start);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.select);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.b);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.a);

  state.buttons = 1 << 6;
  wanbeiyu_buttons_set(&state);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.power);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.home);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.zr);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.zl);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.y);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.x);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.l);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.r);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.down);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == test_state.up);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.left);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.right);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.start);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.select);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.b);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.a);

  state.buttons = 1 << 5;
  wanbeiyu_buttons_set(&state);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.power);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.home);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.zr);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.zl);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.y);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.x);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.l);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.r);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.down);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.up);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == test_state.left);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.right);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.start);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.select);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.b);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.a);

  state.buttons = 1 << 4;
  wanbeiyu_buttons_set(&state);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.power);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.home);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.zr);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.zl);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.y);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.x);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.l);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.r);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.down);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.up);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.left);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == test_state.right);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.start);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.select);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.b);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.a);

  state.buttons = 1 << 3;
  wanbeiyu_buttons_set(&state);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.power);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.home);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.zr);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.zl);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.y);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.x);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.l);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.r);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.down);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.up);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.left);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.right);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == test_state.start);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.select);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.b);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.a);

  state.buttons = 1 << 2;
  wanbeiyu_buttons_set(&state);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.power);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.home);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.zr);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.zl);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.y);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.x);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.l);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.r);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.down);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.up);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.left);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.right);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.start);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == test_state.select);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.b);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.a);

  state.buttons = 1 << 1;
  wanbeiyu_buttons_set(&state);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.power);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.home);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.zr);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.zl);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.y);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.x);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.l);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.r);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.down);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.up);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.left);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.right);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.start);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.select);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == test_state.b);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.a);

  state.buttons = 1 << 0;
  wanbeiyu_buttons_set(&state);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.power);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.home);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.zr);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.zl);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.y);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.x);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.l);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.r);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.down);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.up);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.left);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.right);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.start);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.select);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.b);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == test_state.a);

  state.buttons = 0xaa55;
  wanbeiyu_buttons_set(&state);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == test_state.power);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.home);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == test_state.zr);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.zl);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == test_state.y);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.x);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == test_state.l);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.r);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.down);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == test_state.up);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.left);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == test_state.right);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.start);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == test_state.select);
  assert(WANBEIYU_HAL_SPST_SWITCH_OPEN == test_state.b);
  assert(WANBEIYU_HAL_SPST_SWITCH_CLOSE == test_state.a);

  return 0;
}