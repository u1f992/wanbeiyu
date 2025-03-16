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

#ifndef WANBEIYU_HAL_IDAC_H
#define WANBEIYU_HAL_IDAC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../compat.h"

/**
 * Interface for a current source-sink D/A converter.
 */
typedef struct wanbeiyu_hal_idac_t {
  void (*source)(struct wanbeiyu_hal_idac_t *, wanbeiyu_uint8_t);
  void (*sink)(struct wanbeiyu_hal_idac_t *, wanbeiyu_uint8_t);
} wanbeiyu_hal_idac_t;

static WANBEIYU_INLINE void
wanbeiyu_hal_idac_init(wanbeiyu_hal_idac_t *idac,
                       void (*source)(wanbeiyu_hal_idac_t *, wanbeiyu_uint8_t),
                       void (*sink)(wanbeiyu_hal_idac_t *, wanbeiyu_uint8_t)) {
  assert(idac != NULL);
  assert(source != NULL);
  assert(sink != NULL);

  idac->source = source;
  idac->sink = sink;
}

static WANBEIYU_INLINE void wanbeiyu_hal_idac_source(wanbeiyu_hal_idac_t *idac,
                                                     wanbeiyu_uint8_t value) {
  assert(idac != NULL);

  idac->source(idac, value);
}

static WANBEIYU_INLINE void wanbeiyu_hal_idac_sink(wanbeiyu_hal_idac_t *idac,
                                                   wanbeiyu_uint8_t value) {
  assert(idac != NULL);

  idac->sink(idac, value);
}

#ifdef __cplusplus
}
#endif

#endif /* WANBEIYU_HAL_IDAC_H */