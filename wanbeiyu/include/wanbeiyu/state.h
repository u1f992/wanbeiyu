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

#ifndef WANBEIYU_STATE_H
#define WANBEIYU_STATE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "compat.h"

/*

 */
/* clang-format on */

/**
 * @brief Represents the Touch Screen input state.
 */
typedef struct wanbeiyu_touch_screen_state_t {
  /**
   * @brief Horizontal coordinate.
   *
   * The origin is at the left edge; X increases to the right.
   *
   * This value is not constrained to the screen width (max 319). It is clamped
   * by ::wanbeiyu_touch_screen_set before use.
   */
  wanbeiyu_uint16_t x;
  /**
   * @brief Vertical coordinate.
   *
   * The origin is at the top edge; Y increases downward.
   *
   * This value is not constrained to the screen height (max 239). It is clamped
   * by ::wanbeiyu_touch_screen_set before use.
   */
  wanbeiyu_uint8_t y;
} wanbeiyu_touch_screen_state_t;

/**
 * @brief Represents the C Stick input state.
 */
typedef struct wanbeiyu_c_stick_state_t {
  /**
   * @brief Horizontal coordinate.
   *
   * A NULL pointer indicates that the horizontal input is not present.
   *
   * If non-NULL, the origin is at the left edge; X increases to the right.
   */
  wanbeiyu_uint8_t *x;
  /**
   * @brief Vertical coordinate.
   *
   * A NULL pointer indicates that the vertical input is not present.
   *
   * If non-NULL, the origin is at the bottom edge; Y increases upward.
   */
  wanbeiyu_uint8_t *y;
} wanbeiyu_c_stick_state_t;

/**
 * @brief Represents the Circle Pad input state.
 */
typedef struct wanbeiyu_circle_pad_state_t {
  /**
   * @brief Horizontal coordinate.
   *
   * A NULL pointer indicates that the horizontal input is not present.
   *
   * If non-NULL, the origin is at the left edge; X increases to the right.
   */
  wanbeiyu_uint8_t *x;
  /**
   * @brief Vertical coordinate.
   *
   * A NULL pointer indicates that the vertical input is not present.
   *
   * If non-NULL, the origin is at the bottom edge; Y increases upward.
   */
  wanbeiyu_uint8_t *y;
} wanbeiyu_circle_pad_state_t;

/**
 * @brief Represents the entire input state.
 */
typedef struct wanbeiyu_state_t {
  /**
   * @brief Bitfield representing button states. A value of 1 indicates the
   * button is held; 0 indicates it is released.
   *
   * | Bit | Button |
   * | --- | ------ |
   * | 15  | Power  |
   * | 14  | Home   |
   * | 13  | ZR     |
   * | 12  | ZL     |
   * | 11  | Y      |
   * | 10  | X      |
   * | 9   | L      |
   * | 8   | R      |
   * | 7   | Down   |
   * | 6   | Up     |
   * | 5   | Left   |
   * | 4   | Right  |
   * | 3   | Start  |
   * | 2   | Select |
   * | 1   | B      |
   * | 0   | A      |
   */
  wanbeiyu_uint16_t buttons;
  /**
   * @brief Touch Screen state.
   *
   * A NULL pointer indicates that the input is not present.
   */
  wanbeiyu_touch_screen_state_t *touch_screen;
  /**
   * @brief C Stick state.
   */
  wanbeiyu_c_stick_state_t c_stick;
  /**
   * @brief Circle Pad state.
   */
  wanbeiyu_circle_pad_state_t circle_pad;
  wanbeiyu_uint8_t reserved_0;
  wanbeiyu_uint8_t reserved_1;

  /**
   * @brief Stash of the touch_screen instance. Used for testing purposes only.
   * Do not access outside of test codes.
   */
  wanbeiyu_touch_screen_state_t stash_touch_screen;
  /**
   * @brief Stash of the c_stick instance. Used for testing purposes only. Do
   * not access outside of test codes.
   */
  struct {
    wanbeiyu_uint8_t x;
    wanbeiyu_uint8_t y;
  } stash_c_stick;
  /**
   * @brief Stash of the circle_pad instance. Used for testing purposes only. Do
   * not access outside of test codes.
   */
  struct {
    wanbeiyu_uint8_t x;
    wanbeiyu_uint8_t y;
  } stash_circle_pad;
} wanbeiyu_state_t;

/**
 * @brief Resets the state to the neutral position.
 * @param state Pointer to the state structure.
 */
void wanbeiyu_state_reset(wanbeiyu_state_t *);
/* clang-format off */

/**
 * @brief Parses a 9-byte input and updates the state accordingly.
 * @param buffer Pointer to a 9-byte input array.
 * @param state Pointer to the state structure.
 * 
 * This order is derived from devkitPro, and originally comes from the
 * representation in memory on the actual console.
 *
 * According to devkitPro and Citra, the console internally uses a range of -156
 * to 156 for the C Stick and -154 to 154 for the Circle Pad. The up-right
 * direction is considered positive, with the center at (0,0). These values
 * apply to the uncalibrated case; the actual range may vary depending on
 * calibration.
 * 
 * A value of 1 indicates the component is held; 0 indicates it is released.
 *
 * - https://github.com/devkitPro/libctru/blob/1bafb08f347226fba439d14c7bb1f44e85d70978/libctru/include/3ds/services/hid.h#L10-L41
 * - http://3dbrew.org/wiki/HID_Shared_Memory
 *
 * | Byte | Bit | Description    |
 * | ---- | --- | -------------- |
 * |  0   |  7  | Power          |
 * |      |  6  | Home           |
 * |      |  5  | ZR             |
 * |      |  4  | ZL             |
 * |      |  3  | Y              |
 * |      |  2  | X              |
 * |      |  1  | L              |
 * |      |  0  | R              |
 * | ~~~~ | ~~~ | ~~~~~~~~~~~~~~ |
 * |  1   |  7  | Down           |
 * |      |  6  | Up             |
 * |      |  5  | Left           |
 * |      |  4  | Right          |
 * |      |  3  | Start          |
 * |      |  2  | Select         |
 * |      |  1  | B              |
 * |      |  0  | A              |
 * | ~~~~ | ~~~ | ~~~~~~~~~~~~~~ |
 * |  2   |  7  | Touch Screen   |
 * |      |  6  | C Stick X      |
 * |      |  5  | C Stick Y      |
 * |      |  4  | Circle Pad X   |
 * |      |  3  | Circle Pad Y   |
 * |      |  2  | (Reserved)     |
 * |      |  1  | (Reserved)     |
 * |      |  0  | \              |
 * | ~~~~ | ~~~ | ~~~~~~~~~~~~~~ |
 * |  3   |  7  |                |
 * |      |  6  |                |
 * |      |  5  | Touch Screen X |
 * |      |  4  | left-to-right  |
 * |      |  3  |                |
 * |      |  2  |                |
 * |      |  1  |                |
 * |      |  0  | /              |
 * | ~~~~ | ~~~ | ~~~~~~~~~~~~~~ |
 * |  4   |  7  | \              |
 * |      |  6  |                |
 * |      |  5  |                |
 * |      |  4  | Touch Screen Y |
 * |      |  3  | top-to-bottom  |
 * |      |  2  |                |
 * |      |  1  |                |
 * |      |  0  | /              |
 * | ~~~~ | ~~~ | ~~~~~~~~~~~~~~ |
 * |  5   |  7  | \              |
 * |      |  6  |                |
 * |      |  5  |                |
 * |      |  4  | C Stick X      |
 * |      |  3  | left-to-right  |
 * |      |  2  |                |
 * |      |  1  |                |
 * |      |  0  | /              |
 * | ~~~~ | ~~~ | ~~~~~~~~~~~~~~ |
 * |  6   |  7  | \              |
 * |      |  6  |                |
 * |      |  5  |                |
 * |      |  4  | C Stick Y      |
 * |      |  3  | bottom-to-top  |
 * |      |  2  |                |
 * |      |  1  |                |
 * |      |  0  | /              |
 * | ~~~~ | ~~~ | ~~~~~~~~~~~~~~ |
 * |  7   |  7  | \              |
 * |      |  6  |                |
 * |      |  5  |                |
 * |      |  4  | Circle Pad X   |
 * |      |  3  | left-to-right  |
 * |      |  2  |                |
 * |      |  1  |                |
 * |      |  0  | /              |
 * | ~~~~ | ~~~ | ~~~~~~~~~~~~~~ |
 * |  8   |  7  | \              |
 * |      |  6  |                |
 * |      |  5  |                |
 * |      |  4  | Circle Pad Y   |
 * |      |  3  | bottom-to-top  |
 * |      |  2  |                |
 * |      |  1  |                |
 * |      |  0  | /              |
 */
void wanbeiyu_state_deserialize(wanbeiyu_uint8_t const *, wanbeiyu_state_t *);
/* clang-format on */

/**
 * @brief Serializes the current state into a 9-byte output. See also
 * ::wanbeiyu_state_deserialize
 * @param state Pointer to the state structure.
 * @param buffer Pointer to a 9-byte output array.
 */
void wanbeiyu_state_serialize(wanbeiyu_state_t const *, wanbeiyu_uint8_t *);

#ifdef __cplusplus
}
#endif

#endif /* WANBEIYU_STATE_H */