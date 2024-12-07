#pragma once
#include <stdarg.h>

void kprint_va(const char* fmt, va_list args);
static void kprint(const char* fmt, ...);

static void kprint(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    kprint_va(fmt, args);
    va_end(args);
}
