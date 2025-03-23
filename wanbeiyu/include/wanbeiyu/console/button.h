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

#ifndef WANBEIYU_CONSOLE_BUTTON_H
#define WANBEIYU_CONSOLE_BUTTON_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../hal/spst_switch.h"
#include "state.h"

/**
 *      ^ 1v8
 *      |
 *     .-.
 *     | |
 *     '-'
 *      |    _|_
 *  ----o----o o-.
 *               |
 *               v GND
 */
typedef struct wanbeiyu_console_button_t {
  wanbeiyu_hal_spst_switch_t *switch_;
} wanbeiyu_console_button_t;

static WANBEIYU_INLINE void
wanbeiyu_console_button_init(wanbeiyu_console_button_t *button,
                             wanbeiyu_hal_spst_switch_t *switch_) {
  assert(button != NULL);
  assert(switch_ != NULL);

  button->switch_ = switch_;
}

#define wanbeiyu_console_button_hold(button)                                   \
  /* assert((button) != NULL); */                                              \
  wanbeiyu_hal_spst_switch_close((button)->switch_)

#define wanbeiyu_console_button_release(button)                                \
  /* assert((button) != NULL); */                                              \
  wanbeiyu_hal_spst_switch_open((button)->switch_)

#ifdef __cplusplus
}
#endif

#endif /* WANBEIYU_CONSOLE_BUTTON_H */