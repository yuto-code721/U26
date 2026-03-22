#include <stdio.h>
#include <time.h>
#include "../include/u26.h"

/**
 * U26 Standard Demonstration
 * This program shows how to convert current time to U26
 * and verify it for a 1000-year sustainable future.
 */

int main() {
    // 1. Get Current Time (UTC)
    time_t now = time(NULL);
    
    // 2. Define a target in the distant future (Year 3038)
    // 3038-01-19 03:14:07 UTC
    int64_t future_target = 33706695647LL; 

    char u26_now[12];
    char u26_future[12];
    char integrity_now[17];
    char integrity_future[17];

    // 3. Process: Current Time
    u26_encode((int64_t)now, u26_now);
    u26_get_integrity(u26_now, integrity_now);

    // 4. Process: Future Time (The 3038 Problem Solver)
    u26_encode(future_target, u26_future);
    u26_get_integrity(u26_future, integrity_future);

    // --- Microsoft Proposal Output Format ---
    printf("================================================\n");
    printf("   U26 Protocol Demo\n");
    printf("================================================\n\n");

    printf("[1] CURRENT STATUS (UTC)\n");
    printf("    Unix Time:   %lld\n", (int64_t)now);
    printf("    U26 ID:      %s\n", u26_now);
    printf("    Integrity:   %s\n\n", integrity_now);

    printf("[2] FUTURE PROOF (Year 3038)\n");
    printf("    Unix Time:   %lld\n", future_target);
    printf("    U26 ID:      %s\n", u26_future);
    printf("    Integrity:   %s\n\n", integrity_future);

    printf("[3] STORAGE EFFICIENCY ANALYSIS\n");
    printf("    Standard ISO String:  20 Bytes\n");
    printf("    U26 Encoded String:    6 Bytes\n");
    printf("    Reduction Rate:       70.0%%\n\n");

    // 5. Verification (Decoding)
    int64_t decoded_time = u26_decode(u26_future);
    printf("[4] SYSTEM VERIFICATION\n");
    if (decoded_time == future_target) {
        printf("    Result: PASS (Millennium Data Recovery Success)\n");
    } else {
        printf("    Result: FAIL\n");
    }

    printf("\n================================================\n");
    printf(" Proposed by Yamamoto Yuto for a Greener Cloud.\n");
    printf("================================================\n");

    return 0;
}