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

#ifndef WANBEIYU_CIRCLE_PAD_H
#define WANBEIYU_CIRCLE_PAD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "hal.h"
#include "helper.h"
#include "state.h"

/**
 * ```
 *   ^ 1v8
 *   |
 *   o-------------o
 *   |             |
 *   |            .-.
 *   |            | |<-- Y
 *   |            '-'
 *   |     ___     |
 *   o----|___|----o
 *          ^      |
 *          |      v GND
 *          X
 *
 *           4+
 *           |
 *           |
 *  2+ ------+------ 2-
 *           |
 *           |
 *           4-
 * +: source, -: sink
 *
 * 1: GND; 2: X; 3: 1v8; 4: Y
 * (Pin numbers of Molex 5014610491)
 * ```
 */
void wanbeiyu_circle_pad_set(wanbeiyu_state_t const *);

#ifdef __cplusplus
}
#endif

#endif /* WANBEIYU_CIRCLE_PAD_H */