#ifndef STRING_H
#define STRING_H

#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>

// String functions

typedef struct String {
    char*  string;
    size_t length;
} String;

String* newString(const char* string);
void deleteString(String* string);
bool isValidString(String* string);

// String array functions

typedef struct StringArray {
    String** tokens;
    size_t   count;
} StringArray;

StringArray* newStringArray(size_t countArgs, ...);
void deleteStringArray(StringArray* stringlist);

#endif