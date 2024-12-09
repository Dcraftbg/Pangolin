#pragma once
#include <stdint.h>
#include <stddef.h>
typedef intptr_t status_t;
enum {
    UNSUPPORTED=1,
    PENDING,
    INVALID_PARAM,
    INVALID_OFFSET,
    INVALID_KIND,
    INVALID_PATH,
    NOT_ENOUGH_MEMORY,
    NOT_FOUND,
    REACHED_EOF,
    FILE_CORRUPTION,
    NAME_TOO_LONG,
    BUF_TOO_SMALL
};
// TODO: Status map to convert status to string
// TODO: Map to convert status to errno
