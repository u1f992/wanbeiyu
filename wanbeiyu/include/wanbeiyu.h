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

#ifndef WANBEIYU_H
#define WANBEIYU_H

#ifdef __cplusplus
extern "C" {
#endif

#include "wanbeiyu/buttons.h"
#include "wanbeiyu/c_stick.h"
#include "wanbeiyu/circle_pad.h"
#include "wanbeiyu/compat.h"
#include "wanbeiyu/parser.h"
#include "wanbeiyu/touch_screen.h"

#define WANBEIYU_HAL_UART_BUFFER_SIZE 64

void wanbeiyu_init(void);
void wanbeiyu_loop(void);

#ifdef __cplusplus
}
#endif

#endif /* WANBEIYU_H */