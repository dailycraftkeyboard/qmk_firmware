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
#include QMK_KEYBOARD_H
#include "rgb_matrix.h"

// RGB Matrixの設定
#ifdef RGB_MATRIX_ENABLE
// デバッグモード用の変数
bool debug_mode = false;
uint8_t debug_led_index = 0;
uint8_t debug_mode_type = 0; // 0: オフ, 1: LEDインデックス, 2: MIDIノート, 3: カラー設定, 4: 全て赤色

// Cキーのインデックス
const uint8_t c_key_indices[] = {17, 35, 45};

// Cメジャースケールのキーのインデックス（C以外）
const uint8_t c_major_scale_indices[] = {
    // D, E, F, G, A, B
    8, 20, 21, 2, 14, 16,  // 左側
    26, 28, 29, 41, 32, 34 // 右側
};
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
      RGB_TOG, RGB_MOD, RGB_RMOD, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
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

/*

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

// キーの元の色を保存する配列
uint8_t original_colors[RGB_MATRIX_LED_COUNT][3];

// キーが押されているかどうかを記録する配列
bool key_pressed[RGB_MATRIX_LED_COUNT] = {false};

// LEDインデックスを順番に点灯させる関数
void debug_show_led_indices(void) {
    debug_mode = true;
    debug_mode_type = 1;
    debug_led_index = 0;
    
    // すべてのLEDを消灯
    for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        rgb_matrix_set_color(i, 0, 0, 0);
    }
}

// MIDIノートとLEDインデックスの対応を確認する関数
void debug_show_midi_note_mapping(void) {
    debug_mode = true;
    debug_mode_type = 2;
    
    // すべてのLEDを消灯
    for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        rgb_matrix_set_color(i, 0, 0, 0);
    }
    
    // MIDIノートに対応するLEDを点灯
    for (uint8_t i = 0; i < sizeof(midi_led_map) / sizeof(midi_led_map_t); i++) {
        uint16_t note = midi_led_map[i].note;
        uint8_t led_idx = midi_led_map[i].led_idx;
        
        // Cノートは紫色
        if (is_c_note(note)) {
            rgb_matrix_set_color(led_idx, 191, 0, 255);
        }
        // Cメジャースケールは青色
        else if (is_c_major_scale(note)) {
            rgb_matrix_set_color(led_idx, 0, 0, 255);
        }
        // その他のノートは白色
        else {
            rgb_matrix_set_color(led_idx, 127, 127, 127);
        }
    }
}

// カラー設定を確認する関数
void debug_show_color_settings(void) {
    debug_mode = true;
    debug_mode_type = 3;
    
    // すべてのLEDを元の色で点灯
    for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        rgb_matrix_set_color(i, original_colors[i][0], original_colors[i][1], original_colors[i][2]);
    }
}

// すべてのLEDを赤色に表示する関数
void debug_show_all_red(void) {
    debug_mode = true;
    debug_mode_type = 4;
    
    // すべてのLEDを赤色で点灯
    for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        rgb_matrix_set_color(i, 255, 0, 0);
    }
}

// デバッグモードの更新関数
void debug_update(void) {
    if (!debug_mode) return;
    
    static uint32_t last_update = 0;
    uint32_t now = timer_read32();
    
    // LEDインデックス確認モードの場合
    if (debug_mode_type == 1) {
        // 1秒ごとに次のLEDに移動
        if (now - last_update > 1000) {
            // 前のLEDを消灯
            rgb_matrix_set_color(debug_led_index, 0, 0, 0);
            
            // 次のLEDに移動
            debug_led_index = (debug_led_index + 1) % RGB_MATRIX_LED_COUNT;
            
            // 現在のLEDを赤色に点灯
            rgb_matrix_set_color(debug_led_index, 255, 0, 0);
            
            last_update = now;
        }
    }
}
#endif

// すべてのLEDの色を初期化する関数
void initialize_led_colors(void) {
    // すべてのLEDを黒（消灯）に初期化
    for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        original_colors[i][0] = 0;
        original_colors[i][1] = 0;
        original_colors[i][2] = 0;
    }
    
    // MIDIノートに対応するLEDの色を設定
    for (uint8_t i = 0; i < sizeof(midi_led_map) / sizeof(midi_led_map_t); i++) {
        uint16_t note = midi_led_map[i].note;
        uint8_t led_idx = midi_led_map[i].led_idx;
        
        // Cノートは紫色 (191, 0, 255)
        if (is_c_note(note)) {
            original_colors[led_idx][0] = 191;
            original_colors[led_idx][1] = 0;
            original_colors[led_idx][2] = 255;
            rgb_matrix_set_color(led_idx, 191, 0, 255);
        }
        // Cメジャースケール（C以外）は青色 (0, 0, 255)
        else if (is_c_major_scale(note)) {
            original_colors[led_idx][0] = 0;
            original_colors[led_idx][1] = 0;
            original_colors[led_idx][2] = 255;
            rgb_matrix_set_color(led_idx, 0, 0, 255);
        }
        // その他のノートは暗い灰色 (50, 50, 50)
        else {
            original_colors[led_idx][0] = 50;
            original_colors[led_idx][1] = 50;
            original_colors[led_idx][2] = 50;
            rgb_matrix_set_color(led_idx, 50, 50, 50);
        }
    }
}

// keyboard_post_init_user関数
void keyboard_post_init_user(void) {
    #ifdef RGB_MATRIX_ENABLE
    // RGB Matrixを有効化
    rgb_matrix_enable();
    rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
    
    // すべてのLEDを黒（消灯）に設定
    rgb_matrix_sethsv(0, 0, 0);
    
    // 少し待機（安定化のため）
    wait_ms(100);
    
    // LEDの色を初期化
    initialize_led_colors();
    
    // デバッグモードを無効化
    debug_mode = false;
    #endif
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    #ifdef RGB_MATRIX_ENABLE
    // デバッグモード切り替え
    // ADJUST層でF1キーを押すとLEDインデックス確認モード
    if (keycode == KC_F1 && record->event.pressed && layer_state_is(_ADJUST)) {
        if (debug_mode && debug_mode_type == 1) {
            // デバッグモードをオフ
            debug_mode = false;
            // 元の色に戻す
            for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
                rgb_matrix_set_color(i, original_colors[i][0], original_colors[i][1], original_colors[i][2]);
            }
        } else {
            // LEDインデックス確認モード
            debug_show_led_indices();
        }
        return false;
    }
    
    // ADJUST層でF2キーを押すとMIDIノート確認モード
    if (keycode == KC_F2 && record->event.pressed && layer_state_is(_ADJUST)) {
        if (debug_mode && debug_mode_type == 2) {
            // デバッグモードをオフ
            debug_mode = false;
            // 元の色に戻す
            for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
                rgb_matrix_set_color(i, original_colors[i][0], original_colors[i][1], original_colors[i][2]);
            }
        } else {
            // MIDIノート確認モード
            debug_show_midi_note_mapping();
        }
        return false;
    }
    
    // ADJUST層でF3キーを押すとカラー設定確認モード
    if (keycode == KC_F3 && record->event.pressed && layer_state_is(_ADJUST)) {
        if (debug_mode && debug_mode_type == 3) {
            // デバッグモードをオフ
            debug_mode = false;
            // 元の色に戻す
            for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
                rgb_matrix_set_color(i, original_colors[i][0], original_colors[i][1], original_colors[i][2]);
            }
        } else {
            // カラー設定確認モード
            debug_show_color_settings();
        }
        return false;
    }
    
    // ADJUST層でF4キーを押すと全てのLEDを赤色に表示
    if (keycode == KC_F4 && record->event.pressed && layer_state_is(_ADJUST)) {
        if (debug_mode && debug_mode_type == 4) {
            // デバッグモードをオフ
            debug_mode = false;
            // 元の色に戻す
            for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
                rgb_matrix_set_color(i, original_colors[i][0], original_colors[i][1], original_colors[i][2]);
            }
        } else {
            // 全てのLEDを赤色に表示
            debug_show_all_red();
        }
        return false;
    }
    
    // MIDIノートキーコードの場合
    if (keycode >= MI_C && keycode <= MI_Ds5) {
        uint8_t led_idx = get_led_index_from_midi_note(keycode);
        
        if (led_idx != 255) {
            if (record->event.pressed) {
                // キーが押された時
                key_pressed[led_idx] = true;
                
                // キーを緑色に設定
                rgb_matrix_set_color(led_idx, 0, 255, 0);
                
                // 同じオクターブ内の同じノートのLEDも緑色に設定
                uint8_t note_value = get_midi_note_value(keycode);
                uint8_t octave = (keycode - MI_C) / 12;
                
                for (uint8_t i = 0; i < sizeof(midi_led_map) / sizeof(midi_led_map_t); i++) {
                    uint16_t other_note = midi_led_map[i].note;
                    uint8_t other_led_idx = midi_led_map[i].led_idx;
                    
                    if (get_midi_note_value(other_note) == note_value && (other_note - MI_C) / 12 == octave && other_led_idx != led_idx) {
                        key_pressed[other_led_idx] = true;
                        rgb_matrix_set_color(other_led_idx, 0, 255, 0);
                    }
                }
            } else {
                // キーが離された時
                key_pressed[led_idx] = false;
                
                // キーを元の色に戻す
                rgb_matrix_set_color(led_idx, original_colors[led_idx][0], original_colors[led_idx][1], original_colors[led_idx][2]);
                
                // 同じオクターブ内の同じノートのLEDも元の色に戻す
                uint8_t note_value = get_midi_note_value(keycode);
                uint8_t octave = (keycode - MI_C) / 12;
                
                for (uint8_t i = 0; i < sizeof(midi_led_map) / sizeof(midi_led_map_t); i++) {
                    uint16_t other_note = midi_led_map[i].note;
                    uint8_t other_led_idx = midi_led_map[i].led_idx;
                    
                    if (get_midi_note_value(other_note) == note_value && (other_note - MI_C) / 12 == octave && other_led_idx != led_idx) {
                        key_pressed[other_led_idx] = false;
                        rgb_matrix_set_color(other_led_idx, original_colors[other_led_idx][0], original_colors[other_led_idx][1], original_colors[other_led_idx][2]);
                    }
                }
            }
        }
    }
    #endif
    
    return true;
}

// マトリックススキャン関数
void matrix_scan_user(void) {
    #ifdef RGB_MATRIX_ENABLE
    // デバッグモードの更新
    debug_update();
    #endif
}

*/