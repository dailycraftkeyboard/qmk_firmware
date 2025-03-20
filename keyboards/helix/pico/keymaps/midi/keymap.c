/* Copyright 2018 MakotoKurauchi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <stdio.h>
#include QMK_KEYBOARD_H
#include "rgb_matrix.h"

// 外部関数のプロトタイプ宣言（rgb_matrix_user.incで定義）
#ifdef RGB_MATRIX_ENABLE
// rgb_matrix_user.incで定義される関数のプロトタイプ
void set_key_pressed(uint8_t led_idx, bool pressed);
void set_original_color(uint8_t led_idx, uint8_t r, uint8_t g, uint8_t b);
#endif

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
    _QWERTY = 0,
    _ADJUST
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  ADJUST,
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

//Macros
#define M_SAMPLE M(KC_SAMPLEMACRO)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT(
      MI_F1,   MI_Fs1,  MI_G1,   MI_Gs1,  MI_A1,   MI_As1,                     MI_Cs3,  MI_D3,   MI_Ds3,  MI_E3,   MI_F3,   MI_Fs3,
      MI_C1,   MI_Cs1,  MI_D1,   MI_Ds1,  MI_E1,   MI_F1,                      MI_Gs2,  MI_A2,   MI_As2,  MI_B2,   MI_C3,   MI_Cs3,
      MI_G,    MI_Gs,   MI_A,    MI_As,   MI_B,    MI_C1,                       MI_Ds2,  MI_E2,   MI_F2,  MI_Fs2,  MI_G2,   MI_Gs2,
      MI_D,    MI_Ds,   MI_E,    MI_F,    MI_Fs,   MI_G,    MO(_ADJUST), MO(ADJUST),  MI_As1,  MI_B1,   MI_C2,   MI_Cs2,  MI_D2,   MI_Ds2
      ),

  [_ADJUST] =  LAYOUT(
      RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, _______, _______,                  _______, _______, _______, _______, _______, _______,
      RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, _______, _______,                  _______, _______, _______, _______, _______, _______,
      RGB_RMOD, RGB_MOD, _______, _______, _______, _______,                  _______, _______, _______, _______, _______, _______,
      RGB_TOG, RGB_MOD, RGB_RMOD, _______, _______, QK_BOOTLOADER, _______, _______, _______, _______, _______, _______, _______, _______
      )
};

#ifdef RGB_MATRIX_ENABLE
// キーとLEDの対応関係を定義
led_config_t g_led_config = {
    // キーマトリックスからLEDインデックスへのマッピング
    {
        // 左側のキーボード
        { 5,  4,  3,  2,  1,  0 , NO_LED},
        { 6, 7,  8,  9,  10, 11 , NO_LED},
        { 17, 16, 15, 14, 13, 12 , NO_LED},
        { 18, 19, 20, 21, 22, 23 , 24},
        // 右側のキーボード
        { 30, 29, 28, 27, 26, 25, NO_LED},
        { 31, 32, 33, 34, 35, 36, NO_LED},
        { 42, 41, 40, 39, 38, 37, NO_LED},
        { 43, 44, 45, 46, 47, 48, 49 }
    },
    // LEDの物理的な位置
    {
        // 左側のキーボード
        { 0,  0 }, { 20,  0 }, { 40,  0 }, { 60,  0 }, { 80,  0 }, { 100,  0 },
        { 0, 16 }, { 20, 16 }, { 40, 16 }, { 60, 16 }, { 80, 16 }, { 100, 16 },
        { 0, 32 }, { 20, 32 }, { 40, 32 }, { 60, 32 }, { 80, 32 }, { 100, 32 },
        { 0, 48 }, { 20, 48 }, { 40, 48 }, { 60, 48 }, { 80, 48 }, { 100, 48 }, { 120, 48 },
        // 右側のキーボード
        { 124,  0 }, { 144,  0 }, { 164,  0 }, { 184,  0 }, { 204,  0 }, { 224,  0 },
        { 124, 16 }, { 144, 16 }, { 164, 16 }, { 184, 16 }, { 204, 16 }, { 224, 16 },
        { 124, 32 }, { 144, 32 }, { 164, 32 }, { 184, 32 }, { 204, 32 }, { 224, 32 },
        { 104, 48 }, { 124, 48 }, { 144, 48 }, { 164, 48 }, { 184, 48 }, { 204, 48 }, { 224, 48 }
    },
    // LEDのタイプ（キーライト、アンダーグロー等）
    {
        // すべてのLEDをキーライトとして設定
        4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4
    }
};
#endif

// MIDIノートとLEDインデックスのマッピング
typedef struct {
    uint16_t note;    // MIDIノート番号（uint16_tに変更）
    uint8_t led_idx;  // LEDインデックス
} midi_led_map_t;

// キーマップからMIDIノートとLEDインデックスのマッピングを作成
const midi_led_map_t midi_led_map[] = {
    // 左側のキーボード
    {MI_D,    18}, {MI_Ds,   19}, {MI_E,    20}, {MI_F,    21}, {MI_Fs,   22}, {MI_G,    23},
    {MI_G,    12}, {MI_Gs,   13}, {MI_A,    14}, {MI_As,   15}, {MI_B,    16}, {MI_C1,   17},
    {MI_C1,    6}, {MI_Cs1,   7}, {MI_D1,    8}, {MI_Ds1,   9}, {MI_E1,   10}, {MI_F1,   11},
    {MI_F1,    0}, {MI_Fs1,   1}, {MI_G1,    2}, {MI_Gs1,   3}, {MI_A1,    4}, {MI_As1,   5},
    
    // 右側のキーボード
    {MI_Cs3,  25}, {MI_D3,   26}, {MI_Ds3,  27}, {MI_E3,   28}, {MI_F3,   29}, {MI_Fs3,  30},
    {MI_Gs2,  31}, {MI_A2,   32}, {MI_As2,  33}, {MI_B2,   34}, {MI_C3,   35}, {MI_Cs3,  36},
    {MI_Ds2,  37}, {MI_E2,   38}, {MI_F2,   39}, {MI_Fs2,  40}, {MI_G2,   41}, {MI_Gs2,  42},
    {MI_As1,  43}, {MI_B1,   44}, {MI_C2,   45}, {MI_Cs2,  46}, {MI_D2,   47}, {MI_Ds2,  48}
};

// MIDIノートからLEDインデックスを取得する関数
uint8_t get_led_index_from_midi_note(uint16_t note) {
    for (uint8_t i = 0; i < sizeof(midi_led_map) / sizeof(midi_led_map_t); i++) {
        if (midi_led_map[i].note == note) {
            return midi_led_map[i].led_idx;
        }
    }
    return 255; // 見つからない場合は255を返す
}

// MIDIノートの値を取得する関数
uint8_t get_midi_note_value(uint16_t note) {
    // MIDIノートの値を取得（MI_Cは0、MI_Csは1、MI_Dは2、...）
    if (note >= MI_C && note <= MI_Ds5) {
        return (note - MI_C) % 12;
    }
    return 255; // 無効な値
}

// MIDIノートがCかどうかをチェックする関数
bool is_c_note(uint16_t note) {
    // C, C1, C2, C3, ...
    return get_midi_note_value(note) == 0;
}

// MIDIノートがCメジャースケール（C, D, E, F, G, A, B）に含まれるかチェックする関数
bool is_c_major_scale(uint16_t note) {
    uint8_t note_value = get_midi_note_value(note);
    return note_value == 0 || // C
           note_value == 2 || // D
           note_value == 4 || // E
           note_value == 5 || // F
           note_value == 7 || // G
           note_value == 9 || // A
           note_value == 11;  // B
}

// すべてのLEDの色を初期化する関数
void initialize_led_colors(void) {
    // まず、すべてのLEDを消灯に初期化
    for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        set_original_color(i, 0, 0, 0);
    }
    
    // キーマップをスキャンして、MIDIキーのLEDの色を設定
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            uint8_t led_idx = g_led_config.matrix_co[row][col];
            
            // 有効なLEDインデックスの場合のみ処理
            if (led_idx != NO_LED) {
                // キーマップからキーコードを取得
                uint16_t keycode = pgm_read_word(&keymaps[0][row][col]);
                
                // MIDIノートキーコードの場合のみ処理
                if (keycode >= MI_C && keycode <= MI_Ds5) {
                    // Cノートは紫色
                    if (is_c_note(keycode)) {
                        set_original_color(led_idx, C_NOTE_COLOR_R, C_NOTE_COLOR_G, C_NOTE_COLOR_B);
                    }
                    // Cメジャースケール（C以外）は青色
                    else if (is_c_major_scale(keycode)) {
                        set_original_color(led_idx, SCALE_COLOR_R, SCALE_COLOR_G, SCALE_COLOR_B);
                    }
                    // その他のノートは消灯 (0, 0, 0)
                    else {
                        set_original_color(led_idx, 0, 0, 0);
                    }
                }
                // MIDIノートキーコード以外は消灯
                else {
                    set_original_color(led_idx, 0, 0, 0);
                }
            }
        }
    }
}

// キーボード初期化時の処理
void keyboard_post_init_user(void) {
    debug_enable = true;
    
    #ifdef RGB_MATRIX_ENABLE
    rgb_matrix_enable();
    // pad64_effectモードを設定
    rgb_matrix_mode(RGB_MATRIX_CUSTOM_pad64_effect);
    initialize_led_colors();
    #endif
}

// キー入力処理
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    #ifdef RGB_MATRIX_ENABLE
    // MIDIノートキーコードの場合
    if (keycode >= MI_C && keycode <= MI_Ds5) {
        uint8_t row = record->event.key.row;
        uint8_t col = record->event.key.col;
        uint8_t led_idx = g_led_config.matrix_co[row][col];
        
        if (led_idx != NO_LED) {
            if (record->event.pressed) {
                // キーが押された時
                set_key_pressed(led_idx, true);
                dprintf("key pressed led_idx: %d\n", led_idx);
                
                // 同じオクターブ内の同じノートのLEDも緑色に設定
                uint8_t note_value = get_midi_note_value(keycode);
                uint8_t octave = (keycode - MI_C) / 12;
                
                // 他のキーをスキャンして、同じオクターブ内の同じノートを探す
                for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
                    for (uint8_t c = 0; c < MATRIX_COLS; c++) {
                        if (r == row && c == col) continue; // 自分自身はスキップ
                        
                        uint8_t other_led_idx = g_led_config.matrix_co[r][c];
                        if (other_led_idx == NO_LED) continue;
                        
                        uint16_t other_keycode = pgm_read_word(&keymaps[0][r][c]);
                        if (other_keycode >= MI_C && other_keycode <= MI_Ds5) {
                            if (get_midi_note_value(other_keycode) == note_value &&
                                (other_keycode - MI_C) / 12 == octave) {
                                set_key_pressed(other_led_idx, true);
                            }
                        }
                    }
                }
            } else {
                // キーが離された時
                set_key_pressed(led_idx, false);
                
                // 同じオクターブ内の同じノートのLEDも元の色に戻す
                uint8_t note_value = get_midi_note_value(keycode);
                uint8_t octave = (keycode - MI_C) / 12;
                
                // 他のキーをスキャンして、同じオクターブ内の同じノートを探す
                for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
                    for (uint8_t c = 0; c < MATRIX_COLS; c++) {
                        if (r == row && c == col) continue; // 自分自身はスキップ
                        
                        uint8_t other_led_idx = g_led_config.matrix_co[r][c];
                        if (other_led_idx == NO_LED) continue;
                        
                        uint16_t other_keycode = pgm_read_word(&keymaps[0][r][c]);
                        if (other_keycode >= MI_C && other_keycode <= MI_Ds5) {
                            if (get_midi_note_value(other_keycode) == note_value &&
                                (other_keycode - MI_C) / 12 == octave) {
                                set_key_pressed(other_led_idx, false);
                            }
                        }
                    }
                }
            }
        }
    }
    #endif
    
    return true;
}