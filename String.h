#ifndef STRING_H
#define STRING_H

#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>

static const char DELIMITERS[] = " \t\n\v\f\r";
static const char PUNCTUATION_MARKS[] = " ,.;:\t\n\v\f\r";

// String functions

typedef struct String {
    char*  string;
    size_t length;
} String;

String* newString(const char* string);
void deleteString(String* string);
bool isValidString(String* string);
int stringCompare(String* string01, String* string02);
bool isDelimiter(char character, String* delimiters);
String* stringSegment(String* string, size_t indexStart, size_t indexEnd);
String* readString(FILE* source, char* delimiters);
String* readStringWord();
String* readStringLine();

// String array functions

typedef struct StringArray {
    String** tokens;
    size_t   count;
} StringArray;

StringArray* newStringArray(size_t countArgs, ...);
void deleteStringArray(StringArray* stringlist);
StringArray* splitString(const char* string, const char* separators);
size_t countTokens(String* string, String* separators);
void printStringArray(StringArray* array, bool index);

// String list (C2L) functions

typedef struct StringH1L {
    String*    node;
    size_t     index;
    struct StringH1L* next;
} StringH1L;

typedef struct StringList {
    StringH1L* head;
    size_t     count;
} StringList;

StringH1L* newStringH1L(const char* string, size_t index);
StringList* newStringList();
void deleteStringList(StringList* list);
void appendToList (StringList* list, const char* string);
void prependToList(StringList* list, const char* string);
void insertToList (StringList* list, const char* string, size_t index);
void refactorIndices(StringList* list);
StringH1L* listElemAtIndex(StringList* list, size_t index);
String* listAtIndex(StringList* list, size_t index);
void printStringList(StringList* list, bool index);
void removeFromList(StringList* list, size_t index);

#endif