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

#include <wanbeiyu/touch_screen.h>

extern void wanbeiyu_hal_rdac_touch_screen_pin_2_4_set(wanbeiyu_uint16_t);
extern void wanbeiyu_hal_rdac_touch_screen_pin_3_1_set(wanbeiyu_uint8_t);
extern void
    wanbeiyu_hal_spst_switch_touch_screen_set(wanbeiyu_hal_spst_switch_state_t);

void wanbeiyu_touch_screen_set(wanbeiyu_state_t const *state) {
  wanbeiyu_touch_screen_state_t *touch_screen;
  assert(state != NULL);
  touch_screen = state->touch_screen;
  if (touch_screen == NULL) {
    wanbeiyu_hal_spst_switch_touch_screen_set(WANBEIYU_HAL_SPST_SWITCH_OPEN);
  } else {
    wanbeiyu_hal_rdac_touch_screen_pin_2_4_set(
        touch_screen->x < 320 ? touch_screen->x : 319);
    wanbeiyu_hal_rdac_touch_screen_pin_3_1_set(
        touch_screen->y < 240 ? touch_screen->y : 239);
    wanbeiyu_hal_spst_switch_touch_screen_set(WANBEIYU_HAL_SPST_SWITCH_CLOSE);
  }
}