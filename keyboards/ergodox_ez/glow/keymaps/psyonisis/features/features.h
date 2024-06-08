#ifndef FEATURES_H
#define FEATURES_H

#include "quantum.h"
#include "../library/logger.h"
#include "stdbool.h"
#include "stdint.h"

bool process_record_features(uint16_t keycode, keyrecord_t *record);
void feature_task(void);

#endif // FEATURES_H
