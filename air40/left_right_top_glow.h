/*
 * Copyright 2023
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

RGB_MATRIX_EFFECT(left_column_glow)
RGB_MATRIX_EFFECT(right_column_glow)
RGB_MATRIX_EFFECT(top_row_glow)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static bool ARRAY_CONTAINS(uint8_t led, uint8_t* arr, size_t length) {
    for (uint8_t i = 0; i < length; i++) {
        if (arr[i] == led) {
            return true;
        }
    }
    return false;
}

static bool light_keys(effect_params_t* params, uint8_t* keys, size_t size) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    HSV hsv  = rgb_matrix_config.hsv;
    RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
    RGB brown = {.r = 140, .g = 66, .b = 14};
    for (uint8_t i = led_min; i < led_max; i++) {
        if (ARRAY_CONTAINS(i, keys, size)) {
            rgb_matrix_set_color(i, brown.r, brown.g, brown.b);
        } else {
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }
    return rgb_matrix_check_finished_leds(led_max);
}

static bool left_column_glow(effect_params_t* params) {
    uint8_t keys[] = {11, 23, 35, 50};
    size_t size = sizeof(keys)/sizeof(keys[0]);
    return light_keys(params, keys, size);
}

static bool right_column_glow(effect_params_t* params) {
    uint8_t keys[] = {0, 12, 24, 36};
    size_t size = sizeof(keys)/sizeof(keys[0]);
    return light_keys(params, keys, size);
}

static bool top_row_glow(effect_params_t* params) {
    uint8_t keys[] = {11, 10,  9,  8, 7,  6,  5,  4,  3,  2,  1,  0};
    size_t size = sizeof(keys)/sizeof(keys[0]);
    return light_keys(params, keys, size);
}

#endif
