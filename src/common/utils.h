#ifndef COMMON_UTILS
#define COMMON_UTILS
#include <stdbool.h>
#include <stddef.h>

/// @brief parse cmd line arguments and get filenames from it. First call
/// (filenames = NULL) returns amount of filenames. (for cat)
/// @param argc from int main(int argc, char** argv); amount of arguments
/// @param argv from int main(int argc, char** argv); arguments
/// @param filenames array of strings for filenames
/// @param len length of filenames array
/// @return length of filenames array
size_t get_filenames_cat(int argc, char** argv, const char** filenames,
                         size_t len);

/// @brief parse cmd line arguments and get filenames from it. First call
/// (filenames = NULL) returns amount of filenames. (for grep)
/// @param argc from int main(int argc, char** argv); amount of arguments
/// @param argv from int main(int argc, char** argv); arguments
/// @param filenames array of strings for filenames
/// @param len length of filenames array
/// @return length of filenames array
size_t get_filenames_grep(int argc, char** argv, const char** filenames,
                          size_t len);

/// @brief read from files and put all files entries into char** out array (for
/// cat)
/// @param filenames array of filenames
/// @param count amount of filenames in the array
/// @param files_len array of files sizes
/// @param out array of entries
/// @return 1 if error and 0 if success
int merge_files_cat(const char** filenames, size_t count, size_t* files_len,
                    char** out);

/// @brief read from files and put all files entries into char** out array (for
/// grep)
/// @param filenames array of filenames
/// @param count amount of filenames in the array
/// @param files_len array of files sizes
/// @param out array of entries
/// @return 1 if error and 0 if success
int merge_files_grep(const char** filenames, size_t count, size_t* files_len,
                     char** out);

/// @brief read all the file. First call (out = NULL) returns file size
/// @param name name of file
/// @param out file entry array
/// @param bytes amount of bytes needed for reading
/// @return amount of bytes
size_t read_file(const char* name, char* out, size_t bytes);
#endif