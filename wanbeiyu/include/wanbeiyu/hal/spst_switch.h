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

#ifndef WANBEIYU_HAL_SPST_SWITCH_H
#define WANBEIYU_HAL_SPST_SWITCH_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../compat.h"

/**
 * Interface for a SPST analog switch.
 *
 *   |
 *   o |
 *     |--
 *   o |
 *   |
 */
typedef struct wanbeiyu_hal_spst_switch_t {
  void (*open)(struct wanbeiyu_hal_spst_switch_t *);
  void (*close)(struct wanbeiyu_hal_spst_switch_t *);
} wanbeiyu_hal_spst_switch_t;

static WANBEIYU_INLINE void
wanbeiyu_hal_spst_switch_init(wanbeiyu_hal_spst_switch_t *switch_,
                              void (*open)(wanbeiyu_hal_spst_switch_t *),
                              void (*close)(wanbeiyu_hal_spst_switch_t *)) {
  assert(switch_ != NULL);
  assert(open != NULL);
  assert(close != NULL);

  switch_->open = open;
  switch_->close = close;
}

static WANBEIYU_INLINE void
wanbeiyu_hal_spst_switch_open(wanbeiyu_hal_spst_switch_t *switch_) {
  assert(switch_ != NULL);

  switch_->open(switch_);
}

static WANBEIYU_INLINE void
wanbeiyu_hal_spst_switch_close(wanbeiyu_hal_spst_switch_t *switch_) {
  assert(switch_ != NULL);

  switch_->close(switch_);
}

#ifdef __cplusplus
}
#endif

#endif /* WANBEIYU_HAL_SPST_SWITCH_H */