#include <wanbeiyu/buttons.h>

void wanbeiyu_buttons_set(wanbeiyu_state_t const *state) {
  wanbeiyu_uint16_t buttons;
  assert(state != NULL);
  buttons = state->buttons;
  wanbeiyu_hal_spst_switch_buttons_power_set((buttons >> 15) & 1);
  wanbeiyu_hal_spst_switch_buttons_home_set((buttons >> 14) & 1);
  wanbeiyu_hal_spst_switch_buttons_zr_set((buttons >> 13) & 1);
  wanbeiyu_hal_spst_switch_buttons_zl_set((buttons >> 12) & 1);
  wanbeiyu_hal_spst_switch_buttons_y_set((buttons >> 11) & 1);
  wanbeiyu_hal_spst_switch_buttons_x_set((buttons >> 10) & 1);
  wanbeiyu_hal_spst_switch_buttons_l_set((buttons >> 9) & 1);
  wanbeiyu_hal_spst_switch_buttons_r_set((buttons >> 8) & 1);
  wanbeiyu_hal_spst_switch_buttons_down_set((buttons >> 7) & 1);
  wanbeiyu_hal_spst_switch_buttons_up_set((buttons >> 6) & 1);
  wanbeiyu_hal_spst_switch_buttons_left_set((buttons >> 5) & 1);
  wanbeiyu_hal_spst_switch_buttons_right_set((buttons >> 4) & 1);
  wanbeiyu_hal_spst_switch_buttons_start_set((buttons >> 3) & 1);
  wanbeiyu_hal_spst_switch_buttons_select_set((buttons >> 2) & 1);
  wanbeiyu_hal_spst_switch_buttons_b_set((buttons >> 1) & 1);
  wanbeiyu_hal_spst_switch_buttons_a_set((buttons >> 0) & 1);
}