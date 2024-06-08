#ifndef COUNTER_KEYS_H
#define COUNTER_KEYS_H

#include "quantum.h"
#include "../lib/keymap_ascii.h"

bool tare_action(uint16_t keycode, keyrecord_t *record);
bool incr_action(uint16_t keycode, keyrecord_t *record);
bool decr_action(uint16_t keycode, keyrecord_t *record);
bool valu_action(uint16_t keycode, keyrecord_t *record);
bool handle_number_key_tap(uint16_t keycode, keyrecord_t *record);

#endif //COUNTER_KEYS_H