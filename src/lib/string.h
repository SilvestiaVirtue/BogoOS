#ifndef STRING_H
#define STRING_H

#include "lib/stdint.h"


size_t strlen(const char* str);
int strcmp(const char* str1, const char* str2);
char* strcpy(char* dest, const char* src);
void* memset(void* dest, int val, size_t len);
void* memcpy(void* dest, const void* src, size_t len);
char* strchr(const char *s, int c);
char* strlok(char* str, const char *separator);
int getopt(int argc, char* argv[], char* optstring);

#endif
