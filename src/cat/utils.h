#ifndef CAT_UTILS_H
#define CAT_UTILS_H

#include <stdbool.h>
#include <stdlib.h>

#include "../common/utils.h"

struct options {
  bool number_nonblank;
  bool number;
  bool squeeze_blank;
  bool show_ends;
  bool show_nonprinting;
  bool show_tabs;
  bool e, E;
};

/// @brief parse cmd line arguments
/// @param argc from int main(int argc, char** argv); amount of arguments
/// @param argv from int main(int argc, char** argv); arguments
/// @param flags struct options
/// @return 1 if error and 0 if success
int parse_args(int argc, char** argv, struct options* flags);

/// @brief filter flags. Ignore -n if there is -b flag
/// @param flags struct options
void filter_flags(struct options* flags);

/// @brief process all the files with flags
/// @param flags struct options
/// @param files entries
/// @param files_count amount of files
/// @param files_len array of files sizes
void process_files(struct options flags, char** files, size_t files_count,
                   size_t* files_len);
#endif