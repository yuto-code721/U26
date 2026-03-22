#include "u26.h"
#include <string.h>
#include <openssl/sha.h>
#include <stdio.h>

static const char U26_ALPHABET[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

void u26_encode(int64_t unix_time, char* out_str) {
    int64_t val = unix_time - U26_OFFSET;
    if (val < 0) { strcpy(out_str, "0"); return; }
    
    char buffer[16];
    int i = 0;
    while (val > 0) {
        buffer[i++] = U26_ALPHABET[val % 62];
        val /= 62;
    }
    for (int j = 0; j < i; j++) out_str[j] = buffer[i - 1 - j];
    out_str[i] = '\0';
    if (i == 0) strcpy(out_str, "0");
}

int64_t u26_decode(const char* u26_str) {
    int64_t val = 0;
    while (*u26_str) {
        const char* p = strchr(U26_ALPHABET, *u26_str++);
        if (p) val = val * 62 + (int64_t)(p - U26_ALPHABET);
    }
    return val + U26_OFFSET;
}

void u26_get_integrity(const char* u26_str, char* hash_hex) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)u26_str, strlen(u26_str), hash);
    for (int i = 0; i < 8; i++) sprintf(hash_hex + (i * 2), "%02x", hash[i]);
    hash_hex[16] = '\0';
}