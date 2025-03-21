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

#ifndef WANBEIYU_HAL_RDAC_320_STEPS_H
#define WANBEIYU_HAL_RDAC_320_STEPS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../compat.h"

/**
 * Interface for a digital potentiometer with 320 steps.
 * position=0, W=B; position=319, W=A.
 *
 *   | A
 *  .-.
 *  | |<-- W
 *  '-'
 *   | B
 */
typedef struct wanbeiyu_hal_rdac_320_steps_t {
  void (*set_wiper_position)(struct wanbeiyu_hal_rdac_320_steps_t *,
                             wanbeiyu_uint16_t);
} wanbeiyu_hal_rdac_320_steps_t;

static WANBEIYU_INLINE void wanbeiyu_hal_rdac_320_steps_init(
    wanbeiyu_hal_rdac_320_steps_t *rdac,
    void (*set_wiper_position)(wanbeiyu_hal_rdac_320_steps_t *,
                               wanbeiyu_uint16_t)) {
  assert(rdac != NULL);
  assert(set_wiper_position != NULL);

  rdac->set_wiper_position = set_wiper_position;
}

static WANBEIYU_INLINE void wanbeiyu_hal_rdac_320_steps_set_wiper_position(
    wanbeiyu_hal_rdac_320_steps_t *rdac, wanbeiyu_uint16_t position) {
  assert(rdac != NULL);
  assert(position < 320);

  rdac->set_wiper_position(rdac, position);
}

#ifdef __cplusplus
}
#endif

#endif /* WANBEIYU_HAL_RDAC_320_STEPS_H */