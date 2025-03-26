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

/* extern void wanbeiyu_hal_uart_read(wanbeiyu_uint8_t *, size_t *); */
extern void wanbeiyu_hal_uart_write(const wanbeiyu_uint8_t *, size_t);

typedef enum wanbeiyu_hal_idac_mode_t {
  WANBEIYU_HAL_IDAC_SINK,
  WANBEIYU_HAL_IDAC_SOURCE
} wanbeiyu_hal_idac_mode_t;

typedef enum wanbeiyu_hal_spst_switch_state_t {
  WANBEIYU_HAL_SPST_SWITCH_OPEN,
  WANBEIYU_HAL_SPST_SWITCH_CLOSE
} wanbeiyu_hal_spst_switch_state_t;

#ifdef __cplusplus
}
#endif

#endif /* WANBEIYU_HAL_H */