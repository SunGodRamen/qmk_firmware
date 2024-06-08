#ifndef RAWHID_MOD_H
#define RAWHID_MOD_H

#include "quantum.h"
#include "stdint.h"
#include "stdbool.h"

void convert_keycode_to_raw_hid(uint16_t keycode, bool pressed, uint8_t* data);

#endif
