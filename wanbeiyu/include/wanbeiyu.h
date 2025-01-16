#ifndef WANBEIYU_H
#define WANBEIYU_H

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

typedef bool wanbeiyu_bool_t;
#define WANBEIYU_FALSE false
#define WANBEIYU_TRUE true

#define WANBEIYU_UINT8_MAX UINT8_MAX
typedef uint8_t wanbeiyu_uint8_t;

#define WANBEIYU_UINT16_MAX UINT16_MAX
typedef uint16_t wanbeiyu_uint16_t;

#else /* __STDC_VERSION__ < 199901L */

#define WANBEIYU_INLINE

typedef unsigned char wanbeiyu_bool_t;
#define WANBEIYU_FALSE 0
#define WANBEIYU_TRUE 1

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

/**
 * Interface for a digital potentiometer with 320 steps.
 * position=0, W=B; position=319, W=A.
 *
 *   | A
 *  .-.
 *  | |<-- W
 *  '-'
 *   | B
 */
typedef struct wanbeiyu_rdac_320_steps_t {
  void (*set_wiper_position)(struct wanbeiyu_rdac_320_steps_t *,
                             wanbeiyu_uint16_t);
} wanbeiyu_rdac_320_steps_t;

static WANBEIYU_INLINE void wanbeiyu_rdac_320_steps_init(
    wanbeiyu_rdac_320_steps_t *self,
    void (*set_wiper_position)(wanbeiyu_rdac_320_steps_t *,
                               wanbeiyu_uint16_t)) {
  assert(self != NULL);
  assert(set_wiper_position != NULL);

  self->set_wiper_position = set_wiper_position;
}

static WANBEIYU_INLINE void
wanbeiyu_rdac_320_steps_set_wiper_position(wanbeiyu_rdac_320_steps_t *self,
                                           wanbeiyu_uint16_t position) {
  assert(self != NULL);
  assert(position < 320);

  self->set_wiper_position(self, position);
}

/**
 * Interface for a digital potentiometer with 240 steps.
 * position=0, W=B; position=239, W=A.
 *
 *   | A
 *  .-.
 *  | |<-- W
 *  '-'
 *   | B
 */
typedef struct wanbeiyu_rdac_240_steps_t {
  void (*set_wiper_position)(struct wanbeiyu_rdac_240_steps_t *,
                             wanbeiyu_uint8_t);
} wanbeiyu_rdac_240_steps_t;

static WANBEIYU_INLINE void wanbeiyu_rdac_240_steps_init(
    wanbeiyu_rdac_240_steps_t *self,
    void (*set_wiper_position)(wanbeiyu_rdac_240_steps_t *, wanbeiyu_uint8_t)) {
  assert(self != NULL);
  assert(set_wiper_position != NULL);

  self->set_wiper_position = set_wiper_position;
}

static WANBEIYU_INLINE void
wanbeiyu_rdac_240_steps_set_wiper_position(wanbeiyu_rdac_240_steps_t *self,
                                           wanbeiyu_uint8_t position) {
  assert(self != NULL);
  assert(position < 240);

  self->set_wiper_position(self, position);
}

/**
 * Interface for a SPST analog switch.
 *
 *   |
 *   o |
 *     |--
 *   o |
 *   |
 */
typedef struct wanbeiyu_spst_switch_t {
  void (*open)(struct wanbeiyu_spst_switch_t *);
  void (*close)(struct wanbeiyu_spst_switch_t *);
} wanbeiyu_spst_switch_t;

static WANBEIYU_INLINE void
wanbeiyu_spst_switch_init(wanbeiyu_spst_switch_t *self,
                          void (*open)(struct wanbeiyu_spst_switch_t *),
                          void (*close)(struct wanbeiyu_spst_switch_t *)) {
  assert(self != NULL);
  assert(open != NULL);
  assert(close != NULL);

  self->open = open;
  self->close = close;
}

static WANBEIYU_INLINE void
wanbeiyu_spst_switch_open(wanbeiyu_spst_switch_t *self) {
  assert(self != NULL);

  self->open(self);
}

static WANBEIYU_INLINE void
wanbeiyu_spst_switch_close(wanbeiyu_spst_switch_t *self) {
  assert(self != NULL);

  self->close(self);
}

/**
 * Interface for a current source-sink D/A converter.
 */
typedef struct wanbeiyu_idac_t {
  void (*source)(struct wanbeiyu_idac_t *, wanbeiyu_uint8_t);
  void (*sink)(struct wanbeiyu_idac_t *, wanbeiyu_uint8_t);
} wanbeiyu_idac_t;

static WANBEIYU_INLINE void
wanbeiyu_idac_init(wanbeiyu_idac_t *self,
                   void (*source)(struct wanbeiyu_idac_t *, wanbeiyu_uint8_t),
                   void (*sink)(struct wanbeiyu_idac_t *, wanbeiyu_uint8_t)) {
  assert(self != NULL);
  assert(source != NULL);
  assert(sink != NULL);

  self->source = source;
  self->sink = sink;
}

static WANBEIYU_INLINE void wanbeiyu_idac_source(wanbeiyu_idac_t *self,
                                                 wanbeiyu_uint8_t value) {
  assert(self != NULL);

  self->source(self, value);
}

static WANBEIYU_INLINE void wanbeiyu_idac_sink(wanbeiyu_idac_t *self,
                                               wanbeiyu_uint8_t value) {
  assert(self != NULL);

  self->sink(self, value);
}

typedef struct wanbeiyu_touch_screen_state_t {
  wanbeiyu_uint16_t x;
  wanbeiyu_uint8_t y;
} wanbeiyu_touch_screen_state_t;

typedef struct wanbeiyu_c_stick_state_t {
  wanbeiyu_uint8_t *x;
  wanbeiyu_uint8_t *y;
} wanbeiyu_c_stick_state_t;

typedef wanbeiyu_c_stick_state_t wanbeiyu_circle_pad_state_t;

typedef struct wanbeiyu_state_t {
  wanbeiyu_bool_t power;
  wanbeiyu_bool_t home;
  wanbeiyu_bool_t zr;
  wanbeiyu_bool_t zl;
  wanbeiyu_bool_t y;
  wanbeiyu_bool_t x;
  wanbeiyu_bool_t l;
  wanbeiyu_bool_t r;

  wanbeiyu_bool_t down;
  wanbeiyu_bool_t up;
  wanbeiyu_bool_t left;
  wanbeiyu_bool_t right;
  wanbeiyu_bool_t start;
  wanbeiyu_bool_t select;
  wanbeiyu_bool_t b;
  wanbeiyu_bool_t a;

  wanbeiyu_touch_screen_state_t *touch_screen;
  wanbeiyu_c_stick_state_t c_stick;
  wanbeiyu_circle_pad_state_t circle_pad;
  wanbeiyu_bool_t reserved_0;
  wanbeiyu_bool_t reserved_1;

  wanbeiyu_touch_screen_state_t touch_screen_state;
  struct {
    wanbeiyu_uint8_t x;
    wanbeiyu_uint8_t y;
  } c_stick_state;
  struct {
    wanbeiyu_uint8_t x;
    wanbeiyu_uint8_t y;
  } circle_pad_state;
} wanbeiyu_state_t;

/* clang-format off */
/**
 * This order is derived from devkitPro, and originally comes from the
 * representation in memory on the actual console.
 *
 * According to devkitPro and Citra, the console internally uses a range of -156
 * to 156 for the C Stick and -154 to 154 for the Circle Pad. The up-right
 * direction is considered positive, with the center at (0,0). These values
 * apply to the uncalibrated case; the actual range may vary depending on
 * calibration.
 *
 * - https://github.com/devkitPro/libctru/blob/1bafb08f347226fba439d14c7bb1f44e85d70978/libctru/include/3ds/services/hid.h#L10-L41
 * - http://3dbrew.org/wiki/HID_Shared_Memory
 *
 * | Byte | Bit | Description    |
 * | ---- | --- | -------------- |
 * |  0   |  7  | 1  \           |
 * |      |  6  | 1   \          |
 * |      |  5  | 1              |
 * |      |  4  | 1     0xfb     |
 * |      |  3  | 1              |
 * |      |  2  | 0    /         |
 * |      |  1  | 1   /          |
 * |      |  0  | 1  /           |
 * | ~~~~ | ~~~ | ~~~~~~~~~~~~~~ |
 * |  1   |  7  | Power          | 0=release, 1=hold
 * |      |  6  | Home           |
 * |      |  5  | ZR             |
 * |      |  4  | ZL             |
 * |      |  3  | Y              |
 * |      |  2  | X              |
 * |      |  1  | L              |
 * |      |  0  | R              |
 * | ~~~~ | ~~~ | ~~~~~~~~~~~~~~ |
 * |  2   |  7  | Down           |
 * |      |  6  | Up             |
 * |      |  5  | Left           |
 * |      |  4  | Right          |
 * |      |  3  | Start          |
 * |      |  2  | Select         |
 * |      |  1  | B              |
 * |      |  0  | A              |
 * | ~~~~ | ~~~ | ~~~~~~~~~~~~~~ |
 * |  3   |  7  | Touch Screen   |
 * |      |  6  | C Stick X      |
 * |      |  5  | C Stick Y      |
 * |      |  4  | Circle Pad X   |
 * |      |  3  | Circle Pad Y   |
 * |      |  2  | (Reserved)     |
 * |      |  1  | (Reserved)     |
 * |      |  0  | \              |
 * | ~~~~ | ~~~ | ~\~~~~~~~~~~~~ |
 * |  4   |  7  |                |
 * |      |  6  | Touch Screen X |
 * |      |  5  |                |
 * |      |  4  | left-to-right, |
 * |      |  3  | clamped to 319 |
 * |      |  2  |                |
 * |      |  1  |  /             |
 * |      |  0  | /              |
 * | ~~~~ | ~~~ | ~~~~~~~~~~~~~~ |
 * |  5   |  7  | \              |
 * |      |  6  |                |
 * |      |  5  | Touch Screen Y |
 * |      |  4  |                |
 * |      |  3  | top-to-bottom, |
 * |      |  2  | clamped to 239 |
 * |      |  1  |                |
 * |      |  0  | /              |
 * | ~~~~ | ~~~ | ~~~~~~~~~~~~~~ |
 * |  6   |  7  | \              |
 * |      |  6  |                |
 * |      |  5  | C Stick X      |
 * |      |  4  |                |
 * |      |  3  | left-to-right  |
 * |      |  2  |                |
 * |      |  1  |  /             |
 * |      |  0  | /              |
 * | ~~~~ | ~~~ | ~~~~~~~~~~~~~~ |
 * |  7   |  7  | \              |
 * |      |  6  |                |
 * |      |  5  | C Stick Y      |
 * |      |  4  |                |
 * |      |  3  | bottom-to-top  |
 * |      |  2  |                |
 * |      |  1  |  /             |
 * |      |  0  | /              |
 * | ~~~~ | ~~~ | ~~~~~~~~~~~~~~ |
 * |  8   |  7  | \              |
 * |      |  6  |                |
 * |      |  5  | Circle Pad X   |
 * |      |  4  |                |
 * |      |  3  | left-to-right  |
 * |      |  2  |                |
 * |      |  1  |  /             |
 * |      |  0  | /              |
 * | ~~~~ | ~~~ | ~~~~~~~~~~~~~~ |
 * |  9   |  7  | \              |
 * |      |  6  |                |
 * |      |  5  | Circle Pad Y   |
 * |      |  4  |                |
 * |      |  3  | bottom-to-top  |
 * |      |  2  |                |
 * |      |  1  |  /             |
 * |      |  0  | /              |
 */
static WANBEIYU_INLINE void wanbeiyu_deserialize(const wanbeiyu_uint8_t *buffer,
                                                 size_t length, wanbeiyu_state_t *state) {
  /* clang-format on */
  assert(buffer != NULL);
  assert(length == 10);
  assert(buffer[0] == 0xfb);
  assert(state != NULL);
  (void)length;

  state->power = (buffer[1] >> 7) & 1;
  state->home = (buffer[1] >> 6) & 1;
  state->zr = (buffer[1] >> 5) & 1;
  state->zl = (buffer[1] >> 4) & 1;
  state->y = (buffer[1] >> 3) & 1;
  state->x = (buffer[1] >> 2) & 1;
  state->l = (buffer[1] >> 1) & 1;
  state->r = buffer[1] & 1;

  state->down = (buffer[2] >> 7) & 1;
  state->up = (buffer[2] >> 6) & 1;
  state->left = (buffer[2] >> 5) & 1;
  state->right = (buffer[2] >> 4) & 1;
  state->start = (buffer[2] >> 3) & 1;
  state->select = (buffer[2] >> 2) & 1;
  state->b = (buffer[2] >> 1) & 1;
  state->a = buffer[2] & 1;

  state->touch_screen =
      (buffer[3] >> 7) & 1 ? &(state->touch_screen_state) : NULL;
  state->c_stick.x = (buffer[3] >> 6) & 1 ? &(state->c_stick_state.x) : NULL;
  state->c_stick.y = (buffer[3] >> 5) & 1 ? &(state->c_stick_state.y) : NULL;
  state->circle_pad.x =
      (buffer[3] >> 4) & 1 ? &(state->circle_pad_state.x) : NULL;
  state->circle_pad.y =
      (buffer[3] >> 3) & 1 ? &(state->circle_pad_state.y) : NULL;
  state->reserved_0 = (buffer[3] >> 2) & 1;
  state->reserved_1 = (buffer[3] >> 1) & 1;

  state->touch_screen_state.x = ((buffer[3] & 1) << 8) | buffer[4];
  state->touch_screen_state.y = buffer[5];

  state->c_stick_state.x = buffer[6];
  state->c_stick_state.y = buffer[7];

  state->circle_pad_state.x = buffer[8];
  state->circle_pad_state.y = buffer[9];
}

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
typedef struct wanbeiyu_button_t {
  wanbeiyu_spst_switch_t *switch_;
} wanbeiyu_button_t;

static WANBEIYU_INLINE void
wanbeiyu_button_init(wanbeiyu_button_t *self, wanbeiyu_spst_switch_t *switch_) {
  assert(self != NULL);
  assert(switch_ != NULL);

  self->switch_ = switch_;
}

static WANBEIYU_INLINE void wanbeiyu_button_hold(wanbeiyu_button_t *self) {
  assert(self != NULL);

  wanbeiyu_spst_switch_close(self->switch_);
}

static WANBEIYU_INLINE void wanbeiyu_button_release(wanbeiyu_button_t *self) {
  assert(self != NULL);

  wanbeiyu_spst_switch_open(self->switch_);
}

/**
 *   | Y_{B}
 *  .-.     _|_
 *  | |<----o o-.
 *  '-'         |
 *   | Y_{A}    |
 *             _v_
 *        ----|___|----
 *      X_{B}       X_{A}
 *
 * 1: Y_{A}; 2: X_{B}; 3: Y_{B}; 4: X_{A}
 * (Pin numbers of Molex 5014610491)
 */
typedef struct wanbeiyu_touch_screen_t {
  wanbeiyu_rdac_320_steps_t *horizontal;
  wanbeiyu_rdac_240_steps_t *vertical;
  wanbeiyu_spst_switch_t *switch_;
} wanbeiyu_touch_screen_t;

static WANBEIYU_INLINE void wanbeiyu_touch_screen_init(
    wanbeiyu_touch_screen_t *self, wanbeiyu_rdac_320_steps_t *horizontal,
    wanbeiyu_rdac_240_steps_t *vertical, wanbeiyu_spst_switch_t *switch_) {
  assert(self != NULL);
  assert(horizontal != NULL);
  assert(vertical != NULL);
  assert(switch_ != NULL);

  self->horizontal = horizontal;
  self->vertical = vertical;
  self->switch_ = switch_;
}

static WANBEIYU_INLINE void
wanbeiyu_touch_screen_release(wanbeiyu_touch_screen_t *self) {
  assert(self != NULL);

  wanbeiyu_spst_switch_open(self->switch_);
}

static WANBEIYU_INLINE void
wanbeiyu_touch_screen_hold(wanbeiyu_touch_screen_t *self,
                           const wanbeiyu_touch_screen_state_t *state) {
  assert(self != NULL);

  if (state != NULL) {
    wanbeiyu_rdac_320_steps_set_wiper_position(self->horizontal,
                                               state->x < 320 ? state->x : 319);
    wanbeiyu_rdac_240_steps_set_wiper_position(self->vertical,
                                               state->y < 240 ? state->y : 239);
    wanbeiyu_spst_switch_close(self->switch_);
  } else {
    wanbeiyu_touch_screen_release(self);
  }
}

/**
 *   1+         3+
 *     \_     _/
 *       \_ _/
 *        _X_
 *      _/   \_
 *     /       \
 *   3-         1-
 * +: source, -: sink
 *
 * (Pin numbers of Hirose FH33-4S-1SH(10))
 */
typedef struct wanbeiyu_c_stick_t {
  wanbeiyu_idac_t *axis_1;
  wanbeiyu_spst_switch_t *axis_1_switch;
  wanbeiyu_idac_t *axis_3;
  wanbeiyu_spst_switch_t *axis_3_switch;
} wanbeiyu_c_stick_t;

static WANBEIYU_INLINE void
wanbeiyu_c_stick_init(wanbeiyu_c_stick_t *self, wanbeiyu_idac_t *axis_1,
                      wanbeiyu_spst_switch_t *axis_1_switch,
                      wanbeiyu_idac_t *axis_3,
                      wanbeiyu_spst_switch_t *axis_3_switch) {
  assert(self != NULL);
  assert(axis_1 != NULL);
  assert(axis_1_switch != NULL);
  assert(axis_3 != NULL);
  assert(axis_3_switch != NULL);

  self->axis_1 = axis_1;
  self->axis_1_switch = axis_1_switch;
  self->axis_3 = axis_3;
  self->axis_3_switch = axis_3_switch;
}

static WANBEIYU_INLINE int wanbeiyu_internal_abs(int value) {
  assert(INT_MIN + 1 <= value);

  return value > 0 ? value : -value;
}

static WANBEIYU_INLINE void
wanbeiyu_c_stick_hold(wanbeiyu_c_stick_t *self,
                      const wanbeiyu_c_stick_state_t *state) {
  /*
   * d1 = signed_distance_to(y=x) / DISTANCE_MAX * UINT8_MAX
   * d3 = signed_distance_to(y=-x+255) / DISTANCE_MAX * UINT8_MAX
   *
   * signed_distance_to(y=ax+b) (-a*x+y-b)/sqrt(a^2+1)
   * positive=above, negative=below
   * While a=1,-1 thus sqrt(a^2+1) is always sqrt(2).
   *
   * DISTANCE_MAX=UINT8_MAX/2*sqrt(2)
   *
   * ((-a*x+y-b)/sqrt(2)) / (UINT8_MAX/2*sqrt(2)) * UINT8_MAX
   * = -a*x+y-b
   */
  assert(self != NULL);

  if (state != NULL) {
    wanbeiyu_uint8_t x = state->x != NULL ? *(state->x) : 0x80;
    wanbeiyu_uint8_t y = state->y != NULL ? *(state->y) : 0x80;
    int d1 = -x + y;
    int d3 = x + y - 255;
    assert(-255 <= d1 && d1 <= 255);
    assert(-255 <= d3 && d3 <= 255);

    (d1 > 0 ? wanbeiyu_idac_source : wanbeiyu_idac_sink)(
        self->axis_1, (wanbeiyu_uint8_t)wanbeiyu_internal_abs(d1));
    (d1 == 0 && x == y ? wanbeiyu_spst_switch_open
                       : wanbeiyu_spst_switch_close)(self->axis_1_switch);

    (d3 > 0 ? wanbeiyu_idac_source : wanbeiyu_idac_sink)(
        self->axis_3, (wanbeiyu_uint8_t)wanbeiyu_internal_abs(d3));
    (d3 == 0 && 255 - x == y ? wanbeiyu_spst_switch_open
                             : wanbeiyu_spst_switch_close)(self->axis_3_switch);
  } else {
    wanbeiyu_spst_switch_open(self->axis_1_switch);
    wanbeiyu_spst_switch_open(self->axis_3_switch);
  }
}

static WANBEIYU_INLINE void wanbeiyu_c_stick_release(wanbeiyu_c_stick_t *self) {
  assert(self != NULL);

  wanbeiyu_c_stick_hold(self, NULL);
}

/**
 *   ^ 1v8
 *   |
 *   o-------------o
 *   |             |
 *   |            .-.
 *   |            | |<-- Y
 *   |            '-'
 *   |     ___     |
 *   o----|___|----o
 *          ^      |
 *          |      v GND
 *          X
 *
 *           4+
 *           |
 *           |
 *  2+ ------+------ 2-
 *           |
 *           |
 *           4-
 * +: source, -: sink
 *
 * 1: GND; 2: X; 3: 1v8; 4: Y
 * (Pin numbers of Molex 5014610491)
 */
typedef struct wanbeiyu_circle_pad_t {
  wanbeiyu_idac_t *horizontal;
  wanbeiyu_spst_switch_t *horizontal_switch;
  wanbeiyu_idac_t *vertical;
  wanbeiyu_spst_switch_t *vertical_switch;
} wanbeiyu_circle_pad_t;

static WANBEIYU_INLINE void wanbeiyu_circle_pad_init(
    wanbeiyu_circle_pad_t *self, wanbeiyu_idac_t *horizontal,
    wanbeiyu_spst_switch_t *horizontal_switch, wanbeiyu_idac_t *vertical,
    wanbeiyu_spst_switch_t *vertical_switch) {
  assert(self != NULL);
  assert(horizontal != NULL);
  assert(horizontal_switch != NULL);
  assert(vertical != NULL);
  assert(vertical_switch != NULL);

  self->horizontal = horizontal;
  self->horizontal_switch = horizontal_switch;
  self->vertical = vertical;
  self->vertical_switch = vertical_switch;
}

static WANBEIYU_INLINE wanbeiyu_uint8_t
wanbeiyu_internal_map_127_to_255(wanbeiyu_uint8_t value) {
  assert(value <= 127);

  return (value * 255) / 127;
}

static WANBEIYU_INLINE void
wanbeiyu_circle_pad_hold(wanbeiyu_circle_pad_t *self,
                         const wanbeiyu_circle_pad_state_t *state) {
  assert(self != NULL);

  if (state != NULL) {
    if (state->x != NULL) {
      if (*(state->x) < 128) {
        wanbeiyu_idac_source(self->horizontal, wanbeiyu_internal_map_127_to_255(
                                                   127 - *(state->x)));
      } else {
        wanbeiyu_idac_sink(self->horizontal,
                           wanbeiyu_internal_map_127_to_255(*(state->x) - 128));
      }
      wanbeiyu_spst_switch_close(self->horizontal_switch);
    } else {
      wanbeiyu_spst_switch_open(self->horizontal_switch);
    }
    if (state->y != NULL) {
      if (*(state->y) < 128) {
        wanbeiyu_idac_sink(self->vertical,
                           wanbeiyu_internal_map_127_to_255(127 - *(state->y)));
      } else {
        wanbeiyu_idac_source(self->vertical, wanbeiyu_internal_map_127_to_255(
                                                 *(state->y) - 128));
      }
      wanbeiyu_spst_switch_close(self->vertical_switch);
    } else {
      wanbeiyu_spst_switch_open(self->vertical_switch);
    }
  } else {
    wanbeiyu_spst_switch_open(self->horizontal_switch);
    wanbeiyu_spst_switch_open(self->vertical_switch);
  }
}

static WANBEIYU_INLINE void
wanbeiyu_circle_pad_release(wanbeiyu_circle_pad_t *self) {
  assert(self != NULL);

  wanbeiyu_circle_pad_hold(self, NULL);
}

typedef struct wanbeiyu_console_t {
  wanbeiyu_button_t a;
  wanbeiyu_button_t b;
  wanbeiyu_button_t select;
  wanbeiyu_button_t start;
  wanbeiyu_button_t right;
  wanbeiyu_button_t left;
  wanbeiyu_button_t up;
  wanbeiyu_button_t down;
  wanbeiyu_button_t r;
  wanbeiyu_button_t l;
  wanbeiyu_button_t x;
  wanbeiyu_button_t y;
  wanbeiyu_button_t zl;
  wanbeiyu_button_t zr;
  wanbeiyu_button_t home;
  wanbeiyu_button_t power;
  wanbeiyu_touch_screen_t touch_screen;
  wanbeiyu_c_stick_t c_stick;
  wanbeiyu_circle_pad_t circle_pad;
} wanbeiyu_console_t;

static WANBEIYU_INLINE void
wanbeiyu_console_set(wanbeiyu_console_t *console,
                     const wanbeiyu_state_t *state) {
  assert(console != NULL);

  if (state != NULL) {
    (state->a ? wanbeiyu_button_hold : wanbeiyu_button_release)(&(console->a));
    (state->b ? wanbeiyu_button_hold : wanbeiyu_button_release)(&(console->b));
    (state->select ? wanbeiyu_button_hold
                   : wanbeiyu_button_release)(&(console->select));
    (state->start ? wanbeiyu_button_hold
                  : wanbeiyu_button_release)(&(console->start));
    (state->right ? wanbeiyu_button_hold
                  : wanbeiyu_button_release)(&(console->right));
    (state->left ? wanbeiyu_button_hold
                 : wanbeiyu_button_release)(&(console->left));
    (state->up ? wanbeiyu_button_hold
               : wanbeiyu_button_release)(&(console->up));
    (state->down ? wanbeiyu_button_hold
                 : wanbeiyu_button_release)(&(console->down));
    (state->r ? wanbeiyu_button_hold : wanbeiyu_button_release)(&(console->r));
    (state->l ? wanbeiyu_button_hold : wanbeiyu_button_release)(&(console->l));
    (state->x ? wanbeiyu_button_hold : wanbeiyu_button_release)(&(console->x));
    (state->y ? wanbeiyu_button_hold : wanbeiyu_button_release)(&(console->y));
    (state->zl ? wanbeiyu_button_hold
               : wanbeiyu_button_release)(&(console->zl));
    (state->zr ? wanbeiyu_button_hold
               : wanbeiyu_button_release)(&(console->zr));
    (state->home ? wanbeiyu_button_hold
                 : wanbeiyu_button_release)(&(console->home));
    (state->power ? wanbeiyu_button_hold
                  : wanbeiyu_button_release)(&(console->power));
    wanbeiyu_touch_screen_hold(&(console->touch_screen), state->touch_screen);
    wanbeiyu_c_stick_hold(&(console->c_stick), &(state->c_stick));
    wanbeiyu_circle_pad_hold(&(console->circle_pad), &(state->circle_pad));
  } else {
    wanbeiyu_button_release(&(console->a));
    wanbeiyu_button_release(&(console->b));
    wanbeiyu_button_release(&(console->select));
    wanbeiyu_button_release(&(console->start));
    wanbeiyu_button_release(&(console->right));
    wanbeiyu_button_release(&(console->left));
    wanbeiyu_button_release(&(console->up));
    wanbeiyu_button_release(&(console->down));
    wanbeiyu_button_release(&(console->r));
    wanbeiyu_button_release(&(console->l));
    wanbeiyu_button_release(&(console->x));
    wanbeiyu_button_release(&(console->y));
    wanbeiyu_button_release(&(console->zl));
    wanbeiyu_button_release(&(console->zr));
    wanbeiyu_button_release(&(console->home));
    wanbeiyu_button_release(&(console->power));
    wanbeiyu_touch_screen_release(&(console->touch_screen));
    wanbeiyu_c_stick_release(&(console->c_stick));
    wanbeiyu_circle_pad_release(&(console->circle_pad));
  }
}

static WANBEIYU_INLINE void
wanbeiyu_console_clear(wanbeiyu_console_t *console) {
  assert(console != NULL);

  wanbeiyu_console_set(console, NULL);
}

#ifdef __cplusplus
}
#endif

#endif /* WANBEIYU_H */