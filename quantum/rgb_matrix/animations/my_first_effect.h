//
// Created by hypro on 10/27/2023.
//

#ifdef ENABLE_MY_FIRST_EFFECT
RGB_MATRIX_EFFECT(MY_FIRST_EFFECT)
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

bool MY_FIRST_EFFECT(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    HSV     hsv   = rgb_matrix_config.hsv;
    uint8_t scale = scale8(64, rgb_matrix_config.speed);
    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        // The y range will be 0..64, map this to 0..4
        // Relies on hue being 8-bit and wrapping
        hsv.h   = rgb_matrix_config.hsv.h + scale * (g_led_config.point[i].y >> 3);
        RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
    return rgb_matrix_check_finished_leds(led_max);
}

#endif
#endif
