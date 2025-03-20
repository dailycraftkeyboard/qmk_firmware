/*
This is the c configuration file for the keymap

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

#pragma once

// place overrides here
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_TRANSPORT_MIRROR

#ifdef RGB_MATRIX_ENABLE
    // WS2812ドライバーの設定
    #define RGB_DI_PIN D3  // LEDのデータピン
    #define RGB_MATRIX_LED_COUNT 50
    //#define RGB_MATRIX_SPLIT { 25, 25 }  // 左右それぞれのLED数
    //#define SPLIT_TRANSPORT_MIRROR  // 左右のLED状態を同期
    
    // 輝度設定
    #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150  // 最大輝度（0-255）を150に設定
    #define RGB_MATRIX_DEFAULT_VAL 150  // デフォルトの輝度
    //#define RGB_MATRIX_LIMIT_VAL 150  // 輝度の上限

    // モード設定
    #define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_CUSTOM_pad64_effect

    // 色の定義
    #define C_NOTE_COLOR_R 95  // Cノートの赤成分
    #define C_NOTE_COLOR_G 0   // Cノートの緑成分
    #define C_NOTE_COLOR_B 127 // Cノートの青成分

    #define SCALE_COLOR_R 0  // スケールノートの赤成分
    #define SCALE_COLOR_G 0  // スケールノートの緑成分
    #define SCALE_COLOR_B 255  // スケールノートの青成分

    #define PRESSED_COLOR_R 0  // 押されたキーの赤成分
    #define PRESSED_COLOR_G 127 // 押されたキーの緑成分
    #define PRESSED_COLOR_B 0  // 押されたキーの青成分

#endif


#define MIDI_ADVANCED

#define DEBUG_ENABLE