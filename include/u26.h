/**
 * @file u26.h
 * @author Yamamoto Yuto (Kyoto, JP)
 * @brief U26 Universal Timestamp Standard v1.0.0
 * * DESIGN GOAL: 
 * - Solve Y2038 overflow using an epoch shift to 2026-03-22.
 * - Compress temporal data into 6-character Base62 alphanumeric strings.
 */

 #ifndef U26_STANDARD_H
 #define U26_STANDARD_H
 
 #include <stdint.h>
 #include <stddef.h>
 
 #ifdef __cplusplus
 extern "C" {
 #endif
 
 /* U26 Epoch Origin: 2026-03-22T04:55:00Z (Unix: 1742619300) */
 #define U26_EPOCH_OFFSET 1742619300L
 
 /* Error Codes */
 #define U26_SUCCESS          0
 #define U26_ERR_BUFFER_SMALL -1
 #define U26_ERR_PAST_EPOCH   -2
 
 /**
  * @brief Encodes a Unix timestamp into a U26 alphanumeric string.
  * @param unix_time The source POSIX timestamp.
  * @param out_buffer Minimum size should be 12 bytes to be safe.
  * @return U26_SUCCESS on success, error code otherwise.
  */
 int u26_encode(int64_t unix_time, char* out_buffer);
 
 /**
  * @brief Decodes a U26 string back into a Unix timestamp.
  * @param u26_str The U26 compressed string.
  * @return The 64-bit Unix timestamp.
  */
 int64_t u26_decode(const char* u26_str);
 
 #ifdef __cplusplus
 }
 #endif
 
 #endif // U26_STANDARD_H
