/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert
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
#include "yfuku_keymaps.h"

enum layer_number {
    _QWERTY = 0,
    _RAISE,
    _LOWER,
    _ADJUST,
};

#define TAPPING_LAYER_TERM 500
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case CS_TAB:
    case AS_A:
    case GS_S:
    case A_D:
    case G_F:
    case C_G:
    case C_H:
    case G_J:
    case A_K:
    case GS_L:
    case AS_SCLN:
    case CS_ESC:
      return TAPPING_LAYER_TERM;

    default:
      return TAPPING_TERM;
  }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_wrapper(
       __QWERTY_L1__,  __QWERTY_R1__,
       __QWERTY_L2__,  __QWERTY_R2__,
       __QWERTY_L3__,  __QWERTY_R3__,
       __QUERTY_T3__,
       KC_NO, KC_NO, KC_NO
    ),

    [_RAISE] = LAYOUT_wrapper(
       __RAISE_L1__,  __RAISE_R1__,
       __RAISE_L2__,  __RAISE_R2__,
       __RAISE_L3__,  __RAISE_R3__,
       __RAISE_T3__,
       ____, ____, ____
    ),

    [_LOWER] = LAYOUT_wrapper(
       __LOWER_L1__,  __LOWER_R1__,
       __LOWER_L2__,  __LOWER_R2__,
       __LOWER_L3__,  __LOWER_R3__,
       __LOWER_T3__,
       ____, ____, ____
    ),

    [_ADJUST] = LAYOUT_wrapper(
       __TRANSx6__,  __TRANSx6__,
       __TRANSx6__,  __TRANSx6__,
       __TRANSx6__,  __TRANSx6__,
       __TRANSx3__, __TRANSx3__,
       ____, ____, ____
    ),
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] =   { ENCODER_CCW_CW(KC_NO, KC_NO), ENCODER_CCW_CW(KC_NO, KC_NO), ENCODER_CCW_CW(KC_NO, KC_NO) },
    [1] =   { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
    [2] =   { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
    [3] =   { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) }
};
#endif
