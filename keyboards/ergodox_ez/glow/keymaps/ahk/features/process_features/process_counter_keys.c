#include "process_counter_keys.h"

bool process_counter_keys(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case COUNTER_INCR:
            return incr_action(keycode, record);
        case COUNTER_TARE:
            return tare_action(keycode, record);
        case COUNTER_DECR:
            return decr_action(keycode, record);
        case COUNTER_VALUE:
            return valu_action(keycode, record);
        case KC_1:
        case KC_2:
        case KC_3:
        case KC_4:
        case KC_5:
        case KC_6:
        case KC_7:
        case KC_8:
        case KC_9:
            return handle_number_key_tap(keycode, record);
        default:
            return true;
    }
}