#include "features.h"

#ifdef LEADER_HASH_ENABLE
#    include "process_features/process_leader_hash.h"
#    include "leader_hash.h"
#endif

#ifdef MOD_KEYS_ENABLE
#    include "process_features/process_mod_keys.h"
#endif

#ifdef RAWHID_MOD_ENABLE
#    include "process_features/process_rawhid_mod.h"
#endif

#ifdef COUNTER_KEYS_ENABLE
#    include "process_features/process_counter_keys.h"
#endif

#ifdef ALT_TAB_KEY_ENABLE
#    include "process_features/process_alt_tab.h"
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
#ifdef MOD_KEYS_ENABLE
    process_mod_keys(keycode, record) &&
#endif
#ifdef RAWHID_MOD_ENABLE
    process_rawhid_mod(keycode, record) &&
#endif
#ifdef COUNTER_KEYS_ENABLE
    process_counter_keys(keycode, record) &&
#endif
#ifdef ALT_TAB_KEY_ENABLE
    process_alt_tab(keycode, record) &&
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
