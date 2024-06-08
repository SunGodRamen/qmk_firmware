#ifndef LOGGER_H
#define LOGGER_H
#include "quantum.h"
#include "config_manager.h"
#include <stdarg.h>
#include <stdio.h>
#include "print.h"
#include "debug.h"

#define LOG_BUFFER_SIZE 256

typedef enum {
    LOG_LEVEL_ERROR,   // Lowest value, logs only errors
    LOG_LEVEL_WARN,    // Logs warning messages and exceptions
    LOG_LEVEL_INFO,    // Logs informational messages
    LOG_LEVEL_DEBUG    // Highest value, most verbose logging level
} log_level_t;

extern const log_level_t default_log_level;

void log_init(uint8_t level);
void set_log_level(log_level_t level);
void write_log_format(log_level_t level, const char* format, ...);

#endif // LOGGER_H
