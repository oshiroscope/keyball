/*
Copyright 2022 @kazme-egawa
Copyright 2022 KAZME EGAWA

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

#define _QWERTY 0
#define _AUTO_MOUSE 1
#define _UTIL 2
#define _PREF 3

#include QMK_KEYBOARD_H
#include "quantum.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_sphere_twins(
    KC_ESC   , KC_1     , KC_2     , KC_3     , KC_4     , KC_5     ,                                  KC_6     , KC_7     , KC_8     , KC_9     , KC_0     , KC_BSPC  ,
    KC_TAB   , KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                                  KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     , KC_MINS  ,
    KC_LCTL  , KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                                  KC_H     , KC_J     , KC_K     , KC_L     , KC_SCLN  , KC_QUOT  ,
    KC_LSFT  , KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     , KC_LGUI  ,              KC_RBRC, KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  , KC_EQL   ,
    KC_LALT  , KC_LGUI  ,                                  MO(_UTIL), KC_SPC   ,              KC_ENT , KC_DEL   ,                                  KC_GRV   , KC_BSLS 
  ),
    
  [_AUTO_MOUSE] = LAYOUT_sphere_twins(
    KC_ESC   , KC_1     , KC_2     , KC_3     , KC_4     , KC_5     ,                                  KC_6     , KC_7     , KC_8     , KC_9     , KC_0     , KC_BSPC  ,
    KC_TAB   , KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                                  KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     , KC_MINS  ,
    KC_LCTL  , KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                                  KC_H     , KC_J     , KC_K     , KC_L     , KC_SCLN  , KC_QUOT  ,
    KC_LSFT  , KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     , KC_LGUI  ,              KC_RBRC, KC_N     , KC_M     , KC_BTN1  , KC_BTN3  , KC_BTN2  , KC_EQL   ,
    KC_LALT  , KC_LGUI  ,                                  MO(_UTIL), KC_SPC   ,              KC_ENT , KC_DEL   ,                                  KC_GRV   , SCRL_MO
  ),

  [_UTIL] = LAYOUT_sphere_twins(
    _______  , KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_F5    ,                                  KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   , KC_F11   ,
    _______  , KC_Q     , S(KC_DEL), KC_W     , C(KC_K)  , _______  ,                                  _______  , KC_LBRC  , LSFT(KC_LBRC),LSFT(KC_RBRC),KC_RBRC,_______,
    _______  , KC_LEFT  , KC_DOWN  , KC_UP    , KC_RIGHT , _______  ,                                  KC_HOME  , KC_LEFT  , KC_DOWN  , KC_UP    , KC_RIGHT , KC_END   ,
    _______  , KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_F5    , _______  ,            _______  , _______  , KC_BTN4  , KC_BTN1  , KC_BTN3  , KC_BTN2  , KC_BTN5  ,
    _______  , _______  ,                                  _______  , _______  ,            _______  , _______  ,                                  _______  , _______
  ),

  [_PREF] = LAYOUT_sphere_twins(
    RGB_TOG  , _______  , _______  , _______  , _______  , _______  ,                                  RGB_M_P  , RGB_M_B  , RGB_M_R  , RGB_M_SW , RGB_M_SN , RGB_M_K  ,
    RGB_MOD  , RGB_HUI  , RGB_SAI  , RGB_VAI  , _______  , _______  ,                                  RGB_M_X  , RGB_M_G  , RGB_M_T  , RGB_M_TW , _______  , _______  ,
    RGB_RMOD , RGB_HUD  , RGB_SAD  , RGB_VAD  , _______  , _______  ,                                  CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  , KBC_SAVE , KBC_RST  ,
    _______  , _______  , SCRL_DVD , SCRL_DVI , SCRL_MO  , SCRL_TO  , EEP_RST  ,            EEP_RST  , KC_HOME  , KC_PGDN  , KC_PGUP  , KC_END   , _______  , _______  ,
    RESET    , _______  ,                                  KC_RGHT  , _______  ,            _______  , KC_BSPC  ,                                  _______  , RESET
  ),
};
// clang-format on

report_mouse_t pointing_device_task_user(report_mouse_t report)
{
  if (report.x > 2 || report.x < -2 || report.y > 2 || report.y < -2)
  {
    layer_on(_AUTO_MOUSE);
  }

  return report;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{

  if (layer_state_is(_AUTO_MOUSE) && record->event.pressed)
  {
    switch (keycode)
    {
    // escape mouse btns
    case KC_BTN1:
    case KC_BTN2:
    case KC_BTN3:
    case SCRL_MO:
      break;

    // escape modifier keys
    case KC_LCTL:
    case KC_LSFT:
    case KC_LALT:
    case KC_LGUI:
      break;

    default:
      layer_off(_AUTO_MOUSE);
      break;
    }
  }

  switch (keycode)
  {
  case KC_J:
    if (get_mods() & MOD_MASK_GUI)
    {
      if (record->event.pressed)
      {
        tap_code(KC_LEFT);
      }
      return false;
    }
    break;

  case KC_K:
    if (get_mods() & MOD_MASK_GUI)
    {
      if (record->event.pressed)
      {
        tap_code(KC_DOWN);
      }
      return false;
    }
    break;

  case KC_L:
    if (get_mods() & MOD_MASK_GUI)
    {
      if (record->event.pressed)
      {
        tap_code(KC_UP);
      }
      return false;
    }
    break;

  case KC_SCLN:
    if (get_mods() & MOD_MASK_GUI)
    {
      if (record->event.pressed)
      {
        tap_code(KC_RIGHT);
      }
      return false;
    }
    break;

  case KC_P:
    if (get_mods() & MOD_MASK_GUI)
    {
      if (record->event.pressed)
      {
        tap_code(KC_6);
      }
      return false;
    }
    break;

  case KC_D:
    if (get_mods() & MOD_MASK_GUI)
    {
      if (record->event.pressed)
      {
        tap_code(KC_5);
      }
      return false;
    }
    break;

  default:
    break;
  }

  return true;
}

void keyboard_post_init_user()
{
#ifdef RGBLIGHT_ENABLE
  // Force RGB lights to show test animation without writing EEPROM.
  rgblight_enable_noeeprom();
  rgblight_sethsv_noeeprom(100, 238, 120);
  // rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING);
#endif
}

#ifdef OLED_ENABLE

#include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void)
{
  keyball_oled_render_keyinfo();
  keyball_oled_render_ballinfo();
}
#endif
