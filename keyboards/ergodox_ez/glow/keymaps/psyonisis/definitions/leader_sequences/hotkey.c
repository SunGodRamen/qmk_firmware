#include "hotkey.h"

void hotkey_vs_command(void) {
    register_code16(LS_);
    tap_code16(LCTL(P_));
    unregister_code16(LS_);
}

void hotkey_vs_open(void) {
    register_code16(KC_LCTL);
    tap_code16(K_);
    wait_ms(100);
    tap_code16(O_);
    unregister_code16(KC_LCTL);
}

void hotkey_ditto(void) {
    register_code16(KC_LCTL);
    tap_code16(KC_GRAVE);
    unregister_code16(KC_LCTL);
}

void hotkey_everything(void) {
    register_code16(KC_LGUI);
    register_code16(KC_LSFT);
    tap_code16(KC_F);
    unregister_code16(KC_LSFT);
    unregister_code16(KC_LGUI);
}
