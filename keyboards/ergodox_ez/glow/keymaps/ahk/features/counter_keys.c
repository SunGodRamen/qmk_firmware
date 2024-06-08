#include "counter_keys.h"

static int16_t counter = 1;

static bool incr_is_held = false;
static bool decr_is_held = false;
static bool number_key_pressed = false;


bool tare_action(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        counter = 1;
        uprintf("tare_action: Counter reset to %d\n", counter);
        return false;
    }
    return true;
}

bool incr_action(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        incr_is_held = true;
        number_key_pressed = false;
        uprint("incr_action: Key pressed\n");
    } else {
        incr_is_held = false;
        if (!number_key_pressed) {
            counter++;
            uprintf("incr_action: Counter incremented to %d\n", counter);
        }
        uprintf("incr_action: Key released");
    }
    return true;
}

bool decr_action(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        decr_is_held = true;
        number_key_pressed = false;
        uprintf("decr_action: Key pressed\n");
    } else {
        decr_is_held = false;
        if (!number_key_pressed) {
            counter--;
            uprintf("decr_action: Counter decremented to %d\n", counter);
        }
        uprint("decr_action: Key released\n");
    }
    return true;
}

bool valu_action(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        send_integer_as_keycodes(counter);
        uprintf("valu_action: Sent counter value %d\n", counter);
        return false;
    }
    return true;
}

bool handle_number_key_tap(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        return true;
    }

    int16_t number_value = keycode - KC_1 + 1;
    if (incr_is_held) {
        counter += number_value;
        number_key_pressed = true;
        uprintf("incr_action with number key: Counter incremented to %d\n", counter);
        return false;
    } else if (decr_is_held) {
        counter -= number_value;
        number_key_pressed = true;
        uprintf("decr_action with number key: Counter decremented to %d\n", counter);
        return false;
    }

    return true;
}
