#include <status.h>

const char *status_strings[] = {
    "Unsupported",
    "Pending",
    "Invalid parameter",
    "Invalid offset",
    "Invalid kind",
    "Invalid path",
    "Not enough memory",
    "Not found",
    "Reached EOF",
    "File corruption",
    "Name too long",
    "Buffer too small",
};

const char *status_str(status_t status) {
    if (!status) return "Success";
    status &= 0x7FFFFFFFFFFFFFFF; // Get the absolute value
    status -= 1;
    if ((uint64_t) status >= (sizeof(status_strings) / sizeof(status_strings[0]))) return "Invalid error";
    return status_strings[status];
}
