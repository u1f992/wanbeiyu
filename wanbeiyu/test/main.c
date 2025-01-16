#undef __STDC_VERSION__
#include <wanbeiyu.h>

#include <assert.h>
#include <stdio.h>

#define TEST_IDAC_POLARITY_SOURCE WANBEIYU_TRUE
#define TEST_IDAC_POLARITY_SINK WANBEIYU_FALSE

static void test_deserialize(void) {
  wanbeiyu_state_t out;
  wanbeiyu_uint8_t buffer[10];
  buffer[0] = 0xfb;
  buffer[1] = 147 /* 0b10010011 */;
  buffer[2] = 201 /* 0b11001001 */;
  buffer[3] = 209 /* 0b11010__1; */;
  buffer[4] = 0x3f;
  buffer[5] = 239;
  buffer[6] = 0;
  buffer[7] = 1;
  buffer[8] = 2;
  buffer[9] = 3;
  wanbeiyu_deserialize(buffer, sizeof(buffer), &out);
  assert(out.a);
  assert(!out.b);
  assert(!out.select);
  assert(out.start);
  assert(!out.right);
  assert(!out.left);
  assert(out.up);
  assert(out.down);
  assert(out.r);
  assert(out.l);
  assert(!out.x);
  assert(!out.y);
  assert(out.zl);
  assert(!out.zr);
  assert(!out.home);
  assert(out.power);
  assert(out.touch_screen != NULL && out.touch_screen->x == 319 &&
         out.touch_screen->y == 239);
  assert(out.c_stick.x != NULL && *(out.c_stick.x) == 0);
  assert(out.c_stick.y == NULL);
  assert(out.circle_pad.x != NULL && *(out.circle_pad.x) == 2);
  assert(out.circle_pad.y == NULL);
}

static wanbeiyu_bool_t button_switch_state = WANBEIYU_FALSE;
static void button_switch_open(wanbeiyu_spst_switch_t *super) {
  assert(super != NULL);
  (void)super;
  button_switch_state = WANBEIYU_FALSE;
}
static void button_switch_close(wanbeiyu_spst_switch_t *super) {
  assert(super != NULL);
  (void)super;
  button_switch_state = WANBEIYU_TRUE;
}

static void test_button(void) {
  wanbeiyu_spst_switch_t button_switch;
  wanbeiyu_button_t button;

  wanbeiyu_spst_switch_init(&button_switch, button_switch_open,
                            button_switch_close);
  wanbeiyu_button_init(&button, &button_switch);

  wanbeiyu_button_hold(&button);
  assert(button_switch_state);

  wanbeiyu_button_release(&button);
  assert(!button_switch_state);
}

static wanbeiyu_uint16_t touch_screen_horizontal_position = 0;
static void
touch_screen_horizontal_set_wiper_position(wanbeiyu_rdac_320_steps_t *super,
                                           wanbeiyu_uint16_t position) {
  assert(super != NULL);
  assert(position < 320);
  (void)super;
  touch_screen_horizontal_position = position;
}

static wanbeiyu_uint8_t touch_screen_vertical_position = 0;
static void
touch_screen_vertical_set_wiper_position(wanbeiyu_rdac_240_steps_t *super,
                                         wanbeiyu_uint8_t position) {
  assert(super != NULL);
  assert(position < 240);
  (void)super;
  touch_screen_vertical_position = position;
}

static wanbeiyu_bool_t touch_screen_switch_state = WANBEIYU_FALSE;
static void touch_screen_switch_open(wanbeiyu_spst_switch_t *super) {
  assert(super != NULL);
  (void)super;
  touch_screen_switch_state = WANBEIYU_FALSE;
}
static void touch_screen_switch_close(wanbeiyu_spst_switch_t *super) {
  assert(super != NULL);
  (void)super;
  touch_screen_switch_state = WANBEIYU_TRUE;
}

static void test_touch_screen(void) {
  wanbeiyu_touch_screen_state_t state;

  wanbeiyu_rdac_320_steps_t touch_screen_horizontal;
  wanbeiyu_rdac_240_steps_t touch_screen_vertical;
  wanbeiyu_spst_switch_t touch_screen_switch;
  wanbeiyu_touch_screen_t touch_screen;

  wanbeiyu_rdac_320_steps_init(&touch_screen_horizontal,
                               touch_screen_horizontal_set_wiper_position);
  wanbeiyu_rdac_240_steps_init(&touch_screen_vertical,
                               touch_screen_vertical_set_wiper_position);
  wanbeiyu_spst_switch_init(&touch_screen_switch, touch_screen_switch_open,
                            touch_screen_switch_close);
  wanbeiyu_touch_screen_init(&touch_screen, &touch_screen_horizontal,
                             &touch_screen_vertical, &touch_screen_switch);

  wanbeiyu_touch_screen_release(&touch_screen);
  assert(!touch_screen_switch_state);

  state.x = 0;
  state.y = 0;
  wanbeiyu_touch_screen_hold(&touch_screen, &state);
  assert(touch_screen_horizontal_position == 0);
  assert(touch_screen_vertical_position == 0);
  assert(touch_screen_switch_state);

  state.x = 319;
  state.y = 239;
  wanbeiyu_touch_screen_hold(&touch_screen, &state);
  assert(touch_screen_horizontal_position == 319);
  assert(touch_screen_vertical_position == 239);
  assert(touch_screen_switch_state);

  state.x = 320;
  state.y = 240;
  wanbeiyu_touch_screen_hold(&touch_screen, &state);
  assert(touch_screen_horizontal_position == 319);
  assert(touch_screen_vertical_position == 239);
  assert(touch_screen_switch_state);

  wanbeiyu_touch_screen_release(&touch_screen);
  assert(!touch_screen_switch_state);
}

static wanbeiyu_bool_t c_stick_1_polarity = TEST_IDAC_POLARITY_SINK;
static wanbeiyu_uint8_t c_stick_1_value = 0;
static void c_stick_1_source(wanbeiyu_idac_t *super, wanbeiyu_uint8_t value) {
  assert(super != NULL);
  c_stick_1_polarity = TEST_IDAC_POLARITY_SOURCE;
  c_stick_1_value = value;
}
static void c_stick_1_sink(wanbeiyu_idac_t *super, wanbeiyu_uint8_t value) {
  assert(super != NULL);
  c_stick_1_polarity = TEST_IDAC_POLARITY_SINK;
  c_stick_1_value = value;
}

static wanbeiyu_bool_t c_stick_1_switch_state = WANBEIYU_FALSE;
static void c_stick_1_switch_open(wanbeiyu_spst_switch_t *super) {
  assert(super != NULL);
  (void)super;
  c_stick_1_switch_state = WANBEIYU_FALSE;
}
static void c_stick_1_switch_close(wanbeiyu_spst_switch_t *super) {
  assert(super != NULL);
  (void)super;
  c_stick_1_switch_state = WANBEIYU_TRUE;
}

static wanbeiyu_bool_t c_stick_3_polarity = TEST_IDAC_POLARITY_SINK;
static wanbeiyu_uint8_t c_stick_3_value = 0;
static void c_stick_3_source(wanbeiyu_idac_t *super, wanbeiyu_uint8_t value) {
  assert(super != NULL);
  c_stick_3_polarity = TEST_IDAC_POLARITY_SOURCE;
  c_stick_3_value = value;
}
static void c_stick_3_sink(wanbeiyu_idac_t *super, wanbeiyu_uint8_t value) {
  assert(super != NULL);
  c_stick_3_polarity = TEST_IDAC_POLARITY_SINK;
  c_stick_3_value = value;
}

static wanbeiyu_bool_t c_stick_3_switch_state = WANBEIYU_FALSE;
static void c_stick_3_switch_open(wanbeiyu_spst_switch_t *super) {
  assert(super != NULL);
  (void)super;
  c_stick_3_switch_state = WANBEIYU_FALSE;
}
static void c_stick_3_switch_close(wanbeiyu_spst_switch_t *super) {
  assert(super != NULL);
  (void)super;
  c_stick_3_switch_state = WANBEIYU_TRUE;
}

static void test_c_stick(void) {
  wanbeiyu_uint8_t x;
  wanbeiyu_uint8_t y;
  wanbeiyu_c_stick_state_t state;

  wanbeiyu_idac_t c_stick_1;
  wanbeiyu_spst_switch_t c_stick_1_switch;
  wanbeiyu_idac_t c_stick_3;
  wanbeiyu_spst_switch_t c_stick_3_switch;
  wanbeiyu_c_stick_t c_stick;

  wanbeiyu_idac_init(&c_stick_1, c_stick_1_source, c_stick_1_sink);
  wanbeiyu_spst_switch_init(&c_stick_1_switch, c_stick_1_switch_open,
                            c_stick_1_switch_close);
  wanbeiyu_idac_init(&c_stick_3, c_stick_3_source, c_stick_3_sink);
  wanbeiyu_spst_switch_init(&c_stick_3_switch, c_stick_3_switch_open,
                            c_stick_3_switch_close);
  wanbeiyu_c_stick_init(&c_stick, &c_stick_1, &c_stick_1_switch, &c_stick_3,
                        &c_stick_3_switch);

  wanbeiyu_c_stick_release(&c_stick);
  assert(!c_stick_1_switch_state);
  assert(!c_stick_3_switch_state);

  x = 0;
  y = 0;
  state.x = &x;
  state.y = &y;
  wanbeiyu_c_stick_hold(&c_stick, &state);
  assert(!c_stick_1_switch_state);
  assert(c_stick_3_polarity == TEST_IDAC_POLARITY_SINK);
  assert(c_stick_3_value == 255);
  assert(c_stick_3_switch_state);

  x = 0;
  y = 255;
  state.x = &x;
  state.y = &y;
  wanbeiyu_c_stick_hold(&c_stick, &state);
  assert(c_stick_1_polarity == TEST_IDAC_POLARITY_SOURCE);
  assert(c_stick_1_value == 255);
  assert(c_stick_1_switch_state);
  assert(!c_stick_3_switch_state);

  x = 255;
  y = 255;
  state.x = &x;
  state.y = &y;
  wanbeiyu_c_stick_hold(&c_stick, &state);
  assert(!c_stick_1_switch_state);
  assert(c_stick_3_polarity == TEST_IDAC_POLARITY_SOURCE);
  assert(c_stick_3_value == 255);
  assert(c_stick_3_switch_state);

  x = 255;
  y = 0;
  state.x = &x;
  state.y = &y;
  wanbeiyu_c_stick_hold(&c_stick, &state);
  assert(c_stick_1_polarity == TEST_IDAC_POLARITY_SINK);
  assert(c_stick_1_value == 255);
  assert(c_stick_1_switch_state);
  assert(!c_stick_3_switch_state);

  wanbeiyu_c_stick_release(&c_stick);
  assert(!c_stick_1_switch_state);
  assert(!c_stick_3_switch_state);
}

static wanbeiyu_bool_t circle_pad_horizontal_polarity = TEST_IDAC_POLARITY_SINK;
static wanbeiyu_uint8_t circle_pad_horizontal_value = 0;
static void circle_pad_horizontal_source(wanbeiyu_idac_t *super,
                                         wanbeiyu_uint8_t value) {
  assert(super != NULL);
  circle_pad_horizontal_polarity = TEST_IDAC_POLARITY_SOURCE;
  circle_pad_horizontal_value = value;
}
static void circle_pad_horizontal_sink(wanbeiyu_idac_t *super,
                                       wanbeiyu_uint8_t value) {
  assert(super != NULL);
  circle_pad_horizontal_polarity = TEST_IDAC_POLARITY_SINK;
  circle_pad_horizontal_value = value;
}

static wanbeiyu_bool_t circle_pad_horizontal_switch_state = WANBEIYU_FALSE;
static void circle_pad_horizontal_switch_open(wanbeiyu_spst_switch_t *super) {
  assert(super != NULL);
  (void)super;
  circle_pad_horizontal_switch_state = WANBEIYU_FALSE;
}
static void circle_pad_horizontal_switch_close(wanbeiyu_spst_switch_t *super) {
  assert(super != NULL);
  (void)super;
  circle_pad_horizontal_switch_state = WANBEIYU_TRUE;
}

static wanbeiyu_bool_t circle_pad_vertical_polarity = TEST_IDAC_POLARITY_SINK;
static wanbeiyu_uint8_t circle_pad_vertical_value = 0;
static void circle_pad_vertical_source(wanbeiyu_idac_t *super,
                                       wanbeiyu_uint8_t value) {
  assert(super != NULL);
  circle_pad_vertical_polarity = TEST_IDAC_POLARITY_SOURCE;
  circle_pad_vertical_value = value;
}
static void circle_pad_vertical_sink(wanbeiyu_idac_t *super,
                                     wanbeiyu_uint8_t value) {
  assert(super != NULL);
  circle_pad_vertical_polarity = TEST_IDAC_POLARITY_SINK;
  circle_pad_vertical_value = value;
}

static wanbeiyu_bool_t circle_pad_vertical_switch_state = WANBEIYU_FALSE;
static void circle_pad_vertical_switch_open(wanbeiyu_spst_switch_t *super) {
  assert(super != NULL);
  (void)super;
  circle_pad_vertical_switch_state = WANBEIYU_FALSE;
}
static void circle_pad_vertical_switch_close(wanbeiyu_spst_switch_t *super) {
  assert(super != NULL);
  (void)super;
  circle_pad_vertical_switch_state = WANBEIYU_TRUE;
}

static void test_circle_pad(void) {
  wanbeiyu_uint8_t x;
  wanbeiyu_uint8_t y;
  wanbeiyu_circle_pad_state_t state;

  wanbeiyu_idac_t circle_pad_horizontal;
  wanbeiyu_spst_switch_t circle_pad_horizontal_switch;
  wanbeiyu_idac_t circle_pad_vertical;
  wanbeiyu_spst_switch_t circle_pad_vertical_switch;
  wanbeiyu_circle_pad_t circle_pad;

  wanbeiyu_idac_init(&circle_pad_horizontal, circle_pad_horizontal_source,
                     circle_pad_horizontal_sink);
  wanbeiyu_spst_switch_init(&circle_pad_horizontal_switch,
                            circle_pad_horizontal_switch_open,
                            circle_pad_horizontal_switch_close);
  wanbeiyu_idac_init(&circle_pad_vertical, circle_pad_vertical_source,
                     circle_pad_vertical_sink);
  wanbeiyu_spst_switch_init(&circle_pad_vertical_switch,
                            circle_pad_vertical_switch_open,
                            circle_pad_vertical_switch_close);
  wanbeiyu_circle_pad_init(&circle_pad, &circle_pad_horizontal,
                           &circle_pad_horizontal_switch, &circle_pad_vertical,
                           &circle_pad_vertical_switch);

  wanbeiyu_circle_pad_release(&circle_pad);
  assert(!circle_pad_horizontal_switch_state);
  assert(!circle_pad_vertical_switch_state);

  x = 0;
  y = 0;
  state.x = &x;
  state.y = &y;
  wanbeiyu_circle_pad_hold(&circle_pad, &state);
  assert(circle_pad_horizontal_polarity == TEST_IDAC_POLARITY_SOURCE);
  assert(circle_pad_horizontal_value == 255);
  assert(circle_pad_horizontal_switch_state);
  assert(circle_pad_vertical_polarity == TEST_IDAC_POLARITY_SINK);
  assert(circle_pad_vertical_value == 255);
  assert(circle_pad_vertical_switch_state);

  x = 255;
  y = 255;
  state.x = &x;
  state.y = &y;
  wanbeiyu_circle_pad_hold(&circle_pad, &state);
  assert(circle_pad_horizontal_polarity == TEST_IDAC_POLARITY_SINK);
  assert(circle_pad_horizontal_value == 255);
  assert(circle_pad_horizontal_switch_state);
  assert(circle_pad_vertical_polarity == TEST_IDAC_POLARITY_SOURCE);
  assert(circle_pad_vertical_value == 255);
  assert(circle_pad_vertical_switch_state);

  wanbeiyu_circle_pad_release(&circle_pad);
  assert(!circle_pad_horizontal_switch_state);
  assert(!circle_pad_vertical_switch_state);

  x = 128;
  state.x = &x;
  state.y = NULL;
  wanbeiyu_circle_pad_hold(&circle_pad, &state);
  assert(circle_pad_horizontal_polarity == TEST_IDAC_POLARITY_SINK);
  assert(circle_pad_horizontal_value == 0);
  assert(circle_pad_horizontal_switch_state);
  assert(!circle_pad_vertical_switch_state);

  y = 128;
  state.x = NULL;
  state.y = &y;
  wanbeiyu_circle_pad_hold(&circle_pad, &state);
  assert(!circle_pad_horizontal_switch_state);
  assert(circle_pad_vertical_polarity == TEST_IDAC_POLARITY_SOURCE);
  assert(circle_pad_vertical_value == 0);
  assert(circle_pad_vertical_switch_state);

  wanbeiyu_circle_pad_release(&circle_pad);
  assert(!circle_pad_horizontal_switch_state);
  assert(!circle_pad_vertical_switch_state);
}

int main(void) {
  test_deserialize();
  test_button();
  test_touch_screen();
  test_c_stick();
  test_circle_pad();

  (void)wanbeiyu_console_clear;

  return 0;
}