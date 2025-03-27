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
#include "wanbeiyu/touch_screen.h"

extern void wanbeiyu_hal_uart_read(wanbeiyu_uint8_t *, size_t *);
extern void wanbeiyu_hal_uart_write(const wanbeiyu_uint8_t *, size_t);

#define WANBEIYU_COMMAND_GET_STATE 0xf3
#define WANBEIYU_COMMAND_SET_STATE 0x4a

#define WANBEIYU_BUFFER_SIZE 64
#define WANBEIYU_CONSOLE_SET_SIZE 4

typedef struct wanbeiyu_t {
  void (*console_set[WANBEIYU_CONSOLE_SET_SIZE])(const wanbeiyu_state_t *);
  wanbeiyu_uint8_t buffer[WANBEIYU_BUFFER_SIZE];
  enum {
    WANBEIYU_PARSE_STATE_INITIAL,
    WANBEIYU_PARSE_STATE_0,
    WANBEIYU_PARSE_STATE_1,
    WANBEIYU_PARSE_STATE_2,
    WANBEIYU_PARSE_STATE_3,
    WANBEIYU_PARSE_STATE_4,
    WANBEIYU_PARSE_STATE_5,
    WANBEIYU_PARSE_STATE_6,
    WANBEIYU_PARSE_STATE_7,
    WANBEIYU_PARSE_STATE_8
  } parse_state;
  wanbeiyu_uint8_t command_buffer[9];
  wanbeiyu_state_t state;
} wanbeiyu_t;

static WANBEIYU_INLINE void
wanbeiyu_console_set(void (*const console_set[])(const wanbeiyu_state_t *),
                     size_t length, const wanbeiyu_state_t *state) {
  size_t i;

  assert(console_set != NULL);
  assert(state != NULL);

  for (i = 0; i < length; i++) {
    console_set[i](state);
  }
}

static WANBEIYU_INLINE void wanbeiyu_init(wanbeiyu_t *wanbeiyu) {
  assert(wanbeiyu != NULL);

  wanbeiyu->console_set[0] = wanbeiyu_buttons_set;
  wanbeiyu->console_set[1] = wanbeiyu_touch_screen_set;
  wanbeiyu->console_set[2] = wanbeiyu_c_stick_set;
  wanbeiyu->console_set[3] = wanbeiyu_circle_pad_set;

  wanbeiyu->parse_state = WANBEIYU_PARSE_STATE_INITIAL;
  wanbeiyu_state_reset(&(wanbeiyu->state));
  wanbeiyu_console_set(wanbeiyu->console_set, WANBEIYU_CONSOLE_SET_SIZE,
                       &(wanbeiyu->state));
}

static WANBEIYU_INLINE void wanbeiyu_loop(wanbeiyu_t *wanbeiyu) {
  size_t i;
  size_t length;

  assert(wanbeiyu != NULL);

  while (1) {
    wanbeiyu_hal_uart_read(wanbeiyu->buffer, &length);
    if (length == 0) {
      wanbeiyu->parse_state = WANBEIYU_PARSE_STATE_INITIAL;
      break;
    }

    for (i = 0; i < length; i++) {
      wanbeiyu_uint8_t c = wanbeiyu->buffer[i];

      switch (wanbeiyu->parse_state) {
      case WANBEIYU_PARSE_STATE_INITIAL:
        if (c == WANBEIYU_COMMAND_GET_STATE) {
          wanbeiyu_state_serialize(&(wanbeiyu->state),
                                   wanbeiyu->command_buffer);
          wanbeiyu_hal_uart_write(wanbeiyu->command_buffer,
                                  sizeof(wanbeiyu->command_buffer));
        }
        if (c == WANBEIYU_COMMAND_SET_STATE) {
          wanbeiyu->parse_state++;
        }
        break;
      case WANBEIYU_PARSE_STATE_0:
        /* FALLTHROUGH */
      case WANBEIYU_PARSE_STATE_1:
        /* FALLTHROUGH */
      case WANBEIYU_PARSE_STATE_2:
        /* FALLTHROUGH */
      case WANBEIYU_PARSE_STATE_3:
        /* FALLTHROUGH */
      case WANBEIYU_PARSE_STATE_4:
        /* FALLTHROUGH */
      case WANBEIYU_PARSE_STATE_5:
        /* FALLTHROUGH */
      case WANBEIYU_PARSE_STATE_6:
        /* FALLTHROUGH */
      case WANBEIYU_PARSE_STATE_7:
        wanbeiyu->command_buffer[(wanbeiyu->parse_state++ - 1)] = c;
        break;
      case WANBEIYU_PARSE_STATE_8:
        wanbeiyu->command_buffer[wanbeiyu->parse_state - 1] = c;
        wanbeiyu_state_deserialize(wanbeiyu->command_buffer,
                                   &(wanbeiyu->state));
        wanbeiyu_console_set(wanbeiyu->console_set, WANBEIYU_CONSOLE_SET_SIZE,
                             &(wanbeiyu->state));
        /* FALLTHROUGH */
      default:
        wanbeiyu->parse_state = WANBEIYU_PARSE_STATE_INITIAL;
        break;
      }
    }
  }
}

#ifdef __cplusplus
}
#endif

#endif /* WANBEIYU_H */