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

#ifndef WANBEIYU_C_STICK_H
#define WANBEIYU_C_STICK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "hal.h"
#include "helper.h"
#include "state.h"

/**
 *   1+         3+
 *     \_     _/
 *       \_ _/
 *        _X_
 *      _/   \_
 *     /       \
 *   3-         1-
 * +: source, -: sink
 *
 * (Pin numbers of Hirose FH33-4S-1SH(10))
 */
void wanbeiyu_c_stick_set(wanbeiyu_state_t const *);

#ifdef __cplusplus
}
#endif

#endif /* WANBEIYU_C_STICK_H */