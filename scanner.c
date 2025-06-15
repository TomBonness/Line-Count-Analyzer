#include "scanner.h"
#include "config.h"
#include "counter.h"

#include <dirent.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void scan_dir(const char *path) {
  DIR *dir = opendir(path);
  if (!dir) {
    perror("opendir");
    return;
  }

  struct dirent *entry;
  while ((entry = readdir(dir)) != NULL) {
    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
      continue;

    char full_path[PATH_MAX];
    snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

    struct stat st;
    if (stat(full_path, &st) == -1) {
      perror("stat");
      continue;
    }

    if (S_ISDIR(st.st_mode)) {
      int skip = 0;
      for (int i = 0; i < exclude_count; i++) {
        if (strcmp(entry->d_name, excluded_dirs[i]) == 0) {
          skip = 1;
          break;
        }
      }
      if (skip)
        continue;
      scan_dir(full_path);
    } else if (S_ISREG(st.st_mode)) {
      int line_count = count_lines(full_path);
      const char *ext = get_extension(full_path);
      if (strcmp(ext, ".o") == 0 || strcmp(ext, ".so") == 0 ||
          strcmp(ext, ".a") == 0 || strcmp(ext, ".exe") == 0 ||
          strcmp(ext, ".class") == 0 || strcmp(ext, ".out") == 0 ||
          strcmp(ext, ".bin") == 0) {
        continue;
      }
      update_counts(ext, line_count);
    }
  }

  closedir(dir);
}
