#include "./process_rawhid_tap.h"

bool process_rawhid_tap(uint16_t keycode, keyrecord_t *record) {
    if (keycode == FT_RAW_MOD) {
        if (record->event.pressed) {
            tap_code16(LDR_B);
            return false;
        }
    }
    return true;
}
