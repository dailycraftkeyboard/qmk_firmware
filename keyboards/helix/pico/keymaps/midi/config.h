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

#ifdef RGB_MATRIX_ENABLE
    #define RGB_MATRIX_KEYPRESSES // reacts to keypresses

    // WS2812ドライバーの設定
    #define RGB_DI_PIN D3  // LEDのデータピン
    #define RGB_MATRIX_LED_COUNT 50
    #define RGB_MATRIX_SPLIT { 25, 25 }  // 左右それぞれのLED数
    //#define SPLIT_TRANSPORT_MIRROR  // 左右のLED状態を同期
    
    // 輝度設定
    #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 50  // 最大輝度（0-255）を50に下げる
    #define RGB_MATRIX_DEFAULT_VAL 50  // デフォルトの輝度
    //#define RGB_MATRIX_LIMIT_VAL 50  // 輝度の上限

    #define ENABLE_RGB_MATRIX_SOLID_REACTIVE
    
    // モード設定
    #define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SOLID_COLOR  // デフォルトのモード
    
    // エフェクトの選択
    #define ENABLE_RGB_MATRIX_SOLID_COLOR  // 単色モード
    #define ENABLE_RGB_MATRIX_ALPHAS_MODS  // アルファキーとモディファイアキーで異なる色
    #define ENABLE_RGB_MATRIX_BREATHING  // ブリージングエフェクト
    #define ENABLE_RGB_MATRIX_SOLID_REACTIVE  // キープレスに反応するエフェクト
    #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE  // シンプルなキープレス反応エフェクト

#endif

#define MIDI_ADVANCED
