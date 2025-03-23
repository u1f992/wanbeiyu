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
#include <wanbeiyu.h>

#include <stdio.h>

typedef enum test_spst_switch_state_t {
  TEST_SPST_SWITCH_OPEN,
  TEST_SPST_SWITCH_CLOSE
} test_spst_switch_state_t;

typedef struct test_spst_switch_t {
  wanbeiyu_hal_spst_switch_t base;
  test_spst_switch_state_t state;
} test_spst_switch_t;

static void power_sw_open(wanbeiyu_hal_spst_switch_t *switch_) {
  assert(switch_ != NULL);

  ((test_spst_switch_t *)switch_)->state = TEST_SPST_SWITCH_OPEN;
}
static void power_sw_close(wanbeiyu_hal_spst_switch_t *switch_) {
  assert(switch_ != NULL);

  ((test_spst_switch_t *)switch_)->state = TEST_SPST_SWITCH_CLOSE;
}

static void home_sw_open(wanbeiyu_hal_spst_switch_t *switch_) {
  assert(switch_ != NULL);

  ((test_spst_switch_t *)switch_)->state = TEST_SPST_SWITCH_OPEN;
}
static void home_sw_close(wanbeiyu_hal_spst_switch_t *switch_) {
  assert(switch_ != NULL);

  ((test_spst_switch_t *)switch_)->state = TEST_SPST_SWITCH_CLOSE;
}

static void zr_sw_open(wanbeiyu_hal_spst_switch_t *switch_) {
  assert(switch_ != NULL);

  ((test_spst_switch_t *)switch_)->state = TEST_SPST_SWITCH_OPEN;
}
static void zr_sw_close(wanbeiyu_hal_spst_switch_t *switch_) {
  assert(switch_ != NULL);

  ((test_spst_switch_t *)switch_)->state = TEST_SPST_SWITCH_CLOSE;
}

static void zl_sw_open(wanbeiyu_hal_spst_switch_t *switch_) {
  assert(switch_ != NULL);

  ((test_spst_switch_t *)switch_)->state = TEST_SPST_SWITCH_OPEN;
}
static void zl_sw_close(wanbeiyu_hal_spst_switch_t *switch_) {
  assert(switch_ != NULL);

  ((test_spst_switch_t *)switch_)->state = TEST_SPST_SWITCH_CLOSE;
}

static void y_sw_open(wanbeiyu_hal_spst_switch_t *switch_) {
  assert(switch_ != NULL);

  ((test_spst_switch_t *)switch_)->state = TEST_SPST_SWITCH_OPEN;
}
static void y_sw_close(wanbeiyu_hal_spst_switch_t *switch_) {
  assert(switch_ != NULL);

  ((test_spst_switch_t *)switch_)->state = TEST_SPST_SWITCH_CLOSE;
}

static void x_sw_open(wanbeiyu_hal_spst_switch_t *switch_) {
  assert(switch_ != NULL);

  ((test_spst_switch_t *)switch_)->state = TEST_SPST_SWITCH_OPEN;
}
static void x_sw_close(wanbeiyu_hal_spst_switch_t *switch_) {
  assert(switch_ != NULL);

  ((test_spst_switch_t *)switch_)->state = TEST_SPST_SWITCH_CLOSE;
}

static void l_sw_open(wanbeiyu_hal_spst_switch_t *switch_) {
  assert(switch_ != NULL);

  ((test_spst_switch_t *)switch_)->state = TEST_SPST_SWITCH_OPEN;
}
static void l_sw_close(wanbeiyu_hal_spst_switch_t *switch_) {
  assert(switch_ != NULL);

  ((test_spst_switch_t *)switch_)->state = TEST_SPST_SWITCH_CLOSE;
}

static void r_sw_open(wanbeiyu_hal_spst_switch_t *switch_) {
  assert(switch_ != NULL);

  ((test_spst_switch_t *)switch_)->state = TEST_SPST_SWITCH_OPEN;
}
static void r_sw_close(wanbeiyu_hal_spst_switch_t *switch_) {
  assert(switch_ != NULL);

  ((test_spst_switch_t *)switch_)->state = TEST_SPST_SWITCH_CLOSE;
}

static void down_sw_open(wanbeiyu_hal_spst_switch_t *switch_) {
  assert(switch_ != NULL);

  ((test_spst_switch_t *)switch_)->state = TEST_SPST_SWITCH_OPEN;
}
static void down_sw_close(wanbeiyu_hal_spst_switch_t *switch_) {
  assert(switch_ != NULL);

  ((test_spst_switch_t *)switch_)->state = TEST_SPST_SWITCH_CLOSE;
}

static void up_sw_open(wanbeiyu_hal_spst_switch_t *switch_) {
  assert(switch_ != NULL);

  ((test_spst_switch_t *)switch_)->state = TEST_SPST_SWITCH_OPEN;
}
static void up_sw_close(wanbeiyu_hal_spst_switch_t *switch_) {
  assert(switch_ != NULL);

  ((test_spst_switch_t *)switch_)->state = TEST_SPST_SWITCH_CLOSE;
}

static void left_sw_open(wanbeiyu_hal_spst_switch_t *switch_) {
  assert(switch_ != NULL);

  ((test_spst_switch_t *)switch_)->state = TEST_SPST_SWITCH_OPEN;
}
static void left_sw_close(wanbeiyu_hal_spst_switch_t *switch_) {
  assert(switch_ != NULL);

  ((test_spst_switch_t *)switch_)->state = TEST_SPST_SWITCH_CLOSE;
}

static void right_sw_open(wanbeiyu_hal_spst_switch_t *switch_) {
  assert(switch_ != NULL);

  ((test_spst_switch_t *)switch_)->state = TEST_SPST_SWITCH_OPEN;
}
static void right_sw_close(wanbeiyu_hal_spst_switch_t *switch_) {
  assert(switch_ != NULL);

  ((test_spst_switch_t *)switch_)->state = TEST_SPST_SWITCH_CLOSE;
}

static void start_sw_open(wanbeiyu_hal_spst_switch_t *switch_) {
  assert(switch_ != NULL);

  ((test_spst_switch_t *)switch_)->state = TEST_SPST_SWITCH_OPEN;
}
static void start_sw_close(wanbeiyu_hal_spst_switch_t *switch_) {
  assert(switch_ != NULL);

  ((test_spst_switch_t *)switch_)->state = TEST_SPST_SWITCH_CLOSE;
}

static void select_sw_open(wanbeiyu_hal_spst_switch_t *switch_) {
  assert(switch_ != NULL);

  ((test_spst_switch_t *)switch_)->state = TEST_SPST_SWITCH_OPEN;
}
static void select_sw_close(wanbeiyu_hal_spst_switch_t *switch_) {
  assert(switch_ != NULL);

  ((test_spst_switch_t *)switch_)->state = TEST_SPST_SWITCH_CLOSE;
}

static void b_sw_open(wanbeiyu_hal_spst_switch_t *switch_) {
  assert(switch_ != NULL);

  ((test_spst_switch_t *)switch_)->state = TEST_SPST_SWITCH_OPEN;
}
static void b_sw_close(wanbeiyu_hal_spst_switch_t *switch_) {
  assert(switch_ != NULL);

  ((test_spst_switch_t *)switch_)->state = TEST_SPST_SWITCH_CLOSE;
}

static void a_sw_open(wanbeiyu_hal_spst_switch_t *switch_) {
  assert(switch_ != NULL);

  ((test_spst_switch_t *)switch_)->state = TEST_SPST_SWITCH_OPEN;
}
static void a_sw_close(wanbeiyu_hal_spst_switch_t *switch_) {
  assert(switch_ != NULL);

  ((test_spst_switch_t *)switch_)->state = TEST_SPST_SWITCH_CLOSE;
}

static void ts_sw_open(wanbeiyu_hal_spst_switch_t *switch_) {
  assert(switch_ != NULL);

  ((test_spst_switch_t *)switch_)->state = TEST_SPST_SWITCH_OPEN;
}
static void ts_sw_close(wanbeiyu_hal_spst_switch_t *switch_) {
  assert(switch_ != NULL);

  ((test_spst_switch_t *)switch_)->state = TEST_SPST_SWITCH_CLOSE;
}

static void csa1_sw_open(wanbeiyu_hal_spst_switch_t *switch_) {
  assert(switch_ != NULL);

  ((test_spst_switch_t *)switch_)->state = TEST_SPST_SWITCH_OPEN;
}
static void csa1_sw_close(wanbeiyu_hal_spst_switch_t *switch_) {
  assert(switch_ != NULL);

  ((test_spst_switch_t *)switch_)->state = TEST_SPST_SWITCH_CLOSE;
}

static void csa3_sw_open(wanbeiyu_hal_spst_switch_t *switch_) {
  assert(switch_ != NULL);

  ((test_spst_switch_t *)switch_)->state = TEST_SPST_SWITCH_OPEN;
}
static void csa3_sw_close(wanbeiyu_hal_spst_switch_t *switch_) {
  assert(switch_ != NULL);

  ((test_spst_switch_t *)switch_)->state = TEST_SPST_SWITCH_CLOSE;
}

static void cpx_sw_open(wanbeiyu_hal_spst_switch_t *switch_) {
  assert(switch_ != NULL);

  ((test_spst_switch_t *)switch_)->state = TEST_SPST_SWITCH_OPEN;
}
static void cpx_sw_close(wanbeiyu_hal_spst_switch_t *switch_) {
  assert(switch_ != NULL);

  ((test_spst_switch_t *)switch_)->state = TEST_SPST_SWITCH_CLOSE;
}

static void cpy_sw_open(wanbeiyu_hal_spst_switch_t *switch_) {
  assert(switch_ != NULL);

  ((test_spst_switch_t *)switch_)->state = TEST_SPST_SWITCH_OPEN;
}
static void cpy_sw_close(wanbeiyu_hal_spst_switch_t *switch_) {
  assert(switch_ != NULL);

  ((test_spst_switch_t *)switch_)->state = TEST_SPST_SWITCH_CLOSE;
}

typedef enum test_idac_state_t {
  TEST_IDAC_SOURCE,
  TEST_IDAC_SINK
} test_idac_state_t;

typedef struct test_idac_t {
  wanbeiyu_hal_idac_t base;
  test_idac_state_t state;
  wanbeiyu_uint8_t value;
} test_idac_t;

static void csa1_idac_source(wanbeiyu_hal_idac_t *idac,
                             wanbeiyu_uint8_t value) {
  assert(idac != NULL);

  ((test_idac_t *)idac)->state = TEST_IDAC_SOURCE;
  ((test_idac_t *)idac)->value = value;
}
static void csa1_idac_sink(wanbeiyu_hal_idac_t *idac, wanbeiyu_uint8_t value) {
  assert(idac != NULL);

  ((test_idac_t *)idac)->state = TEST_IDAC_SINK;
  ((test_idac_t *)idac)->value = value;
}

static void csa3_idac_source(wanbeiyu_hal_idac_t *idac,
                             wanbeiyu_uint8_t value) {
  assert(idac != NULL);

  ((test_idac_t *)idac)->state = TEST_IDAC_SOURCE;
  ((test_idac_t *)idac)->value = value;
}
static void csa3_idac_sink(wanbeiyu_hal_idac_t *idac, wanbeiyu_uint8_t value) {
  assert(idac != NULL);

  ((test_idac_t *)idac)->state = TEST_IDAC_SINK;
  ((test_idac_t *)idac)->value = value;
}

static void cpx_idac_source(wanbeiyu_hal_idac_t *idac, wanbeiyu_uint8_t value) {
  assert(idac != NULL);

  ((test_idac_t *)idac)->state = TEST_IDAC_SOURCE;
  ((test_idac_t *)idac)->value = value;
}
static void cpx_idac_sink(wanbeiyu_hal_idac_t *idac, wanbeiyu_uint8_t value) {
  assert(idac != NULL);

  ((test_idac_t *)idac)->state = TEST_IDAC_SINK;
  ((test_idac_t *)idac)->value = value;
}

static void cpy_idac_source(wanbeiyu_hal_idac_t *idac, wanbeiyu_uint8_t value) {
  assert(idac != NULL);

  ((test_idac_t *)idac)->state = TEST_IDAC_SOURCE;
  ((test_idac_t *)idac)->value = value;
}
static void cpy_idac_sink(wanbeiyu_hal_idac_t *idac, wanbeiyu_uint8_t value) {
  assert(idac != NULL);

  ((test_idac_t *)idac)->state = TEST_IDAC_SINK;
  ((test_idac_t *)idac)->value = value;
}

typedef struct test_rdac_320_steps_t {
  wanbeiyu_hal_rdac_320_steps_t base;
  wanbeiyu_uint16_t position;
} test_rdac_320_steps_t;

static void tsx_set_wiper_position(wanbeiyu_hal_rdac_320_steps_t *rdac,
                                   wanbeiyu_uint16_t position) {
  assert(rdac != NULL);
  assert(position < 320);

  ((test_rdac_320_steps_t *)rdac)->position = position;
}

typedef struct test_rdac_240_steps_t {
  wanbeiyu_hal_rdac_240_steps_t base;
  wanbeiyu_uint8_t position;
} test_rdac_240_steps_t;

static void tsy_set_wiper_position(wanbeiyu_hal_rdac_240_steps_t *rdac,
                                   wanbeiyu_uint8_t position) {
  assert(rdac != NULL);
  assert(position < 240);

  ((test_rdac_240_steps_t *)rdac)->position = position;
}

typedef struct test_uart_t {
  wanbeiyu_hal_uart_t base;
} test_uart_t;

static void test_uart_write(wanbeiyu_hal_uart_t *uart,
                            const wanbeiyu_uint8_t *buffer, size_t length) {
  size_t i = 0;

  (void)uart;
  assert(uart != NULL);

  for (i = 0; i < length; i++) {
    fprintf(stderr, "%02x ", buffer[i]);
  }
  fprintf(stderr, "\n");
}

static const struct {
  test_uart_t uart;
  test_spst_switch_t power_sw;
  test_spst_switch_t home_sw;
  test_spst_switch_t zr_sw;
  test_spst_switch_t zl_sw;
  test_spst_switch_t y_sw;
  test_spst_switch_t x_sw;
  test_spst_switch_t l_sw;
  test_spst_switch_t r_sw;
  test_spst_switch_t down_sw;
  test_spst_switch_t up_sw;
  test_spst_switch_t left_sw;
  test_spst_switch_t right_sw;
  test_spst_switch_t start_sw;
  test_spst_switch_t select_sw;
  test_spst_switch_t b_sw;
  test_spst_switch_t a_sw;
  test_spst_switch_t ts_sw;
  test_spst_switch_t csa1_sw;
  test_spst_switch_t csa3_sw;
  test_spst_switch_t cpx_sw;
  test_spst_switch_t cpy_sw;
  test_rdac_320_steps_t tsx_rdac;
  test_rdac_240_steps_t tsy_rdac;
  test_idac_t csa1_idac;
  test_idac_t csa3_idac;
  test_idac_t cpx_idac;
  test_idac_t cpy_idac;
} impl = {{{test_uart_write}},
          {{power_sw_open, power_sw_close}, TEST_SPST_SWITCH_OPEN},
          {{home_sw_open, home_sw_close}, TEST_SPST_SWITCH_OPEN},
          {{zr_sw_open, zr_sw_close}, TEST_SPST_SWITCH_OPEN},
          {{zl_sw_open, zl_sw_close}, TEST_SPST_SWITCH_OPEN},
          {{y_sw_open, y_sw_close}, TEST_SPST_SWITCH_OPEN},
          {{x_sw_open, x_sw_close}, TEST_SPST_SWITCH_OPEN},
          {{l_sw_open, l_sw_close}, TEST_SPST_SWITCH_OPEN},
          {{r_sw_open, r_sw_close}, TEST_SPST_SWITCH_OPEN},
          {{down_sw_open, down_sw_close}, TEST_SPST_SWITCH_OPEN},
          {{up_sw_open, up_sw_close}, TEST_SPST_SWITCH_OPEN},
          {{left_sw_open, left_sw_close}, TEST_SPST_SWITCH_OPEN},
          {{right_sw_open, right_sw_close}, TEST_SPST_SWITCH_OPEN},
          {{start_sw_open, start_sw_close}, TEST_SPST_SWITCH_OPEN},
          {{select_sw_open, select_sw_close}, TEST_SPST_SWITCH_OPEN},
          {{b_sw_open, b_sw_close}, TEST_SPST_SWITCH_OPEN},
          {{a_sw_open, a_sw_close}, TEST_SPST_SWITCH_OPEN},
          {{ts_sw_open, ts_sw_close}, TEST_SPST_SWITCH_OPEN},
          {{csa1_sw_open, csa1_sw_close}, TEST_SPST_SWITCH_OPEN},
          {{csa3_sw_open, csa3_sw_close}, TEST_SPST_SWITCH_OPEN},
          {{cpx_sw_open, cpx_sw_close}, TEST_SPST_SWITCH_OPEN},
          {{cpy_sw_open, cpy_sw_close}, TEST_SPST_SWITCH_OPEN},
          {{tsx_set_wiper_position}, 0},
          {{tsy_set_wiper_position}, 0},
          {{csa1_idac_source, csa1_idac_sink}, TEST_IDAC_SINK, 0},
          {{csa3_idac_source, csa3_idac_sink}, TEST_IDAC_SINK, 0},
          {{cpx_idac_source, cpx_idac_sink}, TEST_IDAC_SINK, 0},
          {{cpy_idac_source, cpy_idac_sink}, TEST_IDAC_SINK, 0}};

static const wanbeiyu_hal_t hal = {
    &(impl.uart.base),
    &(impl.power_sw.base),
    &(impl.home_sw.base),
    &(impl.zr_sw.base),
    &(impl.zl_sw.base),
    &(impl.y_sw.base),
    &(impl.x_sw.base),
    &(impl.l_sw.base),
    &(impl.r_sw.base),
    &(impl.down_sw.base),
    &(impl.up_sw.base),
    &(impl.left_sw.base),
    &(impl.right_sw.base),
    &(impl.start_sw.base),
    &(impl.select_sw.base),
    &(impl.b_sw.base),
    &(impl.a_sw.base),
    {&(impl.tsx_rdac.base), &(impl.tsy_rdac.base), &(impl.ts_sw.base)},
    {&(impl.csa1_idac.base), &(impl.csa1_sw.base), &(impl.csa3_idac.base),
     &(impl.csa3_sw.base)},
    {&(impl.cpx_idac.base), &(impl.cpx_sw.base), &(impl.cpy_idac.base),
     &(impl.cpy_sw.base)}};

int main(void) {
  wanbeiyu_t wanbeiyu;

  wanbeiyu_uint8_t input[10] = {WANBEIYU_COMMAND_GET_CONSOLE_STATE};
  wanbeiyu_init(&wanbeiyu, &hal);

  wanbeiyu_on_data(&wanbeiyu, input, sizeof(input));
  return 0;
}