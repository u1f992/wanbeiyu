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

#include "project.h"

#include <stdio.h>

#include <wanbeiyu.h>

#define USBFS_MODE_DEVICE 0

static bool USBUART_Started = false;

static void USBUART_StartIfVBusPresent() {
  // https://community.infineon.com/t5/Knowledge-Base-Articles/Troubleshooting-PSoC-3-PSoC-4-L-Series-and-PSoC-5LP-USB-Designs/ta-p/256817
  if (!USBUART_VBusPresent()) {
    if (USBUART_Started) {
      USBUART_Stop();
      USBUART_Started = false;
    }
  } else {
    if (!USBUART_Started) {
      // https://www.infineon.com/dgdl/Infineon-Component_USBFS_V3.2-Software%20Module%20Datasheets-v03_02-EN.pdf?fileId=8ac78c8c7d0d8da4017d0e818d2f1332
      USBUART_Start(USBFS_MODE_DEVICE, USBUART_5V_OPERATION);
      while (!USBUART_GetConfiguration())
        ;
      USBUART_CDC_Init();
      USBUART_Started = true;
    }
    // https://github.com/Infineon/PSoC4-MCU-USB-Connectivity-Designs/blob/d739e38414b1ff6a0f522fd9802a13dba2c0e13a/USBFS_UART/USBFS_UART.cydsn/main.c#L88-L97
    if (USBUART_IsConfigurationChanged()) {
      while (!USBUART_GetConfiguration())
        ;
      USBUART_CDC_Init();
    }
  }
}

static void USBUART_SendString(const char *string) {
  if (!USBUART_Started) {
    return;
  }
  USBUART_PutString(string);
  // const char *ptr = string;
  // while (*ptr != '\0') {
  //  USBUART_PutChar(*ptr);
  //  ptr++;
  //  CyDelay(10);
  //}
}

static void SPI_SpiUartWriteTxDataBlocking(uint32 txData) {
  SPI_SpiUartWriteTxData(txData);
  while (SPI_SpiIsBusBusy() != 0)
    ;
}

#define IDAC_POLARITY_SOURCE 0
#define IDAC_POLARITY_SINK 1

/**
 * https://community.infineon.com/t5/PSOC-4/How-to-switch-polarity-of-IDAC-on-PSOC-4/m-p/107510#M14468
 */
static void IDAC_CStick_1_SetPolarity(uint8 polarity) {
  uint8 savedIntrStatus = CyEnterCriticalSection();
  IDAC_CStick_1_IDAC_POLARITY_CONTROL_REG =
      (IDAC_CStick_1_IDAC_POLARITY_CONTROL_REG &
       ~(uint32)(IDAC_CStick_1_IDAC_POLARITY_MASK
                 << IDAC_CStick_1_IDAC_POLARITY_POSITION)) |
      ((uint32)polarity << IDAC_CStick_1_IDAC_POLARITY_POSITION);
  CyExitCriticalSection(savedIntrStatus);
}

static void IDAC_CStick_3_SetPolarity(uint8 polarity) {
  uint8 savedIntrStatus = CyEnterCriticalSection();
  IDAC_CStick_3_IDAC_POLARITY_CONTROL_REG =
      (IDAC_CStick_3_IDAC_POLARITY_CONTROL_REG &
       ~(uint32)(IDAC_CStick_3_IDAC_POLARITY_MASK
                 << IDAC_CStick_3_IDAC_POLARITY_POSITION)) |
      ((uint32)polarity << IDAC_CStick_3_IDAC_POLARITY_POSITION);
  CyExitCriticalSection(savedIntrStatus);
}

static void IDAC_CirclePad_X_SetPolarity(uint8 polarity) {
  uint8 savedIntrStatus = CyEnterCriticalSection();
  IDAC_CirclePad_X_IDAC_POLARITY_CONTROL_REG =
      (IDAC_CirclePad_X_IDAC_POLARITY_CONTROL_REG &
       ~(uint32)(IDAC_CirclePad_X_IDAC_POLARITY_MASK
                 << IDAC_CirclePad_X_IDAC_POLARITY_POSITION)) |
      ((uint32)polarity << IDAC_CirclePad_X_IDAC_POLARITY_POSITION);
  CyExitCriticalSection(savedIntrStatus);
}

static void IDAC_CirclePad_Y_SetPolarity(uint8 polarity) {
  uint8 savedIntrStatus = CyEnterCriticalSection();
  IDAC_CirclePad_Y_IDAC_POLARITY_CONTROL_REG =
      (IDAC_CirclePad_Y_IDAC_POLARITY_CONTROL_REG &
       ~(uint32)(IDAC_CirclePad_Y_IDAC_POLARITY_MASK
                 << IDAC_CirclePad_Y_IDAC_POLARITY_POSITION)) |
      ((uint32)polarity << IDAC_CirclePad_Y_IDAC_POLARITY_POSITION);
  CyExitCriticalSection(savedIntrStatus);
}

static void a_switch_open(wanbeiyu_spst_switch_t *super) {
  assert(super != NULL);
  (void)super;
  Pin_A_Write(1);
}

static void a_switch_close(wanbeiyu_spst_switch_t *super) {
  assert(super != NULL);
  (void)super;
  Pin_A_Write(0);
}

static void b_switch_open(wanbeiyu_spst_switch_t *super) {
  assert(super != NULL);
  (void)super;
  Pin_B_Write(1);
}

static void b_switch_close(wanbeiyu_spst_switch_t *super) {
  assert(super != NULL);
  (void)super;
  Pin_B_Write(0);
}

static void select_switch_open(wanbeiyu_spst_switch_t *super) {
  assert(super != NULL);
  (void)super;
  Pin_Select_Write(1);
}

static void select_switch_close(wanbeiyu_spst_switch_t *super) {
  assert(super != NULL);
  (void)super;
  Pin_Select_Write(0);
}

static void start_switch_open(wanbeiyu_spst_switch_t *super) {
  assert(super != NULL);
  (void)super;
  Pin_Start_Write(1);
}

static void start_switch_close(wanbeiyu_spst_switch_t *super) {
  assert(super != NULL);
  (void)super;
  Pin_Start_Write(0);
}

static void right_switch_open(wanbeiyu_spst_switch_t *super) {
  assert(super != NULL);
  (void)super;
  Pin_Right_Write(1);
}

static void right_switch_close(wanbeiyu_spst_switch_t *super) {
  assert(super != NULL);
  (void)super;
  Pin_Right_Write(0);
}

static void left_switch_open(wanbeiyu_spst_switch_t *super) {
  assert(super != NULL);
  (void)super;
  Pin_Left_Write(1);
}

static void left_switch_close(wanbeiyu_spst_switch_t *super) {
  assert(super != NULL);
  (void)super;
  Pin_Left_Write(0);
}

static void up_switch_open(wanbeiyu_spst_switch_t *super) {
  assert(super != NULL);
  (void)super;
  Pin_Up_Write(1);
}

static void up_switch_close(wanbeiyu_spst_switch_t *super) {
  assert(super != NULL);
  (void)super;
  Pin_Up_Write(0);
}

static void down_switch_open(wanbeiyu_spst_switch_t *super) {
  assert(super != NULL);
  (void)super;
  Pin_Down_Write(1);
}

static void down_switch_close(wanbeiyu_spst_switch_t *super) {
  assert(super != NULL);
  (void)super;
  Pin_Down_Write(0);
}

static void r_switch_open(wanbeiyu_spst_switch_t *super) {
  assert(super != NULL);
  (void)super;
  Pin_R_Write(1);
}

static void r_switch_close(wanbeiyu_spst_switch_t *super) {
  assert(super != NULL);
  (void)super;
  Pin_R_Write(0);
}

static void l_switch_open(wanbeiyu_spst_switch_t *super) {
  assert(super != NULL);
  (void)super;
  Pin_L_Write(1);
}

static void l_switch_close(wanbeiyu_spst_switch_t *super) {
  assert(super != NULL);
  (void)super;
  Pin_L_Write(0);
}

static void x_switch_open(wanbeiyu_spst_switch_t *super) {
  assert(super != NULL);
  (void)super;
  Pin_X_Write(1);
}

static void x_switch_close(wanbeiyu_spst_switch_t *super) {
  assert(super != NULL);
  (void)super;
  Pin_X_Write(0);
}

static void y_switch_open(wanbeiyu_spst_switch_t *super) {
  assert(super != NULL);
  (void)super;
  Pin_Y_Write(1);
}

static void y_switch_close(wanbeiyu_spst_switch_t *super) {
  assert(super != NULL);
  (void)super;
  Pin_Y_Write(0);
}

static void zl_switch_open(wanbeiyu_spst_switch_t *super) {
  assert(super != NULL);
  (void)super;
  Pin_ZL_Write(1);
}

static void zl_switch_close(wanbeiyu_spst_switch_t *super) {
  assert(super != NULL);
  (void)super;
  Pin_ZL_Write(0);
}

static void zr_switch_open(wanbeiyu_spst_switch_t *super) {
  assert(super != NULL);
  (void)super;
  Pin_ZR_Write(1);
}

static void zr_switch_close(wanbeiyu_spst_switch_t *super) {
  assert(super != NULL);
  (void)super;
  Pin_ZR_Write(0);
}

static void home_switch_open(wanbeiyu_spst_switch_t *super) {
  assert(super != NULL);
  (void)super;
  Pin_Home_Write(1);
}

static void home_switch_close(wanbeiyu_spst_switch_t *super) {
  assert(super != NULL);
  (void)super;
  Pin_Home_Write(0);
}

static void power_switch_open(wanbeiyu_spst_switch_t *super) {
  assert(super != NULL);
  (void)super;
  Pin_Power_Write(1);
}

static void power_switch_close(wanbeiyu_spst_switch_t *super) {
  assert(super != NULL);
  (void)super;
  Pin_Power_Write(0);
}

static uint16_t map_319_to_510(uint16_t value) {
  uint16_t ret;
  assert(value <= 319);
  /*
   * Add 159 (half of 319) to approximate rounding
   * and reduce errors in integer calculations.
   */
  ret = (value * 510 + 159) / 319;
  assert(ret <= 510);
  return ret;
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
static void
touch_screen_horizontal_set_wiper_position(wanbeiyu_rdac_320_steps_t *super,
                                           wanbeiyu_uint16_t position) {
  /* clang-format on */
  uint8 r1_2;
  uint8 r3;
  assert(super != NULL);
  assert(position < 320);
  (void)super;
  position = map_319_to_510(position);
  r1_2 = position < 255 ? 0 : position - 255;
  r3 = position >= 255 ? 255 : position;
  SPI_SpiUartWriteTxDataBlocking(0b0000000000 | r1_2);
  SPI_SpiUartWriteTxDataBlocking(0b0100000000 | r3);
  SPI_SpiUartWriteTxDataBlocking(0b1000000000 | r1_2);
}

static uint8_t map_239_to_255(uint8_t value) {
  assert(value <= 239);
  /*
   * Add 119 (half of 239) to approximate rounding
   * and reduce errors in integer calculations.
   */
  return (value * 255 + 119) / 239;
}

static void
touch_screen_vertical_set_wiper_position(wanbeiyu_rdac_240_steps_t *super,
                                         wanbeiyu_uint8_t position) {
  assert(super != NULL);
  assert(position < 240);
  (void)super;
  position = map_239_to_255(position);
  SPI_SpiUartWriteTxDataBlocking(0b1100000000 | position);
}

static void touch_screen_switch_open(wanbeiyu_spst_switch_t *super) {
  assert(super != NULL);
  (void)super;
  AMux_TouchScreen_DisconnectAll();
}

static void touch_screen_switch_close(wanbeiyu_spst_switch_t *super) {
  assert(super != NULL);
  (void)super;
  AMux_TouchScreen_Select(0);
}

static void c_stick_1_source(wanbeiyu_idac_t *super, wanbeiyu_uint8_t value) {
  assert(super != NULL);
  (void)super;
  IDAC_CStick_1_SetPolarity(IDAC_POLARITY_SINK);
  IDAC_CStick_1_SetValue(value);
}

static void c_stick_1_sink(wanbeiyu_idac_t *super, wanbeiyu_uint8_t value) {
  assert(super != NULL);
  (void)super;
  IDAC_CStick_1_SetPolarity(IDAC_POLARITY_SOURCE);
  IDAC_CStick_1_SetValue(value);
}

static void c_stick_1_switch_open(wanbeiyu_spst_switch_t *super) {
  assert(super != NULL);
  (void)super;
  AMux_CStick_1_DisconnectAll();
}

static void c_stick_1_switch_close(wanbeiyu_spst_switch_t *super) {
  assert(super != NULL);
  (void)super;
  AMux_CStick_1_Select(0);
}

static void c_stick_3_source(wanbeiyu_idac_t *super, wanbeiyu_uint8_t value) {
  assert(super != NULL);
  (void)super;
  IDAC_CStick_3_SetPolarity(IDAC_POLARITY_SINK);
  IDAC_CStick_3_SetValue(value);
}

static void c_stick_3_sink(wanbeiyu_idac_t *super, wanbeiyu_uint8_t value) {
  assert(super != NULL);
  (void)super;
  IDAC_CStick_3_SetPolarity(IDAC_POLARITY_SOURCE);
  IDAC_CStick_3_SetValue(value);
}

static void c_stick_3_switch_open(wanbeiyu_spst_switch_t *super) {
  assert(super != NULL);
  (void)super;
  AMux_CStick_3_DisconnectAll();
}

static void c_stick_3_switch_close(wanbeiyu_spst_switch_t *super) {
  assert(super != NULL);
  (void)super;
  AMux_CStick_3_Select(0);
}

static uint8_t map_255_to_127(uint8_t value) {
  return (value * 127 + 127) / 255;
}

static void circle_pad_x_source(wanbeiyu_idac_t *super,
                                wanbeiyu_uint8_t value) {
  assert(super != NULL);
  (void)super;
  IDAC_CirclePad_X_SetPolarity(IDAC_POLARITY_SINK);
  IDAC_CirclePad_X_SetValue(map_255_to_127(value));
}

static void circle_pad_x_sink(wanbeiyu_idac_t *super, wanbeiyu_uint8_t value) {
  assert(super != NULL);
  (void)super;
  IDAC_CirclePad_X_SetPolarity(IDAC_POLARITY_SOURCE);
  IDAC_CirclePad_X_SetValue(map_255_to_127(value));
}

static void circle_pad_x_switch_open(wanbeiyu_spst_switch_t *super) {
  assert(super != NULL);
  (void)super;
  AMux_CirclePad_X_DisconnectAll();
}

static void circle_pad_x_switch_close(wanbeiyu_spst_switch_t *super) {
  assert(super != NULL);
  (void)super;
  AMux_CirclePad_X_Select(0);
}

static void circle_pad_y_source(wanbeiyu_idac_t *super,
                                wanbeiyu_uint8_t value) {
  assert(super != NULL);
  (void)super;
  IDAC_CirclePad_Y_SetPolarity(IDAC_POLARITY_SINK);
  IDAC_CirclePad_Y_SetValue(map_255_to_127(value));
}

static void circle_pad_y_sink(wanbeiyu_idac_t *super, wanbeiyu_uint8_t value) {
  assert(super != NULL);
  (void)super;
  IDAC_CirclePad_Y_SetPolarity(IDAC_POLARITY_SOURCE);
  IDAC_CirclePad_Y_SetValue(map_255_to_127(value));
}

static void circle_pad_y_switch_open(wanbeiyu_spst_switch_t *super) {
  assert(super != NULL);
  (void)super;
  AMux_CirclePad_Y_DisconnectAll();
}

static void circle_pad_y_switch_close(wanbeiyu_spst_switch_t *super) {
  assert(super != NULL);
  (void)super;
  AMux_CirclePad_Y_Select(0);
}

#define WANBEIYU_STATE_STRING_MAX_LENGTH                                       \
  sizeof("{a:0,b:0,select:0,start:0,right:0,left:0,up:0,down:0,r:0,l:0,x:0,y:" \
         "0,zl:0,zr:0,home:0,power:0,touch_screen:[319,239],c_stick:[255,255]" \
         ",circle_pad:[255,255]}")

static int wanbeiyu_state_to_string(const wanbeiyu_state_t *state,
                                    char *buffer) {
  char touch_screen[sizeof("[319,239]")];
  char c_stick[sizeof("[255,255]")];
  char circle_pad[sizeof("[255,255]")];

  assert(state != NULL);
  assert(buffer != NULL);
  /* assert(sizeof(buffer) >= WANBEIYU_CONSOLE_STATE_STRING_MAX_LENGTH); */

  if (state->touch_screen) {
    sprintf(touch_screen, "[%d,%d]", state->touch_screen->x,
            state->touch_screen->y);
  } else {
    touch_screen[0] = '[';
    touch_screen[1] = ']';
    touch_screen[2] = '\0';
  }

  if (state->c_stick.x || state->c_stick.y) {
    sprintf(c_stick, "[%d,%d]", state->c_stick.x ? *(state->c_stick.x) : 80,
            state->c_stick.y ? *(state->c_stick.y) : 80);
  } else {
    c_stick[0] = '[';
    c_stick[1] = ']';
    c_stick[2] = '\0';
  }

  if (state->circle_pad.x || state->circle_pad.y) {
    sprintf(circle_pad, "[%d,%d]",
            state->circle_pad.x ? *(state->circle_pad.x) : 80,
            state->circle_pad.y ? *(state->circle_pad.y) : 80);
  } else {
    circle_pad[0] = '[';
    circle_pad[1] = ']';
    circle_pad[2] = '\0';
  }

  return sprintf(buffer,
                 "{a:%d,b:%d,select:%d,start:%d,right:%d,left:%d,up:%d,down:%d,"
                 "r:%d,l:%d,x:%d,y:%d,zl:%d,zr:%d,home:%d,power:%d,touch_"
                 "screen:%s,c_stick:%s,circle_pad:%s}",
                 state->a, state->b, state->select, state->start, state->right,
                 state->left, state->up, state->down, state->r, state->l,
                 state->x, state->y, state->zl, state->zr, state->home,
                 state->power, touch_screen, c_stick, circle_pad);
}

int main(void) {
  wanbeiyu_spst_switch_t a_switch;
  wanbeiyu_spst_switch_t b_switch;
  wanbeiyu_spst_switch_t select_switch;
  wanbeiyu_spst_switch_t start_switch;
  wanbeiyu_spst_switch_t right_switch;
  wanbeiyu_spst_switch_t left_switch;
  wanbeiyu_spst_switch_t up_switch;
  wanbeiyu_spst_switch_t down_switch;
  wanbeiyu_spst_switch_t r_switch;
  wanbeiyu_spst_switch_t l_switch;
  wanbeiyu_spst_switch_t x_switch;
  wanbeiyu_spst_switch_t y_switch;
  wanbeiyu_spst_switch_t zl_switch;
  wanbeiyu_spst_switch_t zr_switch;
  wanbeiyu_spst_switch_t home_switch;
  wanbeiyu_spst_switch_t power_switch;

  wanbeiyu_rdac_320_steps_t touch_screen_horizontal;
  wanbeiyu_rdac_240_steps_t touch_screen_vertical;
  wanbeiyu_spst_switch_t touch_screen_switch;

  wanbeiyu_idac_t c_stick_1;
  wanbeiyu_spst_switch_t c_stick_1_switch;
  wanbeiyu_idac_t c_stick_3;
  wanbeiyu_spst_switch_t c_stick_3_switch;

  wanbeiyu_idac_t circle_pad_x;
  wanbeiyu_spst_switch_t circle_pad_x_switch;
  wanbeiyu_idac_t circle_pad_y;
  wanbeiyu_spst_switch_t circle_pad_y_switch;

  wanbeiyu_console_t console;
  wanbeiyu_state_t state;

  enum {
    STATE_INITIAL,
    STATE_NATIVE_DATA_0,
    STATE_NATIVE_DATA_1,
    STATE_NATIVE_DATA_2,
    STATE_NATIVE_DATA_3,
    STATE_NATIVE_DATA_4,
    STATE_NATIVE_DATA_5,
    STATE_NATIVE_DATA_6,
    STATE_NATIVE_DATA_7,
    STATE_NATIVE_DATA_8
  } buffer_state = STATE_INITIAL;
  /*
   * > The maximum amount of received data at a time is limited to 64 bytes.
   * Document Number: 002-19744 Rev. *A
   */
  uint8 uart_buffer[64];
  uint8 state_buffer[10];

  char string[WANBEIYU_STATE_STRING_MAX_LENGTH];

  CyGlobalIntEnable; /* Enable global interrupts. */

  /* Place your initialization/startup code here (e.g. MyInst_Start()) */
  SPI_Start();
  SPI_SpiSetActiveSlaveSelect(SPI_SPI_SLAVE_SELECT0);
  AMux_TouchScreen_Start();

  IDAC_CStick_1_Start();
  AMux_CStick_1_Start();
  IDAC_CStick_3_Start();
  AMux_CStick_3_Start();

  IDAC_CirclePad_X_Start();
  AMux_CirclePad_X_Start();
  IDAC_CirclePad_Y_Start();
  AMux_CirclePad_Y_Start();

  wanbeiyu_spst_switch_init(&a_switch, a_switch_open, a_switch_close);
  wanbeiyu_button_init(&(console.a), &a_switch);

  wanbeiyu_spst_switch_init(&b_switch, b_switch_open, b_switch_close);
  wanbeiyu_button_init(&(console.b), &b_switch);

  wanbeiyu_spst_switch_init(&select_switch, select_switch_open,
                            select_switch_close);
  wanbeiyu_button_init(&(console.select), &select_switch);

  wanbeiyu_spst_switch_init(&start_switch, start_switch_open,
                            start_switch_close);
  wanbeiyu_button_init(&(console.start), &start_switch);

  wanbeiyu_spst_switch_init(&right_switch, right_switch_open,
                            right_switch_close);
  wanbeiyu_button_init(&(console.right), &right_switch);

  wanbeiyu_spst_switch_init(&left_switch, left_switch_open, left_switch_close);
  wanbeiyu_button_init(&(console.left), &left_switch);

  wanbeiyu_spst_switch_init(&up_switch, up_switch_open, up_switch_close);
  wanbeiyu_button_init(&(console.up), &up_switch);

  wanbeiyu_spst_switch_init(&down_switch, down_switch_open, down_switch_close);
  wanbeiyu_button_init(&(console.down), &down_switch);

  wanbeiyu_spst_switch_init(&r_switch, r_switch_open, r_switch_close);
  wanbeiyu_button_init(&(console.r), &r_switch);

  wanbeiyu_spst_switch_init(&l_switch, l_switch_open, l_switch_close);
  wanbeiyu_button_init(&(console.l), &l_switch);

  wanbeiyu_spst_switch_init(&x_switch, x_switch_open, x_switch_close);
  wanbeiyu_button_init(&(console.x), &x_switch);

  wanbeiyu_spst_switch_init(&y_switch, y_switch_open, y_switch_close);
  wanbeiyu_button_init(&(console.y), &y_switch);

  wanbeiyu_spst_switch_init(&zl_switch, zl_switch_open, zl_switch_close);
  wanbeiyu_button_init(&(console.zl), &zl_switch);

  wanbeiyu_spst_switch_init(&zr_switch, zr_switch_open, zr_switch_close);
  wanbeiyu_button_init(&(console.zr), &zr_switch);

  wanbeiyu_spst_switch_init(&home_switch, home_switch_open, home_switch_close);
  wanbeiyu_button_init(&(console.home), &home_switch);

  wanbeiyu_spst_switch_init(&power_switch, power_switch_open,
                            power_switch_close);
  wanbeiyu_button_init(&(console.power), &power_switch);

  wanbeiyu_rdac_320_steps_init(&touch_screen_horizontal,
                               touch_screen_horizontal_set_wiper_position);
  wanbeiyu_rdac_240_steps_init(&touch_screen_vertical,
                               touch_screen_vertical_set_wiper_position);
  wanbeiyu_spst_switch_init(&touch_screen_switch, touch_screen_switch_open,
                            touch_screen_switch_close);
  wanbeiyu_touch_screen_init(&(console.touch_screen), &touch_screen_horizontal,
                             &touch_screen_vertical, &touch_screen_switch);

  wanbeiyu_idac_init(&c_stick_1, c_stick_1_source, c_stick_1_sink);
  wanbeiyu_spst_switch_init(&c_stick_1_switch, c_stick_1_switch_open,
                            c_stick_1_switch_close);
  wanbeiyu_idac_init(&c_stick_3, c_stick_3_source, c_stick_3_sink);
  wanbeiyu_spst_switch_init(&c_stick_3_switch, c_stick_3_switch_open,
                            c_stick_3_switch_close);
  wanbeiyu_c_stick_init(&(console.c_stick), &c_stick_1, &c_stick_1_switch,
                        &c_stick_3, &c_stick_3_switch);

  wanbeiyu_idac_init(&circle_pad_x, circle_pad_x_source, circle_pad_x_sink);
  wanbeiyu_spst_switch_init(&circle_pad_x_switch, circle_pad_x_switch_open,
                            circle_pad_x_switch_close);
  wanbeiyu_idac_init(&circle_pad_y, circle_pad_y_source, circle_pad_y_sink);
  wanbeiyu_spst_switch_init(&circle_pad_y_switch, circle_pad_y_switch_open,
                            circle_pad_y_switch_close);
  wanbeiyu_circle_pad_init(&(console.circle_pad), &circle_pad_x,
                           &circle_pad_x_switch, &circle_pad_y,
                           &circle_pad_y_switch);

  wanbeiyu_console_clear(&console);
  wanbeiyu_touch_screen_release(&(console.touch_screen));
  wanbeiyu_c_stick_release(&(console.c_stick));
  wanbeiyu_circle_pad_release(&(console.circle_pad));

  for (;;) {
    uint16_t count;

    USBUART_StartIfVBusPresent();
    if (!USBUART_Started) {
      buffer_state = STATE_INITIAL;
      continue;
    }
    count = USBUART_GetCount();
    if (count == 0) {
      continue;
    }
    sprintf(string, "%d\n", count);
    USBUART_SendString(string);

    assert(count <= 64);
    USBUART_GetData(uart_buffer, count);

    Pin_Status_Write(1);

    for (int i = 0; i < count; i++) {
      unsigned char c = uart_buffer[i];

      switch (buffer_state) {
      case STATE_INITIAL:
        if (c == 0xfb) {
          state_buffer[buffer_state++] = c;
        } else {
          buffer_state = STATE_INITIAL;
        }
        break;
      case STATE_NATIVE_DATA_0:
      case STATE_NATIVE_DATA_1:
      case STATE_NATIVE_DATA_2:
      case STATE_NATIVE_DATA_3:
      case STATE_NATIVE_DATA_4:
      case STATE_NATIVE_DATA_5:
      case STATE_NATIVE_DATA_6:
      case STATE_NATIVE_DATA_7:
        state_buffer[buffer_state++] = c;
        break;
      case STATE_NATIVE_DATA_8:
        state_buffer[buffer_state] = c;
        wanbeiyu_deserialize(state_buffer, 10, &state);
        wanbeiyu_console_set(&console, &state);

        wanbeiyu_state_to_string(&state, string);
        USBUART_SendString(string);

        buffer_state = STATE_INITIAL;
        break;

      default:
        buffer_state = STATE_INITIAL;
        break;
      }
    }
  }
}

/* [] END OF FILE */
