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

#ifndef WANBEIYU_HELPER_H
#define WANBEIYU_HELPER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "compat.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"

static WANBEIYU_INLINE int wanbeiyu_helper_abs(int value) {
  assert(INT_MIN + 1 <= value);
  return value > 0 ? value : -value;
}

/*
 * Integer scaling with rounding
 *
 * To map an integer value `x` from a domain of size `D` to a range of size `N`
 * with minimal quantization error, use the following formula:
 *
 *     (x * N + D / 2) / D
 *
 * This technique approximates real-number scaling with rounding to the nearest
 * integer. Adding `D / 2` before the division helps reduce truncation error
 * caused by integer arithmetic.
 */

static WANBEIYU_INLINE wanbeiyu_uint8_t
wanbeiyu_helper_map_127_to_255(wanbeiyu_uint8_t value) {
  assert(value <= 127);
  return (value * 255 + 127 / 2) / 127;
}

/* clang-format off */

/**
 * Inspired by "[AN-582 Resolution Enhancements of Digital Potentiometers with Multiple Devices](https://www.analog.com/media/en/technical-documentation/application-notes/an-582.pdf)."
 * - (ja-JP) [複数のデバイスによるデジタル・ポテンショメータの分解能の向上](https://www.analog.com/media/jp/technical-documentation/application-notes/an-582_jp.pdf)
 *
 *   |
 *  .-. R2
 *  | |<--o
 *  '-'   |
 *   |   .-. R3
 *   x   | |<--
 *   x   '-'
 *   |    |
 *  .-.   |
 *  | |<--o
 *  '-' R1
 *   |
 *
 * | value | R1, R2 | R3  |
 * | ----- | ------ | --- |
 * | 0     | 0      | 0   |
 * | 1     | 0      | 1   |
 * | 2     | 0      | 2   |
 * | ...   |        |     |
 * | 254   | 0      | 254 |
 * | 255   | 0      | 255 |
 * | 256   | 1      | 255 |
 * | 257   | 2      | 255 |
 * | ...   |        |     |
 * | 509   | 254    | 255 |
 * | 510   | 255    | 255 |
 */
static WANBEIYU_INLINE wanbeiyu_uint16_t
wanbeiyu_helper_map_319_to_510(wanbeiyu_uint16_t value) {
  /* clang-format on */
  wanbeiyu_uint16_t ret;
  assert(value <= 319);
  ret = (value * 510 + 319 / 2) / 319;
  assert(ret <= 510);
  return ret;
}

static WANBEIYU_INLINE wanbeiyu_uint8_t
wanbeiyu_helper_map_239_to_255(wanbeiyu_uint8_t value) {
  assert(value <= 239);
  return (value * 255 + 239 / 2) / 239;
}

static WANBEIYU_INLINE wanbeiyu_uint8_t
wanbeiyu_helper_map_255_to_127(wanbeiyu_uint8_t value) {
  wanbeiyu_uint8_t ret = (value * 127 + 255 / 2) / 255;
  assert(ret <= 127);
  return ret;
}

#pragma GCC diagnostic pop

#ifdef __cplusplus
}
#endif

#endif /* WANBEIYU_HELPER_H */