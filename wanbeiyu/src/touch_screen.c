#include <wanbeiyu/touch_screen.h>

void wanbeiyu_touch_screen_set(wanbeiyu_state_t const *state) {
  wanbeiyu_touch_screen_state_t *touch_screen;
  assert(state != NULL);
  touch_screen = state->touch_screen;
  if (touch_screen == NULL) {
    wanbeiyu_hal_spst_switch_touch_screen_set(WANBEIYU_HAL_SPST_SWITCH_OPEN);
  } else {
    wanbeiyu_hal_rdac_touch_screen_pin_2_4_set(
        touch_screen->x < 320 ? touch_screen->x : 319);
    wanbeiyu_hal_rdac_touch_screen_pin_3_1_set(
        touch_screen->y < 240 ? touch_screen->y : 239);
    wanbeiyu_hal_spst_switch_touch_screen_set(WANBEIYU_HAL_SPST_SWITCH_CLOSE);
  }
}