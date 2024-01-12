#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int merge_files_cat(const char** filenames, size_t count, size_t* files_len,
                    char** out) {
  for (size_t i = 0; i < count; i++) {
    size_t filesize = read_file(filenames[i], 0, 0);
    char* buffer = calloc(filesize + 1, sizeof(char));

    if (read_file(filenames[i], buffer, filesize) == 0) {
      printf("s21_cat: %s: No such file or directory\n", filenames[i]);
      free(buffer);
    } else {
      files_len[i] = filesize;
      out[i] = buffer;
    }
  }
  return 0;
}

int merge_files_grep(const char** filenames, size_t count, size_t* files_len,
                     char** out) {
  for (size_t i = 0; i < count; i++) {
    size_t filesize = read_file(filenames[i], 0, 0) + 1;
    char* buffer = calloc(filesize, sizeof(char));

    if (read_file(filenames[i], buffer, filesize) == 0) {
      printf("s21_grep: %s: No such file or directory\n", filenames[i]);
      free(buffer);
    } else {
      files_len[i] = filesize;
      out[i] = buffer;
    }
  }
  return 0;
}

size_t get_filenames_cat(int argc, char** argv, const char** filenames,
                         size_t len) {
  if (filenames == NULL) {
    size_t _len = 0;
    for (int i = 1; i < argc; i++) {
      if (argv[i][0] != '-') _len++;
    }
    return _len;
  }

  for (int i = 1, j = 0; i < argc; i++) {
    if (argv[i][0] != '-') {
      filenames[j] = argv[i];
      j++;
    }
  }

  return len;
}

size_t get_filenames_grep(int argc, char** argv, const char** filenames,
                          size_t len) {
  if (filenames == NULL) {
    size_t _len = 0;

    bool first_pattern = false;
    for (int i = 1; i < argc; i++) {
      if (!strcmp(argv[i - 1], "-e") || (argv[i][0] != '-' && !first_pattern))
        first_pattern = true;
      else if (argv[i][0] != '-' && first_pattern)
        _len++;
    }
    return _len;
  }

  bool first_pattern = false;
  for (int i = 1, j = 0; i < argc; i++) {
    if (!strcmp(argv[i - 1], "-e") || ((argv[i][0] != '-') && !first_pattern)) {
      first_pattern = true;
    } else if ((argv[i][0] != '-') && first_pattern) {
      filenames[j] = argv[i];
      j++;
    }
  }
  return len;
}

size_t read_file(const char* name, char* out, size_t bytes) {
  FILE* file = fopen(name, "r");
  if (file == NULL) return 0;

  if (out == NULL) {
    fseek(file, 0, SEEK_END);
    size_t filesize = ftell(file);
    fseek(file, 0, SEEK_SET);
    fclose(file);
    return filesize;
  }

  size_t read = fread(out, sizeof(char), bytes, file);

  fclose(file);
  return read;
}