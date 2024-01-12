#include "utils.h"

#include <getopt.h>
#include <memory.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "flags.h"

int parse_args(int argc, char **argv, struct options *flags) {
  if (flags == NULL) return 1;

  const struct option opts[] = {{"number-nonblank", 0, 0, 'b'},
                                {0, 0, 0, 'e'},
                                {"number", 0, 0, 'n'},
                                {"squeeze-blank", 0, 0, 's'},
                                {"show-ends", 0, 0, 't'},
                                {0, 0, 0, 'E'},
                                {"show-nonprinting", 0, 0, 'v'},
                                {"show-tabs", 0, 0, 'T'},
                                {0, 0, 0, 0}};

  int ch = 0;

  while ((ch = getopt_long(argc, argv, "beEnstTv", opts, NULL)) != -1) {
    if (ch == 'b')
      flags->number_nonblank = true;
    else if (ch == 'e')
      flags->e = true;
    else if (ch == 'E')
      flags->E = true;
    else if (ch == 'n')
      flags->number = true;
    else if (ch == 's')
      flags->squeeze_blank = true;
    else if (ch == 't')
      flags->show_ends = true;
    else if (ch == 'T')
      flags->show_tabs = true;
    else if (ch == 'v')
      flags->show_nonprinting = true;
  }

  return 0;
}

void filter_flags(struct options *flags) {
  if (flags->number_nonblank) flags->number = false;
}

void process_files(struct options flags, char **files, size_t files_count,
                   size_t *files_len) {
  for (size_t i = 0; i < files_count; i++) {
    if (files[i] == 0) continue;

    if (flags.show_ends) {
      process_t(&files[i], &files_len[i]);
    }
    if (flags.show_tabs) {
      process_T(&files[i], &files_len[i]);
    }
    if (flags.squeeze_blank) {
      process_s(&files[i], &files_len[i]);
    }
    if (flags.number_nonblank) {
      process_b(&files[i], &files_len[i]);
    }
    if (flags.e) {
      process_e(&files[i], &files_len[i]);
    }
    if (flags.E) {
      process_E(&files[i], &files_len[i]);
    }
    if (flags.number) {
      process_n(&files[i], &files_len[i]);
    }
    if (flags.show_nonprinting) {
      process_v(&files[i], &files_len[i]);
    }
  }

  if (!flags.show_nonprinting && !flags.show_ends && !flags.e) {
    for (size_t i = 0; i < files_count; i++) {
      for (size_t j = 0; j < files_len[i]; j++) {
        printf("%c", files[i][j]);
      }
    }
  }
}