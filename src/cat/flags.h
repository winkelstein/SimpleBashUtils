#ifndef CAT_FLAGS_H
#define CAT_FLAGS_H
#include <stddef.h>

/// @brief (GNU: --number-nonblank), number non-blank output lines
void process_b(char** file, size_t* file_len);

/// @brief implies -v but also display end-of-line characters as $
void process_e(char** file, size_t* file_len);

/// @brief GNU only: -E the same as -e, but without implying -v
void process_E(char** file, size_t* file_len);

/// @brief (GNU: --number), number all output lines
void process_n(char** file, size_t* file_len);

/// @brief (GNU: --squeeze-blank), squeeze multiple adjacent blank lines
void process_s(char** file, size_t* file_len);

/// @brief implies -v, but also display tabs as ^I
void process_t(char** file, size_t* file_len);

/// @brief GNU: -T the same as -t, but without implying -v
void process_T(char** file, size_t* file_len);

/// @brief (GNU: --show-nonprinting), displays nonprinting characters, except
/// for tabs and the end of line character
void process_v(char** file, const size_t* file_len);

#endif