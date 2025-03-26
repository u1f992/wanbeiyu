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

#ifndef WANBEIYU_CONSOLE_BUTTON_H
#define WANBEIYU_CONSOLE_BUTTON_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../hal.h"
#include "state.h"

/**
 *      ^ 1v8
 *      |
 *     .-.
 *     | |
 *     '-'
 *      |    _|_
 *  ----o----o o-.
 *               |
 *               v GND
 */
static WANBEIYU_INLINE void
wanbeiyu_console_buttons_set(wanbeiyu_uint16_t states) {
  wanbeiyu_hal_spst_switch_buttons_power_set((states >> 15) & 1);
  wanbeiyu_hal_spst_switch_buttons_home_set((states >> 14) & 1);
  wanbeiyu_hal_spst_switch_buttons_zr_set((states >> 13) & 1);
  wanbeiyu_hal_spst_switch_buttons_zl_set((states >> 12) & 1);
  wanbeiyu_hal_spst_switch_buttons_y_set((states >> 11) & 1);
  wanbeiyu_hal_spst_switch_buttons_x_set((states >> 10) & 1);
  wanbeiyu_hal_spst_switch_buttons_l_set((states >> 9) & 1);
  wanbeiyu_hal_spst_switch_buttons_r_set((states >> 8) & 1);
  wanbeiyu_hal_spst_switch_buttons_down_set((states >> 7) & 1);
  wanbeiyu_hal_spst_switch_buttons_up_set((states >> 6) & 1);
  wanbeiyu_hal_spst_switch_buttons_left_set((states >> 5) & 1);
  wanbeiyu_hal_spst_switch_buttons_right_set((states >> 4) & 1);
  wanbeiyu_hal_spst_switch_buttons_start_set((states >> 3) & 1);
  wanbeiyu_hal_spst_switch_buttons_select_set((states >> 2) & 1);
  wanbeiyu_hal_spst_switch_buttons_b_set((states >> 1) & 1);
  wanbeiyu_hal_spst_switch_buttons_a_set((states >> 0) & 1);
}

#ifdef __cplusplus
}
#endif

#endif /* WANBEIYU_CONSOLE_BUTTON_H */