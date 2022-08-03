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
  [_QWERTY] = LAYOUT_right_ball(
    KC_ESC   , KC_1     , KC_2     , KC_3     , KC_4     , KC_5     ,                                  KC_6     , KC_7     , KC_8     , KC_9     , KC_0     , KC_BSPC  ,
    KC_TAB   , KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                                  KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     , KC_MINS  ,
    KC_LCTL  , KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                                  KC_H     , KC_J     , KC_K     , KC_L     , KC_SCLN  , KC_QUOT  ,
    KC_LSFT  , KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     , KC_LGUI  ,              KC_RBRC, KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  , KC_EQL   ,
    KC_LALT  , KC_LGUI  , _______  , _______  , _______  , MO(_UTIL), KC_SPC   ,              KC_ENT , KC_DEL   ,                                  KC_GRV   , KC_BSLS 
  ),
    
  [_AUTO_MOUSE] = LAYOUT_right_ball(
    KC_ESC   , KC_1     , KC_2     , KC_3     , KC_4     , KC_5     ,                                  KC_6     , KC_7     , KC_8     , KC_9     , KC_0     , KC_BSPC  ,
    KC_TAB   , KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                                  KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     , KC_MINS  ,
    KC_LCTL  , KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                                  KC_H     , KC_J     , KC_K     , KC_L     , KC_SCLN  , KC_QUOT  ,
    KC_LSFT  , KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     , KC_LGUI  ,              KC_RBRC, KC_N     , KC_M     , KC_BTN1  , KC_BTN3  , KC_BTN2  , KC_EQL   ,
    KC_LALT  , KC_LGUI  , _______  , _______  , _______  , MO(_UTIL), KC_SPC   ,              KC_ENT , KC_DEL   ,                                  KC_GRV   , SCRL_MO
  ),

  [_UTIL] = LAYOUT_right_ball(
    _______  , KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_F5    ,                                  KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   , KC_F11   ,
    KC_TAB   , KC_Q     , S(KC_DEL), KC_W     , C(KC_K)  , _______  ,                                  _______  , KC_LBRC  , LSFT(KC_LBRC),LSFT(KC_RBRC),KC_RBRC,_______,
    _______  , KC_LEFT  , KC_DOWN  , KC_UP    , KC_RIGHT , _______  ,                                  KC_HOME  , KC_LEFT  , KC_DOWN  , KC_UP    , KC_RIGHT , KC_END   ,
    _______  , KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_F5    , _______  ,            _______  , _______  , KC_BTN4  , KC_BTN1  , KC_BTN3  , KC_BTN2  , KC_BTN5  ,
    _______  , _______  , _______  , _______  , _______  , _______  , _______  ,            _______  , _______  ,                                  _______  , _______
  ),

  [_PREF] = LAYOUT_right_ball(
    RGB_TOG  , _______  , _______  , _______  , _______  , _______  ,                                  RGB_M_P  , RGB_M_B  , RGB_M_R  , RGB_M_SW , RGB_M_SN , RGB_M_K  ,
    RGB_MOD  , RGB_HUI  , RGB_SAI  , RGB_VAI  , _______  , _______  ,                                  RGB_M_X  , RGB_M_G  , RGB_M_T  , RGB_M_TW , _______  , _______  ,
    RGB_RMOD , RGB_HUD  , RGB_SAD  , RGB_VAD  , _______  , _______  ,                                  CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  , KBC_SAVE , KBC_RST  ,
    _______  , _______  , SCRL_DVD , SCRL_DVI , SCRL_MO  , SCRL_TO  , EEP_RST  ,            EEP_RST  , KC_HOME  , KC_PGDN  , KC_PGUP  , KC_END   , _______  , _______  ,
    RESET    , _______  , _______  , _______  , _______  , KC_RGHT  , _______  ,            _______  , KC_BSPC  ,                                  _______  , RESET
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

void keyboard_post_init_user()
{
#ifdef RGBLIGHT_ENABLE
  // Force RGB lights to show test animation without writing EEPROM.
  rgblight_enable_noeeprom();
  rgblight_sethsv_noeeprom(100, 238, 120);
  // rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING);
#endif

#ifdef RGB_MATRIX_ENABLE
  rgb_matrix_sethsv_noeeprom(132, 250, 60);
  // rgb_matrix_mode_noeeprom(RGB_MATRIX_TYPING_HEATMAP);
  rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_MULTISPLASH);
#endif
}

#ifdef OLED_ENABLE

#include "lib/oledkit/oledkit.h"

static const char *format_4d(int8_t d)
{
  static char buf[5] = {0}; // max width (4) + NUL (1)
  char lead = ' ';
  if (d < 0)
  {
    d = -d;
    lead = '-';
  }
  buf[3] = (d % 10) + '0';
  d /= 10;
  if (d == 0)
  {
    buf[2] = lead;
    lead = ' ';
  }
  else
  {
    buf[2] = (d % 10) + '0';
    d /= 10;
  }
  if (d == 0)
  {
    buf[1] = lead;
    lead = ' ';
  }
  else
  {
    buf[1] = (d % 10) + '0';
    d /= 10;
  }
  buf[0] = lead;
  return buf;
}

/* KEYBOARD PET START */

/* settings */
#define MIN_WALK_SPEED 10
#define MIN_RUN_SPEED 40

/* advanced settings */
#define ANIM_FRAME_DURATION 200 // how long each frame lasts in ms
#define ANIM_SIZE 96            // number of bytes in array. If you change sprites, minimize for adequate firmware size. max is 1024

/* timers */
uint32_t anim_timer = 0;
uint32_t anim_sleep = 0;

/* current frame */
uint8_t current_frame = 0;

/* status variables */
int current_wpm = 0;
led_t led_usb_state;

bool isSneaking = false;
bool isJumping = false;
bool showedJump = true;

/* logic */
static void render_luna(int LUNA_X, int LUNA_Y) {
    /* Sit */
    static const char PROGMEM sit[2][ANIM_SIZE] = {/* 'sit1', 32x22px */
                                                   {
                                                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1c, 0x02, 0x05, 0x02, 0x24, 0x04, 0x04, 0x02, 0xa9, 0x1e, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x08, 0x68, 0x10, 0x08, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x06, 0x82, 0x7c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x0c, 0x10, 0x10, 0x20, 0x20, 0x20, 0x28, 0x3e, 0x1c, 0x20, 0x20, 0x3e, 0x0f, 0x11, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                   },

                                                   /* 'sit2', 32x22px */
                                                   {
                                                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1c, 0x02, 0x05, 0x02, 0x24, 0x04, 0x04, 0x02, 0xa9, 0x1e, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x90, 0x08, 0x18, 0x60, 0x10, 0x08, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x0e, 0x82, 0x7c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x0c, 0x10, 0x10, 0x20, 0x20, 0x20, 0x28, 0x3e, 0x1c, 0x20, 0x20, 0x3e, 0x0f, 0x11, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};

    /* Walk */
    static const char PROGMEM walk[2][ANIM_SIZE] = {/* 'walk1', 32x22px */
                                                    {
                                                        0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x10, 0x90, 0x90, 0x90, 0xa0, 0xc0, 0x80, 0x80, 0x80, 0x70, 0x08, 0x14, 0x08, 0x90, 0x10, 0x10, 0x08, 0xa4, 0x78, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0xfc, 0x01, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x18, 0xea, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1c, 0x20, 0x20, 0x3c, 0x0f, 0x11, 0x1f, 0x03, 0x06, 0x18, 0x20, 0x20, 0x3c, 0x0c, 0x12, 0x1e, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                    },

                                                    /* 'walk2', 32x22px */
                                                    {
                                                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x20, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x28, 0x10, 0x20, 0x20, 0x20, 0x10, 0x48, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x20, 0xf8, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x10, 0x30, 0xd5, 0x20, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x20, 0x30, 0x0c, 0x02, 0x05, 0x09, 0x12, 0x1e, 0x02, 0x1c, 0x14, 0x08, 0x10, 0x20, 0x2c, 0x32, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                    }};

    /* Run */
    static const char PROGMEM run[2][ANIM_SIZE] = {/* 'run1', 32x22px */
                                                   {
                                                        0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x08, 0x08, 0xc8, 0xb0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x40, 0x40, 0x3c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0xc4, 0xa4, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc8, 0x58, 0x28, 0x2a, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x09, 0x04, 0x04, 0x04, 0x04, 0x02, 0x03, 0x02, 0x01, 0x01, 0x02, 0x02, 0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                   },

                                                   /* 'run2', 32x22px */
                                                   {
                                                        0x00, 0x00, 0x00, 0xe0, 0x10, 0x10, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x78, 0x28, 0x08, 0x10, 0x20, 0x30, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x10, 0xb0, 0x50, 0x55, 0x20, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37, 0x02, 0x1e, 0x20, 0x20, 0x18, 0x0c, 0x14, 0x1e, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                   }};

    /* Bark */
    static const char PROGMEM bark[2][ANIM_SIZE] = {/* 'bark1', 32x22px */
                                                    {
                                                        0x00, 0xc0, 0x20, 0x10, 0xd0, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40, 0x3c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc8, 0x48, 0x28, 0x2a, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37, 0x02, 0x02, 0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                    },

                                                    /* 'bark2', 32x22px */
                                                    {
                                                        0x00, 0xe0, 0x10, 0x10, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40, 0x40, 0x2c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x48, 0x28, 0x2a, 0x10, 0x0f, 0x20, 0x4a, 0x09, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37, 0x02, 0x02, 0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                    }};

    /* Sneak */
    static const char PROGMEM sneak[2][ANIM_SIZE] = {/* 'sneak1', 32x22px */
                                                     {
                                                          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x40, 0x40, 0x80, 0x00, 0x80, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x21, 0xf0, 0x04, 0x02, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x04, 0x04, 0x04, 0x03, 0x01, 0x00, 0x00, 0x09, 0x01, 0x80, 0x80, 0xab, 0x04, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1c, 0x20, 0x20, 0x3c, 0x0f, 0x11, 0x1f, 0x02, 0x06, 0x18, 0x20, 0x20, 0x38, 0x08, 0x10, 0x18, 0x04, 0x04, 0x02, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00,
                                                     },

                                                     /* 'sneak2', 32x22px */
                                                     {
                                                          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xa0, 0x20, 0x40, 0x80, 0xc0, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x41, 0xf0, 0x04, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x02, 0x04, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x40, 0x40, 0x55, 0x82, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x20, 0x30, 0x0c, 0x02, 0x05, 0x09, 0x12, 0x1e, 0x04, 0x18, 0x10, 0x08, 0x10, 0x20, 0x28, 0x34, 0x06, 0x02, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                     }};
  /* animation */
  void animate_luna(void)
  {
    /* jump */
    if (isJumping || !showedJump)
    {
      /* clear */
      oled_set_cursor(LUNA_X, LUNA_Y + 2);
      oled_write("     ", false);

      oled_set_cursor(LUNA_X, LUNA_Y - 1);

      showedJump = true;
    }
    else
    {
      /* clear */
      oled_set_cursor(LUNA_X, LUNA_Y - 1);
      oled_write("     ", false);

      oled_set_cursor(LUNA_X, LUNA_Y);
    }

    /* switch frame */
    current_frame = (current_frame + 1) % 2;

    /* current status */
    if (led_usb_state.caps_lock)
    {
      oled_write_raw_P(bark[abs(1 - current_frame)], ANIM_SIZE);
    }
    else if (isSneaking)
    {
      oled_write_raw_P(sneak[abs(1 - current_frame)], ANIM_SIZE);
    }
    else if (current_wpm <= MIN_WALK_SPEED)
    {
      oled_write_raw_P(sit[abs(1 - current_frame)], ANIM_SIZE);
    }
    else if (current_wpm <= MIN_RUN_SPEED)
    {
      oled_write_raw_P(walk[abs(1 - current_frame)], ANIM_SIZE);
    }
    else
    {
      oled_write_raw_P(run[abs(1 - current_frame)], ANIM_SIZE);
    }
  }

  /* this fixes the screen on and off bug */
  if (current_wpm != 0)
  {
    oled_on();
    if (timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION)
    {
      anim_timer = timer_read32();
      animate_luna();
    }
    anim_sleep = timer_read32();
  }
  else
  {
    if (timer_elapsed32(anim_sleep) > OLED_TIMEOUT)
    {
      oled_off();
    }
    else
    {
      if (timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION)
      {
        anim_timer = timer_read32();
        animate_luna();
      }
    }
  }
}

static void print_status_narrow(void)
{
  /* Print current mode */
  oled_set_cursor(0, 0);

  switch (get_highest_layer(default_layer_state))
  {
  case _QWERTY:
    oled_write("QWRTY", false);
    break;
  case _AUTO_MOUSE:
    oled_write("MOUSE", false);
    break;
  case _UTIL:
    oled_write("UTIL", false);
    break;
  case _PREF:
    oled_write("PREF", false);
    break;
  default:
    oled_write("UNDEF", false);
  }

  oled_set_cursor(0, 2);

  /* Print current layer */
  oled_write("LAYER", false);

  oled_set_cursor(0, 3);

  switch (get_highest_layer(layer_state))
  {
  case _QWERTY:
    oled_write("Base  ", false);
    break;
  case _AUTO_MOUSE:
    oled_write("Mouse ", false);
    break;
  case _UTIL:
    oled_write("Util  ", false);
    break;
  case _PREF:
    oled_write("Pref  ", false);
    break;
  default:
    oled_write("Undef ", false);
  }

  oled_set_cursor(0, 5);

  oled_write_P(PSTR("CPI"), false);

  oled_set_cursor(0, 6);

  oled_write(format_4d(keyball_get_cpi()) + 1, false);
  oled_write_P(PSTR("00"), false);

  /* KEYBOARD PET RENDER START */

  render_luna(0, 13);

  /* KEYBOARD PET RENDER END */
}

/* KEYBOARD PET END */

oled_rotation_t oled_init_user(oled_rotation_t rotation)
{
  if (is_keyboard_master())
    return OLED_ROTATION_270;
  return rotation;
}

bool oled_task_user(void)
{
  /* KEYBOARD PET VARIABLES START */

  current_wpm = get_current_wpm();
  led_usb_state = host_keyboard_led_state();

  /* KEYBOARD PET VARIABLES END */

  if (is_keyboard_master())
  {
    print_status_narrow();
    // keyball_oled_render_keyinfo();
    // keyball_oled_render_ballinfo();
  }
  else
  {
    oledkit_render_logo_user();
  }

  return false;
}

/*
void oledkit_render_info_user(void)
{
  keyball_oled_render_keyinfo();
  keyball_oled_render_ballinfo();
}
*/
#endif

bool isAlt = false;

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

  
  /* ALT + TAB */

  if (layer_state_is(_UTIL))
  {
    if(keycode == KC_TAB && record->event.pressed) 
    {
      isAlt = true;
      register_mods(MOD_MASK_ALT);
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

  case KC_N:
    if (get_mods() & MOD_MASK_GUI)
    {
      if (record->event.pressed)
      {
        tap_code(KC_9);
      }
      return false;
    }
  break;

  /* KEYBOARD PET STATUS START */

  case KC_LCTL:
  case KC_RCTL:
    if (record->event.pressed)
    {
      isSneaking = true;
    }
    else
    {
      isSneaking = false;
    }
    break;
  case KC_SPC:
    if (record->event.pressed)
    {
      isJumping = true;
      showedJump = false;
    }
    else
    {
      isJumping = false;
    }
    break;

    /* KEYBOARD PET STATUS END */

  default:
    break;
  }

  anim_sleep = timer_read32();

  return true;
}

layer_state_t layer_state_set_user(layer_state_t state){
    switch (state){
    case _UTIL:
        break;
    default:
        if(isAlt){
          unregister_mods(MOD_MASK_ALT);
          isAlt = false;
        }
        break;
    }
    return state;
}