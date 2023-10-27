#pragma once

#ifdef RGB_MATRIX_KEYREACTIVE_ENABLED

typedef HSV (*bullet_f)(HSV hsv, int16_t x, int16_t dy, uint16_t tick, bool off);

bool effect_runner_bullet(uint8_t start, effect_params_t* params, bullet_f effect_func) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    uint8_t count = g_last_hit_tracker.count;
    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        HSV hsv = rgb_matrix_config.hsv;
        hsv.v   = 0;
        int16_t  x    = g_led_config.point[i].x;
        for (uint8_t j = start; j < count; j++) {
            int16_t  dy   = g_led_config.point[i].y - g_last_hit_tracker.y[j];
            uint16_t tick = scale16by8(g_last_hit_tracker.tick[j], qadd8(rgb_matrix_config.speed, 1));
            bool off = false;
            if (dy < -17 || dy > 17) off = true;
            hsv           = effect_func(hsv, x, dy, tick, off);
        }
        hsv.h   = qadd8(hsv.h, scale8(x, 180));
        hsv.v   = scale8(hsv.v, rgb_matrix_config.hsv.v);
        RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
    return rgb_matrix_check_finished_leds(led_max);
}
#endif // RGB_MATRIX_KEYREACTIVE_ENABLED