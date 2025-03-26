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

extern void wanbeiyu_hal_buttons_power_set(wanbeiyu_hal_spst_switch_state_t);
extern void wanbeiyu_hal_buttons_home_set(wanbeiyu_hal_spst_switch_state_t);
extern void wanbeiyu_hal_buttons_zr_set(wanbeiyu_hal_spst_switch_state_t);
extern void wanbeiyu_hal_buttons_zl_set(wanbeiyu_hal_spst_switch_state_t);
extern void wanbeiyu_hal_buttons_y_set(wanbeiyu_hal_spst_switch_state_t);
extern void wanbeiyu_hal_buttons_x_set(wanbeiyu_hal_spst_switch_state_t);
extern void wanbeiyu_hal_buttons_l_set(wanbeiyu_hal_spst_switch_state_t);
extern void wanbeiyu_hal_buttons_r_set(wanbeiyu_hal_spst_switch_state_t);
extern void wanbeiyu_hal_buttons_down_set(wanbeiyu_hal_spst_switch_state_t);
extern void wanbeiyu_hal_buttons_up_set(wanbeiyu_hal_spst_switch_state_t);
extern void wanbeiyu_hal_buttons_left_set(wanbeiyu_hal_spst_switch_state_t);
extern void wanbeiyu_hal_buttons_right_set(wanbeiyu_hal_spst_switch_state_t);
extern void wanbeiyu_hal_buttons_start_set(wanbeiyu_hal_spst_switch_state_t);
extern void wanbeiyu_hal_buttons_select_set(wanbeiyu_hal_spst_switch_state_t);
extern void wanbeiyu_hal_buttons_b_set(wanbeiyu_hal_spst_switch_state_t);
extern void wanbeiyu_hal_buttons_a_set(wanbeiyu_hal_spst_switch_state_t);

static void (*const wanbeiyu_internal_buttons_map[16])(
    wanbeiyu_hal_spst_switch_state_t) = {
    wanbeiyu_hal_buttons_a_set,      wanbeiyu_hal_buttons_b_set,
    wanbeiyu_hal_buttons_select_set, wanbeiyu_hal_buttons_start_set,
    wanbeiyu_hal_buttons_right_set,  wanbeiyu_hal_buttons_left_set,
    wanbeiyu_hal_buttons_up_set,     wanbeiyu_hal_buttons_down_set,
    wanbeiyu_hal_buttons_r_set,      wanbeiyu_hal_buttons_l_set,
    wanbeiyu_hal_buttons_x_set,      wanbeiyu_hal_buttons_y_set,
    wanbeiyu_hal_buttons_zl_set,     wanbeiyu_hal_buttons_zr_set,
    wanbeiyu_hal_buttons_home_set,   wanbeiyu_hal_buttons_power_set};

static WANBEIYU_INLINE void
wanbeiyu_console_buttons_set(wanbeiyu_uint16_t states) {
  size_t i;
  for (i = 0; i < 16; ++i) {
    wanbeiyu_internal_buttons_map[i]((states & (1 << i))
                                         ? WANBEIYU_HAL_SPST_SWITCH_CLOSE
                                         : WANBEIYU_HAL_SPST_SWITCH_OPEN);
  }
}

#ifdef __cplusplus
}
#endif

#endif /* WANBEIYU_CONSOLE_BUTTON_H */