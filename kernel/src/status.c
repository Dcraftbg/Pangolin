#include <status.h>

static const char *status_strings[STATUS_COUNT] = {
    "OK",
    [UNSUPPORTED]       = "Unsupported",
    [PENDING]           = "Pending",
    [INVALID_PARAM]     = "Invalid parameter",
    [INVALID_OFFSET]    = "Invalid offset",
    [INVALID_KIND]      = "Invalid kind",
    [INVALID_PATH]      = "Invalid path",
    [NOT_ENOUGH_MEMORY] = "Not enough memory",
    [NOT_FOUND]         = "Not found",
    [REACHED_EOF]       = "Reached EOF",
    [FILE_CORRUPTION]   = "File corruption",
    [NAME_TOO_LONG]     = "Name too long",
    [BUF_TOO_SMALL]     = "Buffer too small",
};

const char *status_str(status_t status) {
    status = -status;
    if ((uint64_t) status >= (sizeof(status_strings) / sizeof(status_strings[0]))) return "Invalid error";
    return status_strings[status];
}
