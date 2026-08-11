#pragma once

typedef enum {
    LOG_INFO,
    LOG_OK,
    LOG_WARN,
    LOG_ERROR
} log_type_t;

void log(log_type_t type, const char *message);

