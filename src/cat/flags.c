#include "flags.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void process_e(char** file, size_t* file_len) {
  process_E(file, file_len);
  process_v(file, file_len);
}

void process_t(char** file, size_t* file_len) {
  process_T(file, file_len);
  process_v(file, file_len);
}

void process_b(char** file, size_t* file_len) {
  size_t outlen = *file_len + 7;
  for (size_t i = 1; i < *file_len; i++)
    if ((*file)[i - 1] == '\n')
      if ((*file)[i] != '\n') outlen += 7;

  char* buffer = calloc(outlen + 1, sizeof(char));
  size_t j = 0;

  unsigned long line_number = 2;

  j += sprintf(buffer + j, "%6lu\t%c", 1lu, (*file)[0]);
  for (size_t i = 1; i < *file_len; i++) {
    if ((*file)[i - 1] == '\n') {
      if ((*file)[i] == '\n') {
        j += sprintf(buffer + j, "%c", (*file)[i]);
      } else {
        j += sprintf(buffer + j, "%6lu\t%c", line_number, (*file)[i]);
        line_number++;
      }
    } else
      j += sprintf(buffer + j, "%c", (*file)[i]);
  }

  *file_len = outlen;

  free(*file);
  *file = buffer;
}

void process_E(char** file, size_t* file_len) {
  size_t outlen = *file_len;

  for (size_t i = 0; i < *file_len; i++) {
    if ((*file)[i] == '\n') outlen++;
  }

  char* buffer = calloc(outlen + 1, sizeof(char));
  size_t j = 0;

  for (size_t i = 0; i < *file_len; i++) {
    if ((*file)[i] == '\n')
      j += sprintf(buffer + j, "$\n");
    else
      j += sprintf(buffer + j, "%c", (*file)[i]);
  }
  *file_len = outlen;

  free(*file);
  (*file) = buffer;
}

void process_n(char** file, size_t* file_len) {
  size_t outlen = *file_len + 7;

  for (size_t i = 1; i < *file_len; i++) {
    if ((*file)[i - 1] == '\n') outlen += 7;
  }

  char* buffer = calloc(outlen + 1, sizeof(char));
  size_t j = 0;

  unsigned long line_number = 2;

  j += sprintf(buffer, "%6lu\t%c", 1lu, (*file)[0]);
  for (size_t i = 1; i < *file_len; i++) {
    if ((*file)[i - 1] == '\n') {
      j += sprintf(buffer + j, "%6lu\t%c", line_number, (*file)[i]);
      line_number++;
    } else
      j += sprintf(buffer + j, "%c", (*file)[i]);
  }

  *file_len = outlen;

  free(*file);
  (*file) = buffer;
}

void process_s(char** file, size_t* file_len) {
  size_t outlen = 0;

  int slash_n = 0;
  for (size_t i = 0; i < *file_len + 1; i++) {
    if ((*file)[i] == '\n')
      slash_n++;
    else
      slash_n = 0;
    if (slash_n >= 3) continue;
    outlen++;
  }

  outlen--;

  char* buffer = calloc(outlen + 1, sizeof(char));
  size_t j = 0;

  slash_n = 0;
  for (size_t i = 0; i < *file_len; i++) {
    if ((*file)[i] == '\n')
      slash_n++;
    else
      slash_n = 0;
    if (slash_n >= 3) continue;
    j += sprintf(buffer + j, "%c", (*file)[i]);
  }

  *file_len = outlen;

  free(*file);
  (*file) = buffer;
}

void process_T(char** file, size_t* file_len) {
  size_t outlen = *file_len;

  for (size_t i = 0; i < *file_len; i++) {
    if ((*file)[i] == '\t') outlen++;
  }

  char* buffer = calloc(outlen + 1, sizeof(char));
  size_t j = 0;

  for (size_t i = 0; i < *file_len; i++) {
    if ((*file)[i] == '\t')
      j += sprintf(buffer + j, "^I");
    else
      j += sprintf(buffer + j, "%c", (*file)[i]);
  }

  *file_len = outlen;

  free(*file);
  (*file) = buffer;
}

void process_v(char** file, const size_t* file_len) {
  for (size_t i = 0; i < *file_len; i++) {
    char ch = (*file)[i];
    if (isprint(ch) || ch == '\n' || ch == '\t')
      printf("%c", ch);
    else if (iscntrl(ch)) {
      // print control symbol (caret notation)
      printf("^");
      if (ch == 127) {
        printf("%c", ch - 64);
      } else {
        printf("%c", ch + 64);
      }
    } else {
      // print meta symbols (M- notation)
      const char meta_symbol = (char)((signed char)ch + 128);
      printf("M-");
      if (isprint((unsigned char)meta_symbol)) {
        printf("%c", meta_symbol);
      } else {
        printf("^");
        if (ch == 127) {
          printf("%c", ch - 64);
        } else {
          printf("%c", ch + 64);
        }
      }
    }
  }
}
