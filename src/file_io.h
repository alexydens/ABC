/*
 * This file just contains some basic Input/Output functions for files in C with
 * the stdlib.
 */

#if !defined(FILE_IO_H)
#define FILE_IO_H

/* Core */
#include <ABC/base.h>

/* Get the contents of the file */
char* readFromFile(const char* path);

/* Write whatever the string contains to the file, wiping everything else */
void writeToFile(const char* path, const char* content);

#endif /* FILE_IO_H */
