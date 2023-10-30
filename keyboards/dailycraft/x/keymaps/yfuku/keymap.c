// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "yfuku_keymaps.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum layer_number {
    _QWERTY = 0,
    _RAISE,
    _LOWER,
    _ADJUST,
};

#define TAPPING_LAYER_TERM 230
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case GS_S:
      return TAPPING_LAYER_TERM;
    case GS_L:
      return TAPPING_LAYER_TERM;
    case A_D:
      return TAPPING_LAYER_TERM;
    case A_K:
      return TAPPING_LAYER_TERM;
    default:
      return TAPPING_TERM;
  }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_wrapper(
       __QWERTY_L1__,                __QWERTY_R1__,
       __QWERTY_L2__,  KC_NO,        __QWERTY_R2__,
       __QWERTY_L3__,  KC_NO, KC_NO, __QWERTY_R3__,
       __QUERTY_T3__
    ),

    [_RAISE] = LAYOUT_wrapper(
       __RAISE_L1__,              __RAISE_R1__,
       __RAISE_L2__,  ____,       __RAISE_R2__,
       __RAISE_L3__,  ____, ____, __RAISE_R3__,
       __RAISE_T3__
    ),

    [_LOWER] = LAYOUT_wrapper(
       __LOWER_L1__,              __LOWER_R1__,
       __LOWER_L2__,  ____,       __LOWER_R2__,
       __LOWER_L3__,  ____, ____, __LOWER_R3__,
       __LOWER_T3__
    ),

    [_ADJUST] = LAYOUT_wrapper(
       __TRANSx6__,              __TRANSx6__,
       __TRANSx6__, ____       , __TRANSx6__,
       __TRANSx6__, __TRANSx2__, __TRANSx6__,
       __TRANSx3__, __TRANSx3__
    ),
};
