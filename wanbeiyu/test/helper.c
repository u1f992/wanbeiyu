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

#undef __STDC_VERSION__
#include <wanbeiyu/helper.h>

#define test_monotonic_increase(fn, start, end)                                \
  do {                                                                         \
    long i;                                                                    \
    for (i = (start); i < (end); i++) {                                        \
      assert((fn)(i) <= (fn)(i + 1));                                          \
    }                                                                          \
  } while (0)

int main(void) {
  assert(0 == wanbeiyu_helper_abs(0));
  assert(127 == wanbeiyu_helper_abs(-127));
  assert(127 == wanbeiyu_helper_abs(127));
  assert(255 == wanbeiyu_helper_abs(-255));
  assert(255 == wanbeiyu_helper_abs(255));
  assert(INT_MAX == wanbeiyu_helper_abs(INT_MIN + 1));
  assert(INT_MAX == wanbeiyu_helper_abs(INT_MAX));

  assert(0 == wanbeiyu_helper_map_127_to_255(0));
  assert(255 == wanbeiyu_helper_map_127_to_255(127));
  test_monotonic_increase(wanbeiyu_helper_map_127_to_255, 0, 127);

  assert(0 == wanbeiyu_helper_map_319_to_510(0));
  assert(510 == wanbeiyu_helper_map_319_to_510(319));
  test_monotonic_increase(wanbeiyu_helper_map_319_to_510, 0, 319);

  assert(0 == wanbeiyu_helper_map_239_to_255(0));
  assert(255 == wanbeiyu_helper_map_239_to_255(239));
  test_monotonic_increase(wanbeiyu_helper_map_239_to_255, 0, 239);

  assert(0 == wanbeiyu_helper_map_255_to_127(0));
  assert(127 == wanbeiyu_helper_map_255_to_127(255));
  test_monotonic_increase(wanbeiyu_helper_map_255_to_127, 0, 255);

  return 0;
}