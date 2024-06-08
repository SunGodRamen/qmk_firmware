#pragma once

#include "quantum.h"
#include "../../features/leader_hash.h"
#include "../../features/feature_keycodes.h"
#include <string.h>

// Define a function pointer type for leader sequence actions with an empty parameter list
typedef void (*LeaderSequenceAction)(void);

typedef struct {
    uint16_t* sequence;
    uint8_t size;
    LeaderSequenceAction action;  // Function pointer to handle the action
} LeaderSequence;

#include "./ahk.h"
#include "./macro.h"
#include "./hotkey.h"
#include "./function.h"

void leader_hash_end_user(uint16_t leader_key);
