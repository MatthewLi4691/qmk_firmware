//
// Created by hypro on 10/27/2023.
//
#ifdef RGB_MATRIX_KEYREACTIVE_ENABLED
#   ifdef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIBULLET
RGB_MATRIX_EFFECT(SOLID_REACTIVE_MULTIBULLET)
#       ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static HSV SOLID_REACTIVE_MULTIBULLET_math (HSV hsv, int16_t x, uint16_t tick, bool off) {
    x = x - 10;
    uint16_t effect = tick > x ? (255 < 3 * (tick - x) ? 0 : 255 + 3 * (x - tick)) : 0;
    if (effect > 255) effect = 255;
    if (off) effect = 0;
    hsv.v = qadd8(hsv.v, effect);
    return hsv;
}

bool SOLID_REACTIVE_MULTIBULLET(effect_params_t* params) {
    return effect_runner_bullet(0, params, &SOLID_REACTIVE_MULTIBULLET_math);
}

#       endif
#   endif
#endif