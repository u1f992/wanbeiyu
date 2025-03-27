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

extern void wanbeiyu_parser_on_get(void);
extern void wanbeiyu_parser_on_set(wanbeiyu_uint8_t const *);

static struct {
  enum {
    WANBEIYU_PARSER_STATE_INITIAL,
    WANBEIYU_PARSER_STATE_0,
    WANBEIYU_PARSER_STATE_1,
    WANBEIYU_PARSER_STATE_2,
    WANBEIYU_PARSER_STATE_3,
    WANBEIYU_PARSER_STATE_4,
    WANBEIYU_PARSER_STATE_5,
    WANBEIYU_PARSER_STATE_6,
    WANBEIYU_PARSER_STATE_7,
    WANBEIYU_PARSER_STATE_8
  } state;
  wanbeiyu_uint8_t buffer[9];
} wanbeiyu_parser;

static WANBEIYU_INLINE void wanbeiyu_parser_reset(void) {
  wanbeiyu_parser.state = WANBEIYU_PARSER_STATE_INITIAL;
}

static WANBEIYU_INLINE void wanbeiyu_parser_feed(wanbeiyu_uint8_t c) {
  switch (wanbeiyu_parser.state) {
  case WANBEIYU_PARSER_STATE_INITIAL:
    if (c == WANBEIYU_COMMAND_GET_STATE) {
      wanbeiyu_parser_on_get();
    }
    if (c == WANBEIYU_COMMAND_SET_STATE) {
      wanbeiyu_parser.state++;
    }
    break;
  case WANBEIYU_PARSER_STATE_0:
    /* FALLTHROUGH */
  case WANBEIYU_PARSER_STATE_1:
    /* FALLTHROUGH */
  case WANBEIYU_PARSER_STATE_2:
    /* FALLTHROUGH */
  case WANBEIYU_PARSER_STATE_3:
    /* FALLTHROUGH */
  case WANBEIYU_PARSER_STATE_4:
    /* FALLTHROUGH */
  case WANBEIYU_PARSER_STATE_5:
    /* FALLTHROUGH */
  case WANBEIYU_PARSER_STATE_6:
    /* FALLTHROUGH */
  case WANBEIYU_PARSER_STATE_7:
    wanbeiyu_parser.buffer[(wanbeiyu_parser.state++ - 1)] = c;
    break;
  case WANBEIYU_PARSER_STATE_8:
    wanbeiyu_parser.buffer[wanbeiyu_parser.state - 1] = c;
    wanbeiyu_parser_on_set(wanbeiyu_parser.buffer);
    wanbeiyu_parser.state = WANBEIYU_PARSER_STATE_INITIAL;
    break;
  default:
    assert(0);
    wanbeiyu_parser.state = WANBEIYU_PARSER_STATE_INITIAL;
    break;
  }
}

#ifdef __cplusplus
}
#endif

#endif /* WANBEIYU_PARSER_H */