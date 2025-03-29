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

#ifndef WANBEIYU_PARSER_H
#define WANBEIYU_PARSER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "compat.h"

#define WANBEIYU_COMMAND_GET_STATE 0xf3
#define WANBEIYU_COMMAND_SET_STATE 0x4a

void wanbeiyu_parser_reset(void);
void wanbeiyu_parser_feed(wanbeiyu_uint8_t);

#ifdef __cplusplus
}
#endif

#endif /* WANBEIYU_PARSER_H */