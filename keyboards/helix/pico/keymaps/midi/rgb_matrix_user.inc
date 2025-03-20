RGB_MATRIX_EFFECT(pad64_effect)

// Step 2.
// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// キーが押されているかどうかを記録する配列
static bool key_pressed[RGB_MATRIX_LED_COUNT] = {false};

// キーの元の色を保存する配列
static uint8_t original_colors[RGB_MATRIX_LED_COUNT][3];

// 外部からキーの状態を設定する関数
void set_key_pressed(uint8_t led_idx, bool pressed) {
    if (led_idx < RGB_MATRIX_LED_COUNT) {
        key_pressed[led_idx] = pressed;
    }
}

// MIDIノートの値を取得する関数（0=C, 1=C#, 2=D, ...）
static uint8_t get_midi_note_value(uint16_t keycode) {
    // MIDIノートの値を取得（MI_Cは0、MI_Csは1、MI_Dは2、...）
    if (keycode >= MI_C && keycode <= MI_Ds5) {
        return (keycode - MI_C) % 12;
    }
    return 255; // 無効な値
}

// MIDIノートがCかどうかをチェックする関数
static bool is_c_note(uint16_t keycode) {
    // C, C1, C2, C3, ...
    return get_midi_note_value(keycode) == 0;
}

// MIDIノートがCメジャースケール（C, D, E, F, G, A, B）に含まれるかチェックする関数
static bool is_c_major_scale(uint16_t keycode) {
    uint8_t note_value = get_midi_note_value(keycode);
    return note_value == 0 || // C
           note_value == 2 || // D
           note_value == 4 || // E
           note_value == 5 || // F
           note_value == 7 || // G
           note_value == 9 || // A
           note_value == 11;  // B
}

// キーマトリックスの位置からLEDインデックスを取得する関数
static uint8_t get_led_index_from_key_position(uint8_t row, uint8_t col) {
    if (row < MATRIX_ROWS && col < MATRIX_COLS) {
        return g_led_config.matrix_co[row][col];
    }
    return 255; // 無効な値
}

// キーコードからオクターブを取得する関数
static uint8_t get_octave_from_keycode(uint16_t keycode) {
    if (keycode >= MI_C && keycode <= MI_Ds5) {
        return (keycode - MI_C) / 12;
    }
    return 255; // 無効な値
}

// pad64_effectの初期化関数
static void pad64_effect_init(effect_params_t* params) {
    // すべてのLEDの元の色を初期化
    for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        original_colors[i][0] = 0;
        original_colors[i][1] = 0;
        original_colors[i][2] = 0;
        key_pressed[i] = false;
    }
}

// pad64_effectの実行関数
static bool pad64_effect_run(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    
    // キーマトリックスをスキャンして、各キーのLEDの色を設定
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            uint8_t led_idx = g_led_config.matrix_co[row][col];
            
            // 有効なLEDインデックスの場合のみ処理
            if (led_idx != NO_LED && led_idx >= led_min && led_idx < led_max) {
                // キーマップからキーコードを取得
                uint16_t keycode = pgm_read_word(&keymaps[0][row][col]);
                
                // MIDIノートキーコードの場合のみ処理
                if (keycode >= MI_C && keycode <= MI_Ds5) {
                    // キーが押されている場合は緑色に設定
                    if (key_pressed[led_idx]) {
                        rgb_matrix_set_color(led_idx, 0, 255, 0);
                    } else {
                        // キーが押されていない場合は元の色に設定
                        // Cノートは紫色 (191, 0, 255)
                        if (is_c_note(keycode)) {
                            rgb_matrix_set_color(led_idx, 191, 0, 255);
                            original_colors[led_idx][0] = 191;
                            original_colors[led_idx][1] = 0;
                            original_colors[led_idx][2] = 255;
                        }
                        // Cメジャースケール（C以外）は青色 (0, 0, 255)
                        else if (is_c_major_scale(keycode)) {
                            rgb_matrix_set_color(led_idx, 0, 0, 255);
                            original_colors[led_idx][0] = 0;
                            original_colors[led_idx][1] = 0;
                            original_colors[led_idx][2] = 255;
                        }
                        // その他のノートは暗い灰色 (50, 50, 50)
                        else {
                            rgb_matrix_set_color(led_idx, 50, 50, 50);
                            original_colors[led_idx][0] = 50;
                            original_colors[led_idx][1] = 50;
                            original_colors[led_idx][2] = 50;
                        }
                    }
                }
            }
        }
    }
    
    return rgb_matrix_check_finished_leds(led_max);
}

// pad64_effectのメイン関数
static bool pad64_effect(effect_params_t* params) {
    if (params->init) {
        pad64_effect_init(params);
    }
    return pad64_effect_run(params);
}

// process_record_user関数でキーの状態を更新する
bool process_record_rgb_matrix_user(uint16_t keycode, record_t *record) {
    // MIDIノートキーコードの場合
    if (keycode >= MI_C && keycode <= MI_Ds5) {
        uint8_t row = record->event.key.row;
        uint8_t col = record->event.key.col;
        uint8_t led_idx = g_led_config.matrix_co[row][col];
        
        if (led_idx != NO_LED) {
            if (record->event.pressed) {
                // キーが押された時
                set_key_pressed(led_idx, true);
                
                // 同じオクターブ内の同じノートのLEDも緑色に設定
                uint8_t note_value = get_midi_note_value(keycode);
                uint8_t octave = get_octave_from_keycode(keycode);
                
                // 他のキーをスキャンして、同じオクターブ内の同じノートを探す
                for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
                    for (uint8_t c = 0; c < MATRIX_COLS; c++) {
                        if (r == row && c == col) continue; // 自分自身はスキップ
                        
                        uint8_t other_led_idx = g_led_config.matrix_co[r][c];
                        if (other_led_idx == NO_LED) continue;
                        
                        uint16_t other_keycode = pgm_read_word(&keymaps[0][r][c]);
                        if (other_keycode >= MI_C && other_keycode <= MI_Ds5) {
                            if (get_midi_note_value(other_keycode) == note_value &&
                                get_octave_from_keycode(other_keycode) == octave) {
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
                uint8_t octave = get_octave_from_keycode(keycode);
                
                // 他のキーをスキャンして、同じオクターブ内の同じノートを探す
                for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
                    for (uint8_t c = 0; c < MATRIX_COLS; c++) {
                        if (r == row && c == col) continue; // 自分自身はスキップ
                        
                        uint8_t other_led_idx = g_led_config.matrix_co[r][c];
                        if (other_led_idx == NO_LED) continue;
                        
                        uint16_t other_keycode = pgm_read_word(&keymaps[0][r][c]);
                        if (other_keycode >= MI_C && other_keycode <= MI_Ds5) {
                            if (get_midi_note_value(other_keycode) == note_value &&
                                get_octave_from_keycode(other_keycode) == octave) {
                                set_key_pressed(other_led_idx, false);
                            }
                        }
                    }
                }
            }
        }
    }
    
    return true;
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS