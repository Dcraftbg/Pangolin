#pragma once
#include <stddef.h>
#include <stdint.h>

size_t strlen(const char *str);
void *memset (void *dest, int x          , size_t n);
void *memcpy (void *dest, const void *src, size_t n);
void *memmove(void* dest, const void* src, size_t n);
int memcmp(const void* s1, const void* s2, size_t max);
int strncmp(const char* s1, const char* s2, size_t max);
int strcmp(const char *restrict s1, const char *restrict s2);
size_t strlen(const char* cstr);
const char* strflip(char* str, size_t len);

size_t itoa(char* buf, size_t cap, int value);
size_t sztoa(char* buf, size_t cap, size_t value);
size_t utoha(char* buf, size_t cap, unsigned int value);
size_t uptrtoha_full(char* buf, size_t cap, uintptr_t value);
