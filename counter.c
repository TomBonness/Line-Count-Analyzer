// counter.c
#include "counter.h"
#include <stdio.h>
#include <string.h>

ExtCount ext_counts[MAX_TYPES];
int ext_count_size = 0;

int count_lines(const char *filepath) {
  FILE *file = fopen(filepath, "r");
  if (!file) {
    perror(filepath);
    return 0;
  }

  int lines = 0;
  char buffer[1024];
  while (fgets(buffer, sizeof(buffer), file)) {
    lines++;
  }

  fclose(file);
  return lines;
}

const char *get_extension(const char *filename) {
  const char *dot = strrchr(filename, '.');
  return (dot && dot[1]) ? dot : "unknown";
}

void update_counts(const char *ext, int lines) {
  for (int i = 0; i < ext_count_size; i++) {
    if (strcmp(ext_counts[i].ext, ext) == 0) {
      ext_counts[i].lines += lines;
      return;
    }
  }
  if (ext_count_size < MAX_TYPES) {
    strncpy(ext_counts[ext_count_size].ext, ext,
            sizeof(ext_counts[ext_count_size].ext));
    ext_counts[ext_count_size].lines = lines;
    ext_count_size++;
  }
}
