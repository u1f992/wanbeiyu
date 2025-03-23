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
  const wanbeiyu_hal_rdac_320_steps_t *horizontal;
  const wanbeiyu_hal_rdac_240_steps_t *vertical;
  const wanbeiyu_hal_spst_switch_t *switch_;
} wanbeiyu_hal_touch_screen_t;

typedef struct wanbeiyu_hal_c_stick_t {
  const wanbeiyu_hal_idac_t *axis1;
  const wanbeiyu_hal_spst_switch_t *axis1_switch;
  const wanbeiyu_hal_idac_t *axis3;
  const wanbeiyu_hal_spst_switch_t *axis3_switch;
} wanbeiyu_hal_c_stick_t;

typedef struct wanbeiyu_hal_circle_pad_t {
  const wanbeiyu_hal_idac_t *horizontal;
  const wanbeiyu_hal_spst_switch_t *horizontal_switch;
  const wanbeiyu_hal_idac_t *vertical;
  const wanbeiyu_hal_spst_switch_t *vertical_switch;
} wanbeiyu_hal_circle_pad_t;

typedef struct wanbeiyu_hal_t {
  const wanbeiyu_hal_uart_t *uart;
  const wanbeiyu_hal_spst_switch_t *power;
  const wanbeiyu_hal_spst_switch_t *home;
  const wanbeiyu_hal_spst_switch_t *zr;
  const wanbeiyu_hal_spst_switch_t *zl;
  const wanbeiyu_hal_spst_switch_t *y;
  const wanbeiyu_hal_spst_switch_t *x;
  const wanbeiyu_hal_spst_switch_t *l;
  const wanbeiyu_hal_spst_switch_t *r;
  const wanbeiyu_hal_spst_switch_t *down;
  const wanbeiyu_hal_spst_switch_t *up;
  const wanbeiyu_hal_spst_switch_t *left;
  const wanbeiyu_hal_spst_switch_t *right;
  const wanbeiyu_hal_spst_switch_t *start;
  const wanbeiyu_hal_spst_switch_t *select;
  const wanbeiyu_hal_spst_switch_t *b;
  const wanbeiyu_hal_spst_switch_t *a;
  const wanbeiyu_hal_touch_screen_t touch_screen;
  const wanbeiyu_hal_c_stick_t c_stick;
  const wanbeiyu_hal_circle_pad_t circle_pad;
} wanbeiyu_hal_t;

#ifdef __cplusplus
}
#endif

#endif /* WANBEIYU_HAL_H */