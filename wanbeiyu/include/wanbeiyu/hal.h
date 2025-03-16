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

#ifndef WANBEIYU_HAL_H
#define WANBEIYU_HAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "hal/idac.h"
#include "hal/rdac_240_steps.h"
#include "hal/rdac_320_steps.h"
#include "hal/spst_switch.h"
#include "hal/uart.h"

typedef struct wanbeiyu_hal_touch_screen_t {
  wanbeiyu_hal_rdac_320_steps_t *horizontal;
  wanbeiyu_hal_rdac_240_steps_t *vertical;
  wanbeiyu_hal_spst_switch_t *switch_;
} wanbeiyu_hal_touch_screen_t;

typedef struct wanbeiyu_hal_c_stick_t {
  wanbeiyu_hal_idac_t *axis1;
  wanbeiyu_hal_spst_switch_t *axis1_switch;
  wanbeiyu_hal_idac_t *axis3;
  wanbeiyu_hal_spst_switch_t *axis3_switch;
} wanbeiyu_hal_c_stick_t;

typedef struct wanbeiyu_hal_circle_pad_t {
  wanbeiyu_hal_idac_t *horizontal;
  wanbeiyu_hal_spst_switch_t *horizontal_switch;
  wanbeiyu_hal_idac_t *vertical;
  wanbeiyu_hal_spst_switch_t *vertical_switch;
} wanbeiyu_hal_circle_pad_t;

typedef struct wanbeiyu_hal_t {
  wanbeiyu_hal_uart_t *uart;
  wanbeiyu_hal_spst_switch_t *power;
  wanbeiyu_hal_spst_switch_t *home;
  wanbeiyu_hal_spst_switch_t *zr;
  wanbeiyu_hal_spst_switch_t *zl;
  wanbeiyu_hal_spst_switch_t *y;
  wanbeiyu_hal_spst_switch_t *x;
  wanbeiyu_hal_spst_switch_t *l;
  wanbeiyu_hal_spst_switch_t *r;
  wanbeiyu_hal_spst_switch_t *down;
  wanbeiyu_hal_spst_switch_t *up;
  wanbeiyu_hal_spst_switch_t *left;
  wanbeiyu_hal_spst_switch_t *right;
  wanbeiyu_hal_spst_switch_t *start;
  wanbeiyu_hal_spst_switch_t *select;
  wanbeiyu_hal_spst_switch_t *b;
  wanbeiyu_hal_spst_switch_t *a;
  wanbeiyu_hal_touch_screen_t touch_screen;
  wanbeiyu_hal_c_stick_t c_stick;
  wanbeiyu_hal_circle_pad_t circle_pad;
} wanbeiyu_hal_t;

static WANBEIYU_INLINE void wanbeiyu_hal_init(
    wanbeiyu_hal_t *hal, wanbeiyu_hal_uart_t *uart,
    wanbeiyu_hal_spst_switch_t *power, wanbeiyu_hal_spst_switch_t *home,
    wanbeiyu_hal_spst_switch_t *zr, wanbeiyu_hal_spst_switch_t *zl,
    wanbeiyu_hal_spst_switch_t *y, wanbeiyu_hal_spst_switch_t *x,
    wanbeiyu_hal_spst_switch_t *l, wanbeiyu_hal_spst_switch_t *r,
    wanbeiyu_hal_spst_switch_t *down, wanbeiyu_hal_spst_switch_t *up,
    wanbeiyu_hal_spst_switch_t *left, wanbeiyu_hal_spst_switch_t *right,
    wanbeiyu_hal_spst_switch_t *start, wanbeiyu_hal_spst_switch_t *select,
    wanbeiyu_hal_spst_switch_t *b, wanbeiyu_hal_spst_switch_t *a,
    wanbeiyu_hal_rdac_320_steps_t *touch_screen_horizontal,
    wanbeiyu_hal_rdac_240_steps_t *touch_screen_vertical,
    wanbeiyu_hal_spst_switch_t *touch_screen_switch,
    wanbeiyu_hal_idac_t *c_stick_axis1,
    wanbeiyu_hal_spst_switch_t *c_stick_axis1_switch,
    wanbeiyu_hal_idac_t *c_stick_axis3,
    wanbeiyu_hal_spst_switch_t *c_stick_axis3_switch,
    wanbeiyu_hal_idac_t *circle_pad_horizontal,
    wanbeiyu_hal_spst_switch_t *circle_pad_horizontal_switch,
    wanbeiyu_hal_idac_t *circle_pad_vertical,
    wanbeiyu_hal_spst_switch_t *circle_pad_vertical_switch) {
  assert(hal != NULL);
  assert(uart != NULL);
  assert(power != NULL);
  assert(home != NULL);
  assert(zr != NULL);
  assert(zl != NULL);
  assert(y != NULL);
  assert(x != NULL);
  assert(l != NULL);
  assert(r != NULL);
  assert(down != NULL);
  assert(up != NULL);
  assert(left != NULL);
  assert(right != NULL);
  assert(start != NULL);
  assert(select != NULL);
  assert(b != NULL);
  assert(a != NULL);
  assert(touch_screen_horizontal != NULL);
  assert(touch_screen_vertical != NULL);
  assert(touch_screen_switch != NULL);
  assert(c_stick_axis1 != NULL);
  assert(c_stick_axis1_switch != NULL);
  assert(c_stick_axis3 != NULL);
  assert(c_stick_axis3_switch != NULL);
  assert(circle_pad_horizontal != NULL);
  assert(circle_pad_horizontal_switch != NULL);
  assert(circle_pad_vertical != NULL);
  assert(circle_pad_vertical_switch != NULL);

  hal->uart = uart;
  hal->power = power;
  hal->home = home;
  hal->zr = zr;
  hal->zl = zl;
  hal->y = y;
  hal->x = x;
  hal->l = l;
  hal->r = r;
  hal->down = down;
  hal->up = up;
  hal->left = left;
  hal->right = right;
  hal->start = start;
  hal->select = select;
  hal->b = b;
  hal->a = a;
  hal->touch_screen.horizontal = touch_screen_horizontal;
  hal->touch_screen.vertical = touch_screen_vertical;
  hal->touch_screen.switch_ = touch_screen_switch;
  hal->c_stick.axis1 = c_stick_axis1;
  hal->c_stick.axis1_switch = c_stick_axis1_switch;
  hal->c_stick.axis3 = c_stick_axis3;
  hal->c_stick.axis3_switch = c_stick_axis3_switch;
  hal->circle_pad.horizontal = circle_pad_horizontal;
  hal->circle_pad.horizontal_switch = circle_pad_horizontal_switch;
  hal->circle_pad.vertical = circle_pad_vertical;
  hal->circle_pad.vertical_switch = circle_pad_vertical_switch;
}

#ifdef __cplusplus
}
#endif

#endif /* WANBEIYU_HAL_H */