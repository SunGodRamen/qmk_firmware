#include "features.h"

#ifdef LEADER_HASH_ENABLE
#    include "./process/process_leader_hash.h"
#    include "./business/leader_hash.h"
#endif

bool process_record_features(uint16_t keycode, keyrecord_t *record) {
    bool processKeycode = true;

    write_log_format(LOG_LEVEL_DEBUG, "\nprocess_record_features in\n");
    uint16_t start_time = timer_read();
    const char* event_type = record->tap.count > 0 ? "tap" : "hold";
    write_log_format(LOG_LEVEL_INFO, "Keycode: 0x%04X, press: %d, event: %s, layer: %d, mods: 0x%02X\n", keycode, record->event.pressed, event_type, biton32(layer_state), get_mods());

    if (!(
#ifdef LEADER_HASH_ENABLE
    process_leader_hash(keycode, record) &&
#endif
            true)) {
        processKeycode = false;
    }

    uint16_t end_time = timer_read();
    uint16_t duration = end_time - start_time;
    write_log_format(LOG_LEVEL_INFO, "process_record_features out: (duration: %d ms, processKeycode: %d, keycode:  0x%04X, pressed: %d)\n", duration, processKeycode, keycode, record->event.pressed);

    return processKeycode;
}

void feature_task(void) {
#ifdef LEADER_HASH_ENABLE
    leader_hash_task();
#endif
}
