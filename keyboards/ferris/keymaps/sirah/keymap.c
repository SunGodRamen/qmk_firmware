#include QMK_KEYBOARD_H

#include "g/keymap_combo.h"

void matrix_init_user(void) {
  debug_enable=true;
  debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(
        KC_SCLN, KC_COMM, KC_DOT, KC_P, KC_Y,               KC_F, KC_G, KC_C,    KC_R,   KC_L,
        KC_A, ALT_T(KC_O), GUI_T(KC_E), CTL_T(KC_U), KC_I,     KC_D, KC_H, KC_T,    KC_N,   KC_S,
        KC_QUOT, KC_Q, KC_J, KC_K, KC_X,                    KC_B, KC_M, KC_W, KC_V, KC_Z,
                          KC_1, KC_LSFT,                    LT(1,KC_SPACE), MO(2)
    ),
    [1] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_HOME, KC_PGDN, KC_PGUP, KC_END,
                          KC_TRNS, KC_LSFT,                  KC_TRNS, KC_TRNS
    ),
    [2] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_7, KC_8, KC_9, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_0,    KC_4, KC_5, KC_6, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_1, KC_2, KC_3, KC_TRNS,
                          KC_TRNS, KC_LSFT,                  KC_TRNS, KC_TRNS
    )
};
// clang-format on
