#include "config.h"
#include "counter.h"
#include "scanner.h"
#include <stdio.h>
#include <string.h>

char *excluded_dirs[MAX_EXCLUDES];
int exclude_count = 0;

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
    return 1;
  }

  if (argc >= 3 && strncmp(argv[2], "--exclude=", 10) == 0) {
    char *list = argv[2] + 10; // skip "--exclude="
    char *token = strtok(list, ",");
    while (token && exclude_count < MAX_EXCLUDES) {
      excluded_dirs[exclude_count++] = token;
      token = strtok(NULL, ",");
    }
  }

  if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
    printf("Usage: %s <directory>\n", argv[0]);
    printf("Recursively scans a directory and counts lines per file type.\n");
    printf("Example: %s ./my_project\n", argv[0]);
    return 0;
  }

  scan_dir(argv[1]);

  printf("\n--- Summary ---\n");

  for (int i = 0; i < ext_count_size - 1; i++) {
    for (int j = 0; j < ext_count_size - i - 1; j++) {
      if (ext_counts[j].lines < ext_counts[j + 1].lines) {
        ExtCount temp = ext_counts[j];
        ext_counts[j] = ext_counts[j + 1];
        ext_counts[j + 1] = temp;
      }
    }
  }
  for (int i = 0; i < ext_count_size; i++) {
    printf("%s: %d lines\n", ext_counts[i].ext, ext_counts[i].lines);
  }

  int total = 0;
  for (int i = 0; i < ext_count_size; i++) {
    total += ext_counts[i].lines;
  }
  printf("Total: %d lines\n", total);

  printf("\n--- Breakdown by Percentage ---\n");
  for (int i = 0; i < ext_count_size; i++) {
    float percent = (ext_counts[i].lines / (float)total) * 100.0f;
    printf("%s: %d lines (%.1f%%)\n", ext_counts[i].ext, ext_counts[i].lines,
           percent);
  }

  return 0;
}
