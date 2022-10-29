/*
This is the c configuration file for the keymap

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

#pragma once

#ifdef RGBLIGHT_ENABLE
// #define RGBLIGHT_EFFECT_BREATHING
// #define RGBLIGHT_EFFECT_RAINBOW_MOOD
// #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
// #define RGBLIGHT_EFFECT_SNAKE
// #define RGBLIGHT_EFFECT_KNIGHT
// #define RGBLIGHT_EFFECT_CHRISTMAS
// #define RGBLIGHT_EFFECT_STATIC_GRADIENT
// #define RGBLIGHT_EFFECT_RGB_TEST
// #define RGBLIGHT_EFFECT_ALTERNATING
// #define RGBLIGHT_EFFECT_TWINKLE
#endif

#ifdef RGB_MATRIX_ENABLE
// #define RIGHT_BALL
// #define LEFT_BALL
#define DUAL_BALL
// #define NO_BALL
#ifdef RIGHT_BALL
#define RGB_MATRIX_SPLIT \
    {                    \
        37, 34           \
    }
#define DRIVER_LED_TOTAL 71
#endif
#ifdef LEFT_BALL
#define RGB_MATRIX_SPLIT \
    {                    \
        34, 37           \
    }
#define DRIVER_LED_TOTAL 71
#endif
#ifdef DUAL_BALL
#define RGB_MATRIX_SPLIT \
    {                    \
        34, 34           \
    }
#define DRIVER_LED_TOTAL 71
#endif
#ifdef NO_BALL
#define RGB_MATRIX_SPLIT \
    {                    \
        37, 37           \
    }
#define DRIVER_LED_TOTAL 74
#endif

//#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
//#define ENABLE_RGB_MATRIX_TYPING_HEATMAP
// #    define ENABLE_RGB_MATRIX_DIGITAL_RAIN

#define RGB_MATRIX_KEYPRESSES
// #    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
// #    define ENABLE_RGB_MATRIX_SOLID_REACTIVE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
// #    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
// #    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
// #    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
// #    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
// #    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
// #    define ENABLE_RGB_MATRIX_SPLASH
// #define ENABLE_RGB_MATRIX_MULTISPLASH
// #define ENABLE_RGB_MATRIX_SOLID_SPLASH
#define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH

// https://github.com/qmk/qmk_firmware/blob/5a727dbc6dc51b2d7d90e5d2a7e99ca3435153be/docs/feature_rgb_matrix.md
#define SPLIT_LAYER_STATE_ENABLE

#endif
