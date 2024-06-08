#include "logger.h"

const log_level_t default_log_level = LOG_LEVEL_DEBUG;

log_level_t local_log_level = default_log_level;

const char* log_level_to_string(log_level_t level) {
    switch (level) {
        case LOG_LEVEL_ERROR:
            return "ERROR";
        case LOG_LEVEL_WARN:
            return "WARN";
        case LOG_LEVEL_INFO:
            return "INFO";
        case LOG_LEVEL_DEBUG:
            return "DEBUG";
        default:
            return "UNKNOWN";
    }
}

void set_log_level(log_level_t level) {
    write_log_format(LOG_LEVEL_INFO, "Setting log level to '%s'\n", log_level_to_string(level));
    local_log_level = level;
    config_set_log_level(level);
}

void log_init(uint8_t value) {
    if (value >= LOG_LEVEL_ERROR && value <= LOG_LEVEL_DEBUG) {
        set_log_level((log_level_t)value);
    } else {
        set_log_level(default_log_level);
        write_log_format(LOG_LEVEL_WARN, "Provided log level: '%d' outside of possible 0-3, using default.\n", value);
    }
}

static bool should_log(log_level_t level) {
#ifdef CONSOLE_ENABLE
    return config_get_log_level() <= level;
#else
    return true;
    // return false;
#endif
}

void write_log_format(log_level_t level, const char* format, ...) {
    if (should_log(level)) {
        char buffer[LOG_BUFFER_SIZE];
        va_list args;
        va_start(args, format);
        vsnprintf(buffer, sizeof(buffer), format, args);
        va_end(args);
        dprintf("[%s] %s", log_level_to_string(level), buffer);
    }
}
