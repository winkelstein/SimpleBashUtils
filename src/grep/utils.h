#ifndef GREP_UTILS
#define GREP_UTILS
#include <regex.h>
#include <stdbool.h>

#include "../common/utils.h"

typedef struct options {
  bool e;
  bool i;
  bool v;
  bool c;
  bool l;
  bool n;
  char** patterns;
  size_t patters_number;
} options_t;

int parse_args(int argc, char** argv, struct options* flags);
void free_all(char** files, size_t count, options_t* flags,
              const char** filenames, size_t* files_len);
bool match_regex(regex_t* regex, size_t regex_number, const char* str);
int compile_regex(regex_t* regex, const char* template, int reg_flags);

#endif