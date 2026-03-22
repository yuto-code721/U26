#ifndef U26_H
#define U26_H

#include <stdint.h>

// U26 Definition: Epoch is 2026-03-22 04:55:00 UTC
#define U26_OFFSET 1742619300L

// Converts Unix Time to U26 String (Base62)
// out_str should be at least 12 bytes
void u26_encode(int64_t unix_time, char* out_str);

// Converts U26 String back to Unix Time
int64_t u26_decode(const char* u26_str);

// Generates 16-char hex SHA256 integrity hash
void u26_get_integrity(const char* u26_str, char* hash_hex);

#endif