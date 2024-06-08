#include "mod_keys.h"

custom_mod_key_t custom_mod_keys[] = {
    {KC_COLN,      KC_SCLN,           KC_LSFT},
    {KC_DQUO,      KC_QUOT,           KC_LSFT},
    {KC_DOT,       KC_EXCLAIM,        KC_LSFT},
    {KC_COMM,      KC_QUES,           KC_LSFT},
    {MDRAW,        LGUI(KC_TAB),      KC_LGUI},
    {MDRAW,        LALT(KC_TAB),      KC_LALT},
    {MDRAW,        LCTL(KC_TAB),      KC_LCTL},
};

uint8_t NUM_CUSTOM_MOD_KEYS = sizeof(custom_mod_keys) / sizeof(custom_mod_key_t);
