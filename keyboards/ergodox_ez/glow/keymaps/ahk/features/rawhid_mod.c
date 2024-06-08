#include "rawhid_mod.h"

// Function to convert keycode and press/release status into Raw HID data
void convert_keycode_to_raw_hid(uint16_t keycode, bool pressed, uint8_t* data) {
    // Store the keycode in the first byte of the data
    data[0] = (uint8_t)(keycode & 0xFF);
    data[1] = (uint8_t)(keycode >> 8);

    // Store the press/release status in the second byte (1 for pressed, 0 for released)
    data[2] = pressed ? 1 : 0;
}
