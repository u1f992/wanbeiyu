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

#include <wanbeiyu.h>

void wanbeiyu_hal_uart_read(wanbeiyu_uint8_t *, size_t *);
void wanbeiyu_hal_uart_write(wanbeiyu_uint8_t const *, size_t);
void wanbeiyu_hook(void);

static struct {
  wanbeiyu_uint8_t uart_buffer[WANBEIYU_HAL_UART_BUFFER_SIZE];
  wanbeiyu_state_t state;
} wanbeiyu;

void wanbeiyu_parser_on_get(void) {
  wanbeiyu_uint8_t buffer[9];
  wanbeiyu_state_serialize(&(wanbeiyu.state), buffer);
  wanbeiyu_hal_uart_write(buffer, sizeof(buffer));
}

static WANBEIYU_INLINE void
wanbeiyu_console_set(wanbeiyu_state_t const *state) {
  assert(state != NULL);

  wanbeiyu_buttons_set(state);
  wanbeiyu_touch_screen_set(state);
  wanbeiyu_c_stick_set(state);
  wanbeiyu_circle_pad_set(state);
}

void wanbeiyu_parser_on_set(wanbeiyu_uint8_t const *buffer) {
  wanbeiyu_state_deserialize(buffer, &(wanbeiyu.state));
  wanbeiyu_console_set(&(wanbeiyu.state));
  wanbeiyu_hook();
}

void wanbeiyu_init(void) {
  wanbeiyu_state_reset(&(wanbeiyu.state));
  wanbeiyu_console_set(&(wanbeiyu.state));
  wanbeiyu_parser_reset();
}

void wanbeiyu_loop(void) {
  size_t i;
  size_t length;

  while (1) {
    wanbeiyu_hal_uart_read(wanbeiyu.uart_buffer, &length);
    if (length == 0) {
      wanbeiyu_parser_reset();
      break;
    }

    for (i = 0; i < length; i++) {
      wanbeiyu_uint8_t c = wanbeiyu.uart_buffer[i];
      wanbeiyu_parser_feed(c);
    }
  }
}