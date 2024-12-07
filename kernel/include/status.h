#pragma once
#include <stdint.h>
#include <stddef.h>
typedef intptr_t status_t;
enum {
    UNSUPPORTED=1,
    INVALID_PARAM,
};
// TODO: Status map to convert status to string
// TODO: Map to convert status to errno
