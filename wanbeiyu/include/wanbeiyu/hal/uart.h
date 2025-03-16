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

#ifndef WANBEIYU_HAL_UART_H
#define WANBEIYU_HAL_UART_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../compat.h"

typedef struct wanbeiyu_hal_uart_t {
  void (*write)(struct wanbeiyu_hal_uart_t *, const wanbeiyu_uint8_t *, size_t);
} wanbeiyu_hal_uart_t;

static WANBEIYU_INLINE void wanbeiyu_hal_uart_init(
    wanbeiyu_hal_uart_t *uart,
    void (*write)(wanbeiyu_hal_uart_t *, const wanbeiyu_uint8_t *, size_t)) {
  assert(uart != NULL);
  assert(write != NULL);

  uart->write = write;
}

static WANBEIYU_INLINE void
wanbeiyu_hal_uart_write(wanbeiyu_hal_uart_t *uart,
                        const wanbeiyu_uint8_t *buffer, size_t length) {
  assert(uart != NULL);

  uart->write(uart, buffer, length);
}

#ifdef __cplusplus
}
#endif

#endif /* WANBEIYU_HAL_UART_H */