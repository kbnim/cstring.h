#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "cstring.h"

const char DELIMITERS[] = " \t\n\v\f\r";
const char PUNCTUATION_MARKS[] = " ,.;:\t\n\v\f\r";

struct _string {
    char*  data;
    size_t length;
};

static void string_memory_allocation_error(void) {
    fprintf(stderr, "%s\n", CSTRING_MEMORY_ALLOCATION_ERROR_MESSAGE);
    exit(CSTRING_MEMORY_ALLOCATION_ERROR_CODE);
}

static void string_null_pointer_error(void) {
    fprintf(stderr, "%s\n", CSTRING_NULL_POINTER_ERROR_MESSAGE);
    exit(CSTRING_NULL_POINTER_ERROR_CODE);
}

static void string_out_of_bounds_error(void) {
    fprintf(stderr, "%s\n", CSTRING_STRING_LENGTH_OUT_OF_BOUNDS_ERROR_MESSAGE);
    exit(CSTRING_STRING_LENGTH_OUT_OF_BOUNDS_ERROR_CODE);
}

static void strarr_index_out_of_bounds_error(void) {
    fprintf(stderr, "%s\n", CSTRING_STRARR_INDEX_OUT_OF_BOUNDS_ERROR_MESSAGE);
    exit(CSTRING_STRARR_INDEX_OUT_OF_BOUNDS_ERROR_CODE);
}

const char* string_get_data(const string* str) {
    return str->data;
}

size_t string_get_length(const string* str) {
    return str->length;
}

string* new_string(const char* source) {
    if (!source) string_null_pointer_error();

    size_t length = strlen(source);
    string* str = calloc(1, sizeof(string));
    
    if (!str) string_memory_allocation_error();

    str->length = length;
    str->data = calloc(length + 1, sizeof(char));

    if (!(str->data)) string_memory_allocation_error();

    strcpy(str->data, source);
    return str;
}

void delete_string(string* str) {
    if (str) {
        free(str->data);
        free(str);
        str = NULL;
    }
}

bool string_isvalid(const string* str) {
    if (!str) string_null_pointer_error();
    return str->data[str->length] == '\0';
}

int string_compare(const string* str1, const string* str2) {
    if (!str1 || !str2) string_null_pointer_error();
    return strcmp(str1->data, str2->data);
}

bool string_areequal(const string* str1, const string* str2) {
    if (!str1 || !str2) string_null_pointer_error();
    return strcmp(str1->data, str2->data) == 0;
}

string* string_concatenate(const string* str1, const string* str2) {
    if (!str1 || !str2) string_null_pointer_error();

    size_t length = str1->length + str2->length;
    char proto_string[length + 1];

    for (size_t index = 0; index < length; index++) {
        if (index < str1->length) {
            proto_string[index] = str1->data[index];
        } else {
            proto_string[index] = str2->data[index - str1->length];
        }
    }

    proto_string[length] = '\0';

    return new_string(proto_string);
}

string* string_substring(const string* str, const size_t start_index, const size_t end_index) {
    if (!str) string_null_pointer_error();
    if (end_index >= str->length) string_out_of_bounds_error();

    size_t length = end_index - start_index + 1;
    char proto_string[length + 1];

    for (size_t i = 0; i < length; i++) {
        proto_string[i] = str->data[start_index + i];
    }

    proto_string[length] = '\0';

    return new_string(proto_string);
}

bool string_issubstring(const string* str, const string* substr) {
    if (!str || !substr) string_null_pointer_error();

    char buffer_string[substr->length + 1];
    buffer_string[substr->length] = '\0';
    size_t first_occurrence = 0;
    size_t occurrences = 0;

    for (size_t i = 0; i < str->length; i++) {
        if (str->data[i] == substr->data[first_occurrence]) {
            buffer_string[first_occurrence] = str->data[i];
            first_occurrence++;
            occurrences++; 
        }
    }

    return strcmp(substr->data, buffer_string) == 0;
}

char* string_strchr(const string* str, char character) {
    if (!str) string_null_pointer_error();
    return strchr(str->data, character);
}

bool string_contains_char(const string* str, const char character) {
    if (!str) string_null_pointer_error();
    return strchr(str->data, character) != NULL;
}

string* string_read(FILE* source, const char* delimiters) {
    if (feof(source)) return NULL;

    size_t index = 0; 
    size_t size = 2;
    int character;
    char* buffer = malloc(size * sizeof(char));

    if (!buffer) string_memory_allocation_error();

    character = getc(source);

    while (character != EOF && strchr(delimiters, character) == NULL) {
        if (index >= size - 1) {
            size *= 2;
            buffer = realloc(buffer, size * sizeof(char));
            for (size_t i = index; i < size; i++) buffer[i] = '\0';
        }

        buffer[index] = character;
        index++;
        character = getc(source);
    }

    buffer[index] = '\0';
    string* output = new_string(buffer);
    free(buffer);

    return output;
}

string* string_read_line(void) {
    return string_read(stdin, "\n");
}

string* string_read_word(void) {
    return string_read(stdin, " ");
}

// string array

typedef struct _strnode {
    string* str;
    size_t index;
    strnode* next;
} strnode;

static strnode* new_strnode(const char* source) {
    if (!source) string_null_pointer_error();

    strnode* node = calloc(1, sizeof(strnode));

    if (!node) string_memory_allocation_error();

    node->index = 0;
    node->next = NULL;
    node->str = new_string(source);
    
    return node;
}

static void delete_strnode(strnode* node) {
    if (node) {
        delete_string(node->str);
        free(node);
        node = NULL;
    }
}

string* strnode_get_string(const strnode* node) {
    return node->str;
}

const char* strnode_get_data(const strnode* node) {
    return node->str->data;
}

size_t strnode_get_length(const strnode* node) {
    return node->str->length;
}

strnode* strnode_get_next(const strnode* node) {
    return node->next;
}

size_t strnode_get_index(const strnode* node) {
    return node->index;
}

typedef struct _strarr {
    strnode* first;
    strnode* last;
    size_t count;
} strarr;

strarr* new_strarr(void) {
    strarr* array = calloc(1, sizeof(strarr));

    if (!array) string_memory_allocation_error();

    array->first = NULL;
    array->last = NULL;
    array->count = 0;
    
    return array;
}

void delete_strarr(strarr* arr) {
    if (arr) {
        strnode* node;
        
        while(arr->first && arr->last) {
            node = arr->first;
            arr->first = arr->first->next;
            node->next = NULL;
            delete_strnode(node);
        }

        free(arr);
        arr = NULL;
    }
}

size_t strarr_get_count(const strarr* arr) {
    return arr->count;
}

strnode* strarr_get_first(const  strarr* arr) {
    if (!arr) string_null_pointer_error();
    return arr->first;
}

void strarr_append(const  string* str, strarr** arr) {
    if (!str || !arr) string_null_pointer_error();

    strarr* array = *arr;
    strnode* node = new_strnode(str->data);

    if (!array->first && !array->last) {
        array->first = node;
        array->last = array->first;
    } else {
        node->index = array->count;
        array->last->next = node;
        array->last = array->last->next;
    }

    array->count++;
    *arr = array;
}

void strarr_prepend(const string* str, strarr** arr) {
    if (!str || !arr) string_null_pointer_error();

    strarr* array = *arr;
    strnode* node = new_strnode(str->data);

    if (!array->first && !array->last) {
        array->first = node;
        array->last = array->first;
    } else {
        strnode* iterator = array->first;
        node->next = array->first;
        array->first = node;

        while (iterator) {
            iterator->index++;
            iterator = iterator->next;
        }
    }

    array->count++;
    *arr = array;
}

static bool strarr_check_index(const size_t index, const strarr* arr) {
    return index < arr->count;
}

void strarr_insert_at(const string* str, const size_t index, strarr** arr) {
    if (!str || !arr) string_null_pointer_error();

    strarr* array = *arr;

    if (!strarr_check_index(index, array)) strarr_index_out_of_bounds_error();
    
    strnode* preceding = NULL;
    strnode* iterator = array->first;

    while (iterator && iterator->index != index) {
        preceding = iterator;
        iterator = iterator->next;
    }

    strnode* node_at_index = new_strnode(str->data);
    preceding->next = node_at_index;
    node_at_index->index = index;
    node_at_index->next = iterator;

    while (iterator) {
        iterator->index++;
        iterator = iterator->next;
    }

    *arr = array;
}

string* strarr_remove_last(strarr** arr) {
    if (!arr) string_null_pointer_error();

    strarr* array = *arr;

    if (array->count == 0) {
        fprintf(stderr, "%s\n", CSTRING_STRARR_EMPTY_ARRAY_REMOVE_WARNING);
        return NULL;
    }

    strnode* last_to_remove = array->last;
    last_to_remove->index = 0;
    array->count--;

    strnode* preceding = NULL;
    strnode* iterator = array->first;

    while (iterator && iterator != last_to_remove) {
        preceding = iterator;
        iterator = iterator->next;
    }

    preceding->next = NULL;
    array->last = preceding;
    string* string_to_remove = new_string(last_to_remove->str->data);
    delete_strnode(last_to_remove);
    *arr = array;
    return string_to_remove;
}

string* strarr_remove_first(strarr** arr) {
    if (!arr) string_null_pointer_error();

    strarr* array = *arr;

    if (array->count == 0) {
        fprintf(stderr, "%s\n", CSTRING_STRARR_EMPTY_ARRAY_REMOVE_WARNING);
        return NULL;
    }

    strnode* first_to_remove = array->first;
    array->first = array->first->next;
    first_to_remove->next = NULL;
    first_to_remove->index = 0;
    array->count--;
    string* string_to_remove = new_string(first_to_remove->str->data);
    delete_strnode(first_to_remove);

    for (strnode* i = array->first; i != NULL; i = i->next) {
        i->index--;
    }

    *arr = array;
    return string_to_remove;
}

string* strarr_remove_at(const size_t index, strarr** arr) {
    if (!arr) string_null_pointer_error();

    strarr* array = *arr;

    if (array->count == 0) {
        fprintf(stderr, "%s\n", CSTRING_STRARR_EMPTY_ARRAY_REMOVE_WARNING);
        return NULL;
    }

    if (!strarr_check_index(index, array)) strarr_index_out_of_bounds_error();

    strnode* preceding = NULL;
    strnode* iterator = array->first;

    while (iterator && iterator->index != index) {
        preceding = iterator;
        iterator = iterator->next;
    }

    strnode* item_to_remove = iterator;
    iterator = iterator->next;
    preceding->next = iterator;
    item_to_remove->next = NULL;
    array->count--;

    while (iterator) {
        iterator->index--;
        iterator = iterator->next;
    }

    string* string_to_remove = new_string(item_to_remove->str->data);
    delete_strnode(item_to_remove);
    *arr = array;
    return string_to_remove;
}