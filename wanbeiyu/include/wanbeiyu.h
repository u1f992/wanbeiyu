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

#include "wanbeiyu/compat.h"
#include "wanbeiyu/console.h"
#include "wanbeiyu/hal.h"

#define WANBEIYU_COMMAND_GET_CONSOLE_STATE 0xf3
#define WANBEIYU_COMMAND_SET_CONSOLE_STATE 0x4a

typedef enum wanbeiyu_state_t {
  WANBEIYU_STATE_INITIAL,
  WANBEIYU_STATE_0,
  WANBEIYU_STATE_1,
  WANBEIYU_STATE_2,
  WANBEIYU_STATE_3,
  WANBEIYU_STATE_4,
  WANBEIYU_STATE_5,
  WANBEIYU_STATE_6,
  WANBEIYU_STATE_7,
  WANBEIYU_STATE_8
} wanbeiyu_state_t;

typedef struct wanbeiyu_t {
  wanbeiyu_uint8_t buffer[9];
  wanbeiyu_state_t state;
  wanbeiyu_console_state_t console_state;
  wanbeiyu_console_t console;
  wanbeiyu_hal_uart_t *uart;
} wanbeiyu_t;

static WANBEIYU_INLINE void wanbeiyu_init(wanbeiyu_t *wanbeiyu,
                                          wanbeiyu_hal_t *hal) {
  assert(wanbeiyu != NULL);
  assert(hal != NULL);

  wanbeiyu->state = WANBEIYU_STATE_INITIAL;
  wanbeiyu_console_init(&(wanbeiyu->console), hal);
  wanbeiyu->uart = hal->uart;
}

static WANBEIYU_INLINE void wanbeiyu_on_data(wanbeiyu_t *wanbeiyu,
                                             const wanbeiyu_uint8_t *buffer,
                                             size_t length) {
  size_t i = 0;

  assert(wanbeiyu != NULL);

  for (i = 0; i < length; i++) {
    wanbeiyu_uint8_t c = buffer[i];

    switch (wanbeiyu->state) {
    case WANBEIYU_STATE_INITIAL:
      if (c == WANBEIYU_COMMAND_GET_CONSOLE_STATE) {
        wanbeiyu_console_state_serialize(&(wanbeiyu->console_state),
                                         wanbeiyu->buffer);
        wanbeiyu_hal_uart_write(wanbeiyu->uart, wanbeiyu->buffer,
                                sizeof(wanbeiyu->buffer));
      }
      if (c != WANBEIYU_COMMAND_SET_CONSOLE_STATE) {
        wanbeiyu->state++;
      }
      break;
    case WANBEIYU_STATE_0:
      /* FALLTHROUGH */
    case WANBEIYU_STATE_1:
      /* FALLTHROUGH */
    case WANBEIYU_STATE_2:
      /* FALLTHROUGH */
    case WANBEIYU_STATE_3:
      /* FALLTHROUGH */
    case WANBEIYU_STATE_4:
      /* FALLTHROUGH */
    case WANBEIYU_STATE_5:
      /* FALLTHROUGH */
    case WANBEIYU_STATE_6:
      /* FALLTHROUGH */
    case WANBEIYU_STATE_7:
      wanbeiyu->buffer[(wanbeiyu->state++ - 1)] = c;
      break;
    case WANBEIYU_STATE_8:
      wanbeiyu->buffer[wanbeiyu->state - 1] = c;
      wanbeiyu_console_state_deserialize(wanbeiyu->buffer,
                                         &(wanbeiyu->console_state));
      wanbeiyu_console_set(&(wanbeiyu->console), &(wanbeiyu->console_state));
      /* FALLTHROUGH */

    default:
      wanbeiyu->state = WANBEIYU_STATE_INITIAL;
      break;
    }
  }
}

#ifdef __cplusplus
}
#endif

#endif /* WANBEIYU_H */