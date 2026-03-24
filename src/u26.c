#include "u26.h"
#include <string.h>
#include <ctype.h>

/**
 * RFC 4648準拠のBase32アルファベット
 * 数字の 0, 1, 8, 9 を含まないため、視認性が高く、
 * かつケースインセンシティブ（大文字小文字を問わない）な運用が可能です。
 */
static const char U26_CHARSET[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";

int u26_encode(int64_t unix_time, char* out_buffer) {
    // 指定されたエポック以前の時間はエラー
    if (unix_time < U26_EPOCH_OFFSET) {
        return U26_ERR_PAST_EPOCH;
    }

    uint64_t delta = (uint64_t)(unix_time - U26_EPOCH_OFFSET);
    char temp[32]; // 十分なバッファサイズを確保
    int i = 0;

    // ゼロ地点（エポックちょうど）のハンドリング
    if (delta == 0) {
        out_buffer[0] = U26_CHARSET[0];
        out_buffer[1] = '\0';
        return U26_SUCCESS;
    }

    // Base32 変換ループ (32進法)
    // 32は2の5乗なので、計算効率も非常に高いです
    while (delta > 0) {
        temp[i++] = U26_CHARSET[delta % 32];
        delta /= 32;
    }

    // 一時バッファに逆順で入っている文字を反転させて出力
    for (int j = 0; j < i; j++) {
        out_buffer[j] = temp[i - 1 - j];
    }
    out_buffer[i] = '\0';

    return U26_SUCCESS;
}

int64_t u26_decode(const char* u26_str) {
    if (!u26_str || u26_str[0] == '\0') {
        return -1;
    }

    uint64_t delta = 0;

    for (size_t i = 0; u26_str[i] != '\0'; i++) {
        // 全ての入力を大文字として扱うことで、小文字入力も許容します
        char c = toupper((unsigned char)u26_str[i]);
        int val = -1;

        // 文字から数値へのマッピング
        if (c >= 'A' && c <= 'Z') {
            val = c - 'A';
        } else if (c >= '2' && c <= '7') {
            val = c - '2' + 26;
        } else {
            // 不正な文字（Base32に含まれない文字）
            return -1;
        }

        delta = (delta * 32) + (uint64_t)val;
    }

    return (int64_t)(delta + U26_EPOCH_OFFSET);
}
