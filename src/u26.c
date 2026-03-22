#include "u26.h"
#include <string.h>

static const char U26_CHARSET[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

int u26_encode(int64_t unix_time, char* out_buffer) {
    if (unix_time < U26_EPOCH_OFFSET) {
        return U26_ERR_PAST_EPOCH;
    }

    uint64_t delta = (uint64_t)(unix_time - U26_EPOCH_OFFSET);
    char temp[16];
    int i = 0;

    // Handle the absolute zero point
    if (delta == 0) {
        out_buffer[0] = '0';
        out_buffer[1] = '\0';
        return U26_SUCCESS;
    }

    // Base62 transformation loop (Low-level optimization)
    while (delta > 0) {
        temp[i++] = U26_CHARSET[delta % 62];
        delta /= 62;
    }

    // Reverse the temporary buffer into the output
    for (int j = 0; j < i; j++) {
        out_buffer[j] = temp[i - 1 - j];
    }
    out_buffer[i] = '\0';

    return U26_SUCCESS;
}

int64_t u26_decode(const char* u26_str) {
    if (!u26_str) return -1;

    uint64_t delta = 0;
    size_t len = strlen(u26_str);

    for (size_t i = 0; i < len; i++) {
        char c = u26_str[i];
        int val = 0;

        // Optimized character mapping
        if (c >= '0' && c <= '9') val = c - '0';
        else if (c >= 'A' && c <= 'Z') val = c - 'A' + 10;
        else if (c >= 'a' && c <= 'z') val = c - 'a' + 36;
        else return -1; // Invalid character detected

        delta = delta * 62 + val;
    }

    return (int64_t)(delta + U26_EPOCH_OFFSET);
}
