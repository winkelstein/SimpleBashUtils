#include "utils.h"

#include <getopt.h>
#include <stdlib.h>
#include <string.h>

int parse_args(int argc, char** argv, struct options* flags) {
  if (flags == NULL) return 1;
  bool first_pattern = false;
  for (int i = 1; i < argc; i++) {
    if (!strcmp(argv[i - 1], "-e") || (argv[i][0] != '-' && !first_pattern)) {
      flags->patters_number++;
      first_pattern = true;
    }
  }

  flags->patterns = malloc(sizeof(char*) * flags->patters_number);

  first_pattern = false;
  for (int i = 1, j = 0; i < argc; i++) {
    if (!strcmp(argv[i - 1], "-e") || (argv[i][0] != '-' && !first_pattern)) {
      flags->patterns[j] = argv[i];
      j++;

      first_pattern = true;
    }
  }

  const struct option opts[] = {{0, 0, 0, 'e'}, {0, 0, 0, 'i'}, {0, 0, 0, 'v'},
                                {0, 0, 0, 'c'}, {0, 0, 0, 'l'}, {0, 0, 0, 'n'},
                                {0, 0, 0, 0}};

  int ch = 0;

  while ((ch = getopt_long(argc, argv, "e:ivcln", opts, NULL)) != -1) {
    if (ch == 'e')
      flags->e = true;
    else if (ch == 'i')
      flags->i = true;
    else if (ch == 'v')
      flags->v = true;
    else if (ch == 'c')
      flags->c = true;
    else if (ch == 'l')
      flags->l = true;
    else if (ch == 'n')
      flags->n = true;
  }

  return 0;
}

void free_all(char** files, size_t count, options_t* flags,
              const char** filenames, size_t* files_len) {
  for (size_t i = 0; i < count; i++) free(files[i]);
  free(flags->patterns);
  free(files);
  free(files_len);
  free(filenames);
}

int compile_regex(regex_t* regex, const char* template, int reg_flags) {
  return regcomp(regex, template, reg_flags);
}

bool match_regex(regex_t* regex, size_t regex_number, const char* str) {
  for (size_t i = 0; i < regex_number; i++) {
    if (regexec(&(regex[i]), str, 0, NULL, 0) == 0) return true;
  }
  return false;
}