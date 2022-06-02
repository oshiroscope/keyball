/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#include "quantum.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_universal(
    KC_ESC   , KC_1     , KC_2     , KC_3     , KC_4     , KC_5     ,                                  KC_6     , KC_7     , KC_8     , KC_9     , KC_0     , KC_BSPC  ,
    KC_TAB   , KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                                  KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     , KC_MINS  ,
    KC_LCTL  , KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                                  KC_H     , KC_J     , KC_K     , KC_L     , KC_SCLN  , KC_QUOT  ,
    KC_LSFT  , KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     , KC_LBRC  ,              KC_RBRC, KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  , KC_GRV   ,
    _______  , _______  , KC_TAB   , LT(2,KC_LGUI),KC_LALT,MO(1)    , LT(3,KC_SPC),           KC_ENT , KC_BSPC  , _______  , _______  , _______  , KC_EQL   , KC_DEL
  ),

  [1] = LAYOUT_universal(
    _______  , KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_F5    ,                                  KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   , KC_F11   ,
    _______  , KC_Q     , S(KC_DEL), KC_W     , C(KC_K)  , _______  ,                                  _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , KC_LEFT  , KC_DOWN  , KC_UP    , KC_RIGHT , _______  ,                                  KC_HOME  , KC_LEFT  , KC_DOWN  , KC_UP    , KC_RIGHT , KC_END   ,
    _______  , KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_F5    , _______  ,            _______  , _______  , KC_BTN4  , KC_BTN1  , KC_BTN3  , KC_BTN2  , KC_BTN5  ,
    _______  , _______  , _______  , _______  , _______  , _______  , _______  ,            _______  , _______  , _______  , _______  , _______  , _______  , _______
  ),

  [2] = LAYOUT_universal(
    _______  ,LCTL(LGUI(KC_1)),LCTL(LGUI(KC_2)),LCTL(LGUI(KC_3)),LCTL(LGUI(KC_4)),LCTL(LGUI(KC_5)),LCTL(LGUI(KC_6)),LCTL(LGUI(KC_7)),LCTL(LGUI(KC_8)),LCTL(LGUI(KC_9)),_______,_______,
    LGUI(KC_TAB),_______, _______  , _______  , _______  , _______  ,                                  _______  , _______  , _______  , _______  , _______  , _______  ,
    KC_LCTRL , _______  , LSFT(LGUI(KC_S)),_______,_______,_______  ,                                  _______  , LGUI(KC_LEFT),LGUI(KC_DOWN),LGUI(KC_UP),LGUI(KC_RIGHT),_______,
    _______  , _______  , _______  , _______  , LGUI(KC_V),_______  , _______  ,            _______  , _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  , _______  ,             KC_DEL  , _______  , _______  , _______  , _______  , _______  , _______
  ),

  [3] = LAYOUT_universal(
    RGB_TOG  , _______  , _______  , _______  , _______  , _______  ,                                  RGB_M_P  , RGB_M_B  , RGB_M_R  , RGB_M_SW , RGB_M_SN , RGB_M_K  ,
    RGB_MOD  , RGB_HUI  , RGB_SAI  , RGB_VAI  , _______  , _______  ,                                  RGB_M_X  , RGB_M_G  , RGB_M_T  , RGB_M_TW , _______  , _______  ,
    RGB_RMOD , RGB_HUD  , RGB_SAD  , RGB_VAD  , _______  , _______  ,                                  CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  , KBC_SAVE , KBC_RST  ,
    _______  , _______  , SCRL_DVD , SCRL_DVI , SCRL_MO  , SCRL_TO  , EEP_RST  ,            EEP_RST  , KC_HOME  , KC_PGDN  , KC_PGUP  , KC_END   , _______  , _______  ,
    RESET    , _______  , KC_LEFT  , KC_DOWN  , KC_UP    , KC_RGHT  , _______  ,            _______  , KC_BSPC  , _______  , _______  , _______  , _______  , RESET
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state)
{
  // Auto enable scroll mode when the highest layer is 3
  keyball_set_scroll_mode(get_highest_layer(state) == 3);
  return state;
}

static bool mouse_on = false;

report_mouse_t pointing_device_task_user(report_mouse_t report)
{
  if (report.x > 2 || report.x < -2 || report.y > 2 || report.y < -2)
  {
    mouse_on = true;
  }

  return report;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
  report_mouse_t currentReport;
  switch (keycode)
  {
  case KC_COMMA:
    if (!mouse_on)
      return true;
    currentReport = pointing_device_get_report();
    if (record->event.pressed)
      currentReport.buttons |= MOUSE_BTN1;
    else
      currentReport.buttons &= ~MOUSE_BTN1;
    pointing_device_set_report(currentReport);
    return false;

  case KC_DOT:
    if (!mouse_on)
      return true;
    currentReport = pointing_device_get_report();
    if (record->event.pressed)
      currentReport.buttons |= MOUSE_BTN3;
    else
      currentReport.buttons &= ~MOUSE_BTN3;
    pointing_device_set_report(currentReport);
    return false;

  case KC_SLASH:
    if (!mouse_on)
      return true;
    currentReport = pointing_device_get_report();
    if (record->event.pressed)
      currentReport.buttons |= MOUSE_BTN2;
    else
      currentReport.buttons &= ~MOUSE_BTN2;
    pointing_device_set_report(currentReport);
    return false;

  default:
    if (record->event.pressed)
      mouse_on = false;
    break;
  }
  // switch (keycode) {
  //     case KC_BTN1:
  //         if (record->event.pressed && IS_LAYER_ON(2)) {
  //             mouse_on = off;
  //         }
  //         break;

  //     default:
  //         break;
  // }
  return true;
}

#ifdef OLED_ENABLE

#include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void)
{
  keyball_oled_render_keyinfo();
  keyball_oled_render_ballinfo();
}
#endif
