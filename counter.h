#ifndef COUNTER_H
#define COUNTER_H

#define MAX_TYPES 100

typedef struct {
  char ext[16];
  int lines;
} ExtCount;

extern ExtCount ext_counts[MAX_TYPES];
extern int ext_count_size;

int count_lines(const char *filepath);
const char *get_extension(const char *filename);
void update_counts(const char *ext, int lines);

#endif
