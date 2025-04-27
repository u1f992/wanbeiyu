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

#include <wanbeiyu.h>

void wanbeiyu_hook_on_get(wanbeiyu_state_t const *state) {
  assert(state != NULL);
  (void)state;
  Pin_USBUART_Status_Write(0);
  Timer_USBUART_Status_Stop();
  Timer_USBUART_Status_WriteCounter(0);
  Timer_USBUART_Status_Start();
}
void wanbeiyu_hook_on_set(wanbeiyu_state_t const *state) {
  assert(state != NULL);
  (void)state;
  Pin_USBUART_Status_Write(0);
  Timer_USBUART_Status_Stop();
  Timer_USBUART_Status_WriteCounter(0);
  Timer_USBUART_Status_Start();
}

#define USBFS_DEVICE 0
/*
 * > The maximum amount of received data at a time is limited to 64 bytes.
 * Document Number: 002-19744 Rev. *A
 */
#define USBUART_BUFFER_SIZE 64
static uint8 USBUART_Started = 0;

void wanbeiyu_hal_uart_read(wanbeiyu_uint8_t *buffer, size_t *length) {
  assert(buffer != NULL);
  assert(length != NULL);
  /*
   * https://community.infineon.com/t5/Knowledge-Base-Articles/Troubleshooting-PSoC-3-PSoC-4-L-Series-and-PSoC-5LP-USB-Designs/ta-p/256817#toc-hId-1576988805
   */
  if (!USBUART_VBusPresent()) {
    USBUART_Stop();
    USBUART_Started = 0;
    Pin_USBUART_Status_Write(0);
    *length = 0;
    return;
  } else if (!USBUART_Started) {
    USBUART_Start(USBFS_DEVICE, USBUART_5V_OPERATION);
    USBUART_Started = 1;
    Pin_USBUART_Status_Write(1);
  }
  /*
   * https://github.com/Infineon/PSoC4-MCU-USB-Connectivity-Designs/blob/d739e38414b1ff6a0f522fd9802a13dba2c0e13a/USBFS_UART/USBFS_UART.cydsn/main.c#L87-L97
   */
  if (USBUART_IsConfigurationChanged() && USBUART_GetConfiguration()) {
    USBUART_CDC_Init();
  }
  /*
   * https://github.com/Infineon/PSoC4-MCU-USB-Connectivity-Designs/blob/d739e38414b1ff6a0f522fd9802a13dba2c0e13a/USBFS_UART/USBFS_UART.cydsn/main.c#L99-L178
   */
  if (!USBUART_GetConfiguration() || !USBUART_DataIsReady()) {
    *length = 0;
    return;
  }
  *length = USBUART_GetAll(buffer);
  assert(*length <= USBUART_BUFFER_SIZE);
  assert(*length <= WANBEIYU_HAL_UART_BUFFER_SIZE);
}

void wanbeiyu_hal_uart_write(wanbeiyu_uint8_t const *buffer, size_t length) {
  assert(buffer != NULL);
  while (USBUART_CDCIsReady() == 0)
    ;
  USBUART_PutData(buffer, length);
  /*
   * https://github.com/Infineon/PSoC4-MCU-USB-Connectivity-Designs/blob/d739e38414b1ff6a0f522fd9802a13dba2c0e13a/USBFS_UART/USBFS_UART.cydsn/main.c#L118-L132
   */
  if (USBUART_BUFFER_SIZE == length) {
    while (USBUART_CDCIsReady() == 0)
      ;
    USBUART_PutData(NULL, 0);
  }
}

void wanbeiyu_hal_spst_switch_buttons_power_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  (void)state;
}
void wanbeiyu_hal_spst_switch_buttons_home_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  (void)state;
}
void wanbeiyu_hal_spst_switch_buttons_zr_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  (void)state;
}
void wanbeiyu_hal_spst_switch_buttons_zl_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  (void)state;
}
void wanbeiyu_hal_spst_switch_buttons_y_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  (void)state;
}
void wanbeiyu_hal_spst_switch_buttons_x_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  (void)state;
}
void wanbeiyu_hal_spst_switch_buttons_l_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  (void)state;
}
void wanbeiyu_hal_spst_switch_buttons_r_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  (void)state;
}
void wanbeiyu_hal_spst_switch_buttons_down_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  (void)state;
}
void wanbeiyu_hal_spst_switch_buttons_up_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  (void)state;
}
void wanbeiyu_hal_spst_switch_buttons_left_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  (void)state;
}
void wanbeiyu_hal_spst_switch_buttons_right_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  (void)state;
}
void wanbeiyu_hal_spst_switch_buttons_start_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  (void)state;
}
void wanbeiyu_hal_spst_switch_buttons_select_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  (void)state;
}
void wanbeiyu_hal_spst_switch_buttons_b_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  (void)state;
}
void wanbeiyu_hal_spst_switch_buttons_a_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  (void)state;
}

void wanbeiyu_hal_rdac_touch_screen_pin_2_4_set(wanbeiyu_uint16_t position) {
  uint8 r1_2;
  uint8 r3;
  assert(position < 320);
  position = wanbeiyu_helper_map_319_to_510(position);
  r1_2 = position < 255 ? 0 : position - 255;
  r3 = position >= 255 ? 255 : position;
  SPI_SpiSetActiveSlaveSelect(SPI_SPI_SLAVE_SELECT0);
  /* https://github.com/Infineon/PSoC4-MCU-Digital-Designs/blob/72f1d4e035cda9354576b2631b1308c05ab79b63/SPI/CE95365%20-%20SPI%20Transmit%20and%20Receive%20using%20a%20Serial%20Communication%20Block%20(SCB)%20with%20PSoC%204/CE95365.cydsn/main.c#L58-L78 */
  SPI_ClearMasterInterruptSource(SPI_INTR_MASTER_SPI_DONE);
  SPI_SpiUartWriteTxData(0b0000000000 | r1_2);
  SPI_SpiUartWriteTxData(0b0100000000 | r3);
  SPI_SpiUartWriteTxData(0b1000000000 | r1_2);
  while ((SPI_GetMasterInterruptSource() & SPI_INTR_MASTER_SPI_DONE) == 0)
    ;
}
void wanbeiyu_hal_rdac_touch_screen_pin_3_1_set(wanbeiyu_uint8_t position) {
  assert(position < 240);
  position = wanbeiyu_helper_map_239_to_255(position);
  SPI_SpiSetActiveSlaveSelect(SPI_SPI_SLAVE_SELECT0);
  SPI_ClearMasterInterruptSource(SPI_INTR_MASTER_SPI_DONE);
  SPI_SpiUartWriteTxData(0b1100000000 | position);
  while ((SPI_GetMasterInterruptSource() & SPI_INTR_MASTER_SPI_DONE) == 0)
    ;
}
void wanbeiyu_hal_spst_switch_touch_screen_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  SPI_SpiSetActiveSlaveSelect(SPI_SPI_SLAVE_SELECT1);
  SPI_ClearMasterInterruptSource(SPI_INTR_MASTER_SPI_DONE);
  /*
   * > ... THE DEVICE USERS THE LAST 8 BITS RECEIVED TO UPDATE THE SWITCHES.
   * Maxim Integrated 19-7308; Rev 1; 6/14, P.16
   */
  SPI_SpiUartWriteTxData(state == WANBEIYU_HAL_SPST_SWITCH_CLOSE ? 0x0f : 0);
  while ((SPI_GetMasterInterruptSource() & SPI_INTR_MASTER_SPI_DONE) == 0)
    ;
}

void wanbeiyu_hal_idac_c_stick_pin_1_set(wanbeiyu_hal_idac_mode_t mode,
                                         wanbeiyu_uint8_t value) {
  (void)mode;
  (void)value;
}
void wanbeiyu_hal_spst_switch_c_stick_pin_1_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  (void)state;
}
void wanbeiyu_hal_idac_c_stick_pin_3_set(wanbeiyu_hal_idac_mode_t mode,
                                         wanbeiyu_uint8_t value) {
  (void)mode;
  (void)value;
}
void wanbeiyu_hal_spst_switch_c_stick_pin_3_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  (void)state;
}

void wanbeiyu_hal_idac_circle_pad_pin_2_set(wanbeiyu_hal_idac_mode_t mode,
                                            wanbeiyu_uint8_t value) {
  (void)mode;
  (void)value;
}
void wanbeiyu_hal_spst_switch_circle_pad_pin_2_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  (void)state;
}
void wanbeiyu_hal_idac_circle_pad_pin_4_set(wanbeiyu_hal_idac_mode_t mode,
                                            wanbeiyu_uint8_t value) {
  (void)mode;
  (void)value;
}
void wanbeiyu_hal_spst_switch_circle_pad_pin_4_set(
    wanbeiyu_hal_spst_switch_state_t state) {
  (void)state;
}

CY_ISR(ISR_USBUART_Status_Handler) {
  Pin_USBUART_Status_Write(1);
  Timer_USBUART_Status_ClearInterrupt(Timer_USBUART_Status_INTR_MASK_TC);
}

int main(void) {
  CyGlobalIntEnable; /* Enable global interrupts. */

  Pin_USBUART_Status_Write(0);
  ISR_USBUART_Status_StartEx(ISR_USBUART_Status_Handler);
  SPI_Start();
  wanbeiyu_init();

  for (;;) {
    wanbeiyu_loop();
  }
}

/* [] END OF FILE */
