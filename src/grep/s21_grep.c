#define _POSIX_C_SOURCE 200809L
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

int process(regex_t* regex, const char* token, options_t flags,
            const char* filename, size_t* lines_c, size_t* line_number,
            bool* breaked, bool print_filename);
int grep(const char** filenames, char** files, size_t count, options_t flags);

int main(int argc, char** argv) {
  options_t flags = {};

  size_t count = get_filenames_grep(argc, argv, 0, 0);

  const char** filenames = calloc(count, sizeof(char*));
  if (filenames == NULL) {
    printf("s21_grep: unable to allocate memory");
    return 1;
  }

  get_filenames_grep(argc, argv, filenames, count);
  parse_args(argc, argv, &flags);

  if (count < 1) {
    free(filenames);
    free(flags.patterns);
    return 1;
  }

  char** files = calloc(count, sizeof(char*));
  if (files == NULL) {
    printf("s21_grep: unable to allocate memory");
    free(flags.patterns);
    return 1;
  }

  size_t* files_len = calloc(count, sizeof(size_t));
  if (files_len == NULL) {
    printf("s21_grep: unable to allocate memory");
    free(files);
    free(flags.patterns);
    return 1;
  }

  if (merge_files_grep(filenames, count, files_len, files)) return 1;

  if (grep(filenames, files, count, flags)) printf("error");

  free_all(files, count, &flags, filenames, files_len);

  return 0;
}

int process(regex_t* regex, const char* token, options_t flags,
            const char* filename, size_t* lines_c, size_t* line_number,
            bool* breaked, bool print_filename) {
  int result = match_regex(regex, flags.patters_number, token);
  if (flags.v) result = !result;

  if (result) {
    if (print_filename && !flags.l && !flags.c) printf("%s:", filename);
    if (flags.n && !flags.l && !flags.c) printf("%zu:", *line_number);
    if (!flags.l && !flags.c)
      printf("%s\n", token);
    else
      (*lines_c)++;

    if (flags.l) {
      // printf("%s\n", filename);
      *breaked = true;
    }
  }

  (*line_number)++;
  return result;
}

int grep(const char** filenames, char** files, size_t count, options_t flags) {
  regex_t* regex = calloc(flags.patters_number, sizeof(regex_t));
  if (regex == NULL) return 1;

  int reg_flags = REG_EXTENDED;

  if (flags.i) reg_flags |= REG_ICASE;

  for (size_t i = 0; i < flags.patters_number; i++) {
    if (compile_regex(&(regex[i]), flags.patterns[i], reg_flags)) {
      printf("Regex error");
      return 1;
    }
  }

  for (size_t i = 0; i < count; i++) {
    if (files[i] == 0) continue;
    char* buffer = files[i];
    char delimiter = '\n';
    char* token = buffer;

    size_t lines_c = 0;
    size_t line_number = 1;
    bool breaked = false;
    const bool print_filename = count > 1 ? true : false;
    int result = 0;

    for (char* ptr = buffer; *ptr != '\0'; ptr++) {
      if (*ptr == delimiter) {
        *ptr = '\0';

        result = process(regex, token, flags, filenames[i], &lines_c,
                         &line_number, &breaked, print_filename);
        if (breaked) break;

        token = ptr + 1;
      }
    }

    if (!breaked) {
      if (token[0] != '\0')
        result = process(regex, token, flags, filenames[i], &lines_c,
                         &line_number, &breaked, print_filename);
    }

    if (flags.c) {
      if (print_filename) printf("%s:", filenames[i]);
      printf("%zu\n", lines_c);
    }
    if (flags.l && result) {
      printf("%s\n", filenames[i]);
      //*breaked = true;
    }
  }

  for (size_t i = 0; i < flags.patters_number; i++) regfree(&(regex[i]));
  free(regex);
  return 0;
}