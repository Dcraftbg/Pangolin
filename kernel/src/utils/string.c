#include <string.h>

size_t strlen(const char *str) {
    size_t len = 0;
    while (str[len]) len++;
    return len;
}

const char* strflip(char* str, size_t len) {
    for(size_t i = 0; i < len/2; ++i) {
        char c = str[i];
        str[i] = str[len-i-1];
        str[len-i-1] = c;
    }
    return str;
}
size_t itoa(char* buf, size_t cap, int value) {
    size_t at=0;
    if(value == 0 && at < cap) {
        buf[at++] = '0';
        return at;
    }

    if(value < 0 && at < cap) {
        buf[at++] = '-';
        value = -value;
    }
    char* whole = buf+at;
    while(at < cap && value > 0) {
        int k = value % 10;
        value /= 10;
        buf[at++] = '0'+k;
    }
    strflip(whole, (buf+at)-whole);
    return at;
}
size_t sztoa(char* buf, size_t cap, size_t value) {
    size_t at=0;
    if(value == 0 && at < cap) {
        buf[at++] = '0';
        return at;
    }
    while(at < cap && value > 0) {
        int k = value % 10;
        value /= 10;
        buf[at++] = '0'+k;
    }
    strflip(buf, at);
    return at;
}
static const char* hex_digits = "0123456789ABCDEF";
size_t utoha(char* buf, size_t cap, unsigned int value) {
    size_t at=0;
    while(at < cap && value > 0) {
        int k = value & 0xF;
        value >>= 4;
        buf[at++] = hex_digits[k];
    }
    strflip(buf, at);
    return at;
}
size_t uptrtoha_full(char* buf, size_t cap, uintptr_t value) {
    size_t at=0;
    while(at < cap && at < 16) {
        int k = value & 0xF;
        value >>= 4;
        buf[at++] = hex_digits[k];
    }
    strflip(buf, at);
    return at;
}
