#pragma once
#include <stddef.h>
#include <stdint.h>

size_t strlen(const char *str);

const char* strflip(char* str, size_t len);
size_t itoa(char* buf, size_t cap, int value);
size_t utoha(char* buf, size_t cap, unsigned int value);
size_t uptrtoha_full(char* buf, size_t cap, uintptr_t value);
