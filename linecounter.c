#include <dirent.h>   // opendir, readdir, closedir
#include <limits.h>   // PATH_MAX
#include <stdio.h>    // printf, perror, snprintf
#include <stdlib.h>   // malloc, free (if needed)
#include <string.h>   // strcmp, strrchr
#include <sys/stat.h> // stat, S_ISDIR, S_ISREG

void scan_dir(const char *path) {
  DIR *dir = opendir(path);
  if (!dir) {
    perror("opendir");
    return;
  }

  struct dirent *entry;
  while ((entry = readdir(dir)) != NULL) {
    // skip . and ..
    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
      continue;

    // build full path: path + "/" + entry->d_name
    char full_path[PATH_MAX];
    snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

    struct stat st;
    if (stat(full_path, &st) == -1) {
      perror("stat");
      continue;
    }

    if (S_ISDIR(st.st_mode)) {
      // recurse into directory
      scan_dir(full_path);
    } else if (S_ISREG(st.st_mode)) {
      printf("File: %s\n", full_path); // placeholder only to check if it's
                                       // working - remove later
      // this is checking to see if it's a regular file
      // TODO: call count_lines(full_path) and update counters
    }
  }

  closedir(dir);
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
    return 1;
  }

  scan_dir(argv[1]); // Pass the directory you want to scan
  return 0;
}
