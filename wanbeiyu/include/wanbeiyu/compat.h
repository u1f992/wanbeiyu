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

#ifndef WANBEIYU_COMPAT_H
#define WANBEIYU_COMPAT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <assert.h>
#include <limits.h>
#include <stddef.h>

#if __STDC_VERSION__ >= 199901L

#include <stdbool.h>
#include <stdint.h>

#define WANBEIYU_INLINE inline

#define WANBEIYU_UINT8_MAX UINT8_MAX
typedef uint8_t wanbeiyu_uint8_t;

#define WANBEIYU_UINT16_MAX UINT16_MAX
typedef uint16_t wanbeiyu_uint16_t;

#else /* __STDC_VERSION__ < 199901L */

#define WANBEIYU_INLINE

#define WANBEIYU_UINT8_MAX 0xff
typedef unsigned char wanbeiyu_uint8_t;

#define WANBEIYU_UINT16_MAX 0xffff
#if USHRT_MAX == WANBEIYU_UINT16_MAX
typedef unsigned short wanbeiyu_uint16_t;
#elif UINT_MAX == WANBEIYU_UINT16_MAX
typedef unsigned int wanbeiyu_uint16_t;
#elif ULONG_MAX == WANBEIYU_UINT16_MAX
typedef unsigned long wanbeiyu_uint16_t;
#else
#error "16-bit unsigned integer type is not available on this platform."
#endif

#endif /* __STDC_VERSION__ */

#ifdef __cplusplus
}
#endif

#endif /* WANBEIYU_COMPAT_H */