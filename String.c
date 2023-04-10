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

    newString->length = strlen(string);
    newString->string = calloc(newString->length + 1, sizeof(char));
    strcpy(newString->string, string);
    
    return newString;
}

void deleteString(String* string) {
    if (string != NULL) {
        free(string->string);
        free(string);
    }
}

bool isValidString(String* string) {
    return string->string[string->length] == '\0';
}

int stringCompare(String* string01, String* string02) {
    return strcmp(string01->string, string02->string);
}

bool isDelimiter(char character, String* delimiters) {
    return strchr(delimiters->string, character) != NULL;
}

String* stringSegment(String* string, size_t indexStart, size_t indexEnd) {
    if (!((indexStart <= indexEnd) && (indexEnd < string->length))) {
        perror("Invalid string indices");
        return NULL;
    }

    String* segment = calloc(1, sizeof(String));

    if (segment == NULL) {
        perror("Memory allocation failed");
        return NULL;
    }

    segment->length = indexEnd - indexStart + 1;
    segment->string = calloc(segment->length + 1, sizeof(char));

    if (segment->string == NULL) {
        perror("Memory allocation failed");
        return NULL;
    }

    for (size_t i = 0; i < segment->length; i++) {
        segment->string[i] = string->string[indexStart + i];
    }

    segment->string[segment->length] = '\0';
    return (isValidString(segment)) ? segment : NULL;
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
    if (stringarray != NULL) {
        for (size_t i = 0; i < stringarray->count; i++) {
            deleteString(stringarray->tokens[i]);
        }

        free(stringarray->tokens);
        free(stringarray);
    }
}

size_t countTokens(String* string, String* separators) {
    size_t countTokens = 0;
    size_t index = 0;
    bool isToken = false;

    while (index <= string->length || isToken) {
        if (isDelimiter(string->string[index], separators)) isToken = false;
        else if (!isDelimiter(string->string[index], separators) && !isToken) {
            isToken = true;
            countTokens++;
        }
        index++;
    }

    return countTokens;
}

StringArray* splitString(const char* string0, const char* separators0) {
    String* string = newString(string0);
    String* separators = newString(separators0);
    size_t count = countTokens(string, separators);
    printf("%lu\n", count);
    StringArray* stringarray = calloc(1, sizeof(StringArray));

    if (stringarray == NULL) {
        perror("Memory allocation failed");
        return NULL;
    }

    stringarray->count  = count;
    stringarray->tokens = calloc(count, sizeof(String*));

    if (stringarray->tokens == NULL) {
        perror("Memory allocation failed");
        return NULL;
    }

    size_t indexStart = 0;
    size_t indexEnd = 0;
    size_t tokenIndex = 0;

    while ((indexEnd < (string->length)) && (tokenIndex < count)) {
        if (isDelimiter(string->string[indexEnd], separators) 
        && !isDelimiter(string->string[indexEnd + 1], separators)) {
            indexStart = indexEnd + 1;
        } else if (!isDelimiter(string->string[indexEnd], separators) 
        && isDelimiter(string->string[indexEnd + 1], separators)) {
            stringarray->tokens[tokenIndex] = stringSegment(string, indexStart, indexEnd);
            tokenIndex++;
        }
        
        indexEnd++;
    }

    deleteString(string);
    deleteString(separators);
    return stringarray;
}

// String list functions

StringH1L* newStringH1L(const char* string, size_t index) {
    StringH1L* newElement = calloc(1, sizeof(StringH1L));

    if (newElement == NULL) {
        perror("Memory allocation failed");
        return NULL;
    }

    newElement->node  = newString(string);
    newElement->index = index;
    newElement->next  = NULL;
    return newElement;
}

StringList* newStringList() {
    StringList* list = calloc(1, sizeof(StringList));

    if (list == NULL) {
        perror("Memory allocation failed");
        return NULL;
    }

    list->count = 0;
    list->head = NULL;
    return list;
}

void deleteStringList(StringList* list) {
    if (list == NULL) {
        return;
    }
    
    StringH1L* current = list->head;
    
    while (current != NULL) {
        StringH1L* next = current->next;
        deleteString(current->node);
        free(current);
        current = next;
    }
    
    free(list);
}

void appendToList(StringList* list, const char* string) {
    if (list == NULL) {
        return;
    }
    
    StringH1L* node = newStringH1L(string, list->count);
    
    if (node == NULL) {
        return;
    }

    if (list->head == NULL) {
        list->head = node;
    } else {
        StringH1L* current = list->head;

        while (current->next != NULL) {
            current = current->next;
        }
        
        current->next = node;
    }

    list->count++;
}

String* listAtIndex(StringList* list, size_t index) {
    if (index >= list->count) {
        perror("List index out of bounds");
        return NULL;
    }

    StringH1L* stringAtIndex = list->head;

    while (stringAtIndex != NULL) {
        if (stringAtIndex->index == index) return stringAtIndex->node;
        stringAtIndex = stringAtIndex->next;
    }

    return NULL;
}
