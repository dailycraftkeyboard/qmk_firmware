RGB_MATRIX_EFFECT(pad64_effect)

// Step 2.
// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// キーが押されているかどうかを記録する配列
static bool key_pressed[RGB_MATRIX_LED_COUNT] = {false};

// キーの元の色を保存する配列
static uint8_t original_colors[RGB_MATRIX_LED_COUNT][3] = {
    // デフォルトでは、すべてのLEDを暗い灰色に設定
    [0 ... RGB_MATRIX_LED_COUNT-1] = {50, 50, 50}
};

// 外部からキーの状態を設定する関数
void set_key_pressed(uint8_t led_idx, bool pressed) {
    if (led_idx < RGB_MATRIX_LED_COUNT) {
        key_pressed[led_idx] = pressed;
    }
}

// 外部から元の色を設定する関数
void set_original_color(uint8_t led_idx, uint8_t r, uint8_t g, uint8_t b) {
    if (led_idx < RGB_MATRIX_LED_COUNT) {
        original_colors[led_idx][0] = r;
        original_colors[led_idx][1] = g;
        original_colors[led_idx][2] = b;
    }
}

// pad64_effectの実行関数
static bool pad64_effect(effect_params_t* params) {
    // dprintf("pad64_effect: Running on %s\n", is_keyboard_master() ? "MASTER" : "SLAVE");
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    // dprintf("pad64_effect / led_min: %d, led_max: %d\n", led_min, led_max);
    
    // すべてのLEDをスキャンして色を設定
    for (uint8_t i = led_min; i < led_max; i++) {
        // キーが押されている場合は緑色に設定（輝度を下げた）
        if (key_pressed[i]) {
            dprintf("pad64_effect / key pressed led_idx: %d\n", i);
            rgb_matrix_set_color(i, PRESSED_COLOR_R, PRESSED_COLOR_G, PRESSED_COLOR_B);
        } else {
            // キーが押されていない場合は元の色に設定
            rgb_matrix_set_color(i, original_colors[i][0], original_colors[i][1], original_colors[i][2]);
        }
    }
    
    return rgb_matrix_check_finished_leds(led_max);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS