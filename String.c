#include <stdlib.h>
#include <string.h>

#include "String.h"

// String functions

String* newString(const char* string) {
    String* newString = calloc(1, sizeof(String));

    if (newString == NULL) {
        perror("Memory allocation failed");
        return NULL;
    }

    if (string != NULL) {
        newString->length = strlen(string);
        newString->string = calloc(newString->length + 1, sizeof(char));
        strcpy(newString->string, string);
    }
    
    return newString;
}

void deleteString(String* string) {
    free(string->string);
    free(string);
}

bool isValidString(String* string) {
    return string->string[string->length] == '\0';
}

// String array functions

StringArray* newStringArray(size_t countArgs, ...) {
    StringArray* stringarray = calloc(1, sizeof(StringArray));

    if (stringarray == NULL) {
        perror("Memory allocation failed");
        return NULL;
    }

    stringarray->count  = countArgs;
    stringarray->tokens = calloc(countArgs, sizeof(String*));

    if (stringarray->tokens == NULL) {
        perror("Memory allocation failed");
        return NULL;
    }

    va_list arguments;
    va_start(arguments, countArgs);

    for (size_t i = 0; i < countArgs; i++) {
        stringarray->tokens[i] = va_arg(arguments, String*);
    }

    va_end(arguments);
    return stringarray;
}

void deleteStringArray(StringArray* stringarray) {
    for (size_t i = 0; i < stringarray->count; i++) {
        deleteString(stringarray->tokens[i]);
    }

    free(stringarray->tokens);
    free(stringarray);
}