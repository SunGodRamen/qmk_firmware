#ifndef MOD_KEYS_H
#define MOD_KEYS_H

#include "quantum.h"
#include "../aliases.h"
#include "../features/feature_keycodes.h"

typedef struct {
    uint16_t keycode;
    uint16_t mod_keycode;
    uint8_t modifier;
} custom_mod_key_t;

extern custom_mod_key_t custom_mod_keys[];
extern uint8_t NUM_CUSTOM_MOD_KEYS;

#endif //MOD_KEYS_H