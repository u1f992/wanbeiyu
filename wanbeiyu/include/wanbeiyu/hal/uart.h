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

#define wanbeiyu_hal_uart_write(uart, buffer, length)                          \
  /* assert(uart != NULL); */                                                  \
  (uart)->write((uart), (buffer), (length))

#ifdef __cplusplus
}
#endif

#endif /* WANBEIYU_HAL_UART_H */