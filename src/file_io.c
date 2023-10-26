#include "file_io.h"

/* Get the contents of the file */
char* readFromFile(const char* path) {
  FILE* ptr;
  char ch;
  char* str;
  i32 length = 0;
  ptr = fopen(path, "r");
  ASSERT(ptr != 0);

  str = malloc(0);

  while (!feof(ptr)) {
    ch = fgetc(ptr);
    str = realloc(str, ++length);
    str[length-1] = ch;
  }
  fclose(ptr);

  return str;
}

/* Write whatever the string contains to the file, wiping everything else */
void writeToFile(const char* path, const char* content) {
  FILE* ptr;
  ptr = fopen(path, "w");
  fprintf(ptr, "%s", content);
  fclose(ptr);
}
