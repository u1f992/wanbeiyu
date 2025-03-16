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

static void test_spst_switch_init(test_spst_switch_t *switch_,
                                  void (*open)(wanbeiyu_hal_spst_switch_t *),
                                  void (*close)(wanbeiyu_hal_spst_switch_t *)) {
  assert(switch_ != NULL);
  assert(open != NULL);
  assert(close != NULL);

  wanbeiyu_hal_spst_switch_init(&(switch_->base), open, close);
  switch_->state = TEST_SPST_SWITCH_OPEN;
}

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

static void
test_idac_init(test_idac_t *idac,
               void (*source)(wanbeiyu_hal_idac_t *, wanbeiyu_uint8_t),
               void (*sink)(wanbeiyu_hal_idac_t *, wanbeiyu_uint8_t)) {
  assert(idac != NULL);
  assert(source != NULL);
  assert(sink != NULL);

  wanbeiyu_hal_idac_init(&(idac->base), source, sink);
  idac->state = TEST_IDAC_SINK;
  idac->value = 0;
}

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

static void test_rdac_320_steps_init(
    test_rdac_320_steps_t *rdac,
    void (*set_wiper_position)(wanbeiyu_hal_rdac_320_steps_t *,
                               wanbeiyu_uint16_t)) {
  assert(rdac != NULL);
  assert(set_wiper_position != NULL);

  wanbeiyu_hal_rdac_320_steps_init(&(rdac->base), set_wiper_position);
  rdac->position = 0;
}

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

static void test_rdac_240_steps_init(
    test_rdac_240_steps_t *rdac,
    void (*set_wiper_position)(wanbeiyu_hal_rdac_240_steps_t *,
                               wanbeiyu_uint8_t)) {
  assert(rdac != NULL);
  assert(set_wiper_position != NULL);

  wanbeiyu_hal_rdac_240_steps_init(&(rdac->base), set_wiper_position);
  rdac->position = 0;
}

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

static void test_uart_init(test_uart_t *uart) {
  assert(uart != NULL);

  wanbeiyu_hal_uart_init(&(uart->base), test_uart_write);
}

typedef struct test_impl_t {
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
} test_impl_t;

static void test_impl_init(test_impl_t *impl) {
  test_uart_init(&(impl->uart));
  test_spst_switch_init(&(impl->power_sw), power_sw_open, power_sw_close);
  test_spst_switch_init(&(impl->home_sw), home_sw_open, home_sw_close);
  test_spst_switch_init(&(impl->zr_sw), zr_sw_open, zr_sw_close);
  test_spst_switch_init(&(impl->zl_sw), zl_sw_open, zl_sw_close);
  test_spst_switch_init(&(impl->y_sw), y_sw_open, y_sw_close);
  test_spst_switch_init(&(impl->x_sw), x_sw_open, x_sw_close);
  test_spst_switch_init(&(impl->l_sw), l_sw_open, l_sw_close);
  test_spst_switch_init(&(impl->r_sw), r_sw_open, r_sw_close);
  test_spst_switch_init(&(impl->down_sw), down_sw_open, down_sw_close);
  test_spst_switch_init(&(impl->up_sw), up_sw_open, up_sw_close);
  test_spst_switch_init(&(impl->left_sw), left_sw_open, left_sw_close);
  test_spst_switch_init(&(impl->right_sw), right_sw_open, right_sw_close);
  test_spst_switch_init(&(impl->start_sw), start_sw_open, start_sw_close);
  test_spst_switch_init(&(impl->select_sw), select_sw_open, select_sw_close);
  test_spst_switch_init(&(impl->b_sw), b_sw_open, b_sw_close);
  test_spst_switch_init(&(impl->a_sw), a_sw_open, a_sw_close);
  test_spst_switch_init(&(impl->ts_sw), ts_sw_open, ts_sw_close);
  test_spst_switch_init(&(impl->csa1_sw), csa1_sw_open, csa1_sw_close);
  test_spst_switch_init(&(impl->csa3_sw), csa3_sw_open, csa3_sw_close);
  test_spst_switch_init(&(impl->cpx_sw), cpx_sw_open, cpx_sw_close);
  test_spst_switch_init(&(impl->cpy_sw), cpy_sw_open, cpy_sw_close);
  test_rdac_320_steps_init(&(impl->tsx_rdac), tsx_set_wiper_position);
  test_rdac_240_steps_init(&(impl->tsy_rdac), tsy_set_wiper_position);
  test_idac_init(&(impl->csa1_idac), csa1_idac_source, csa1_idac_sink);
  test_idac_init(&(impl->csa3_idac), csa3_idac_source, csa3_idac_sink);
  test_idac_init(&(impl->cpx_idac), cpx_idac_source, cpx_idac_sink);
  test_idac_init(&(impl->cpy_idac), cpy_idac_source, cpy_idac_sink);
}

int main(void) {
  wanbeiyu_t wanbeiyu;
  wanbeiyu_hal_t hal;
  test_impl_t impl;

  wanbeiyu_uint8_t input[10] = {
      WANBEIYU_COMMAND_GET_CONSOLE_STATE, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  test_impl_init(&impl);
  wanbeiyu_hal_init(
      &hal, &(impl.uart.base), &(impl.power_sw.base), &(impl.home_sw.base),
      &(impl.zr_sw.base), &(impl.zl_sw.base), &(impl.y_sw.base),
      &(impl.x_sw.base), &(impl.l_sw.base), &(impl.r_sw.base),
      &(impl.down_sw.base), &(impl.up_sw.base), &(impl.left_sw.base),
      &(impl.right_sw.base), &(impl.start_sw.base), &(impl.select_sw.base),
      &(impl.b_sw.base), &(impl.a_sw.base), &(impl.tsx_rdac.base),
      &(impl.tsy_rdac.base), &(impl.ts_sw.base), &(impl.csa1_idac.base),
      &(impl.csa1_sw.base), &(impl.csa3_idac.base), &(impl.csa3_sw.base),
      &(impl.cpx_idac.base), &(impl.cpx_sw.base), &(impl.cpy_idac.base),
      &(impl.cpy_sw.base));
  wanbeiyu_init(&wanbeiyu, &hal);

  wanbeiyu_on_data(&wanbeiyu, input, sizeof(input));
  return 0;
}