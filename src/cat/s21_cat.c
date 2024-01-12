#define _POSIX_C_SOURCE 200809L

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "flags.h"
#include "utils.h"

int main(int argc, char **argv) {
  struct options flags = {};

  if (parse_args(argc, argv, &flags)) fprintf(stderr, "error");

  filter_flags(&flags);

  const char **filenames = 0;
  size_t count = get_filenames_cat(argc, argv, 0, 0);

  filenames = calloc(count, sizeof(char *));
  get_filenames_cat(argc, argv, filenames, count);

  char **files = calloc(count, sizeof(char *));
  size_t *files_len = calloc(count, sizeof(size_t));
  if (merge_files_cat(filenames, count, files_len, files)) return 1;

  process_files(flags, files, count, files_len);

  free(filenames);

  for (size_t i = 0; i < count; i++) free(files[i]);
  free(files_len);
  free(files);
  return 0;
}