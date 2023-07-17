#ifndef CSTRING_H
#define CSTRING_H

#include <stddef.h>
#include <stdbool.h>

// Constant array storing all (possible) delimiters.
extern const char DELIMITERS[];

// Constant array storing all (possible) punctuation marks.
extern const char PUNCTUATION_MARKS[];

// error messages and their respective error codes

#define CSTRING_NULL_POINTER_ERROR_MESSAGE "Error: uninstantiated string (i.e. null pointer)."
#define CSTRING_NULL_POINTER_ERROR_CODE -1

#define CSTRING_MEMORY_ALLOCATION_ERROR_MESSAGE "Error: memory allocation failed."
#define CSTRING_MEMORY_ALLOCATION_ERROR_CODE -2

#define CSTRING_STRING_LENGTH_OUT_OF_BOUNDS_ERROR_MESSAGE "Error: index is out of bounds of string's length."
#define CSTRING_STRING_LENGTH_OUT_OF_BOUNDS_ERROR_CODE -3

#define CSTRING_STRARR_INDEX_OUT_OF_BOUNDS_ERROR_MESSAGE "Error: array index is out of bounds."
#define CSTRING_STRARR_INDEX_OUT_OF_BOUNDS_ERROR_CODE -4

// warning messages (note that they do not terminate thet program, only the respective function)

#define CSTRING_STRARR_EMPTY_ARRAY_REMOVE_WARNING "Warning: no element can be removed from an empty array / list."

// Definition of type 'string'
typedef struct _string string;

// Getter to extract the underlying array of char's.
// Note that the individual characters are immutable.
const char* string_get_data(const string* str);

// Getter for the length of the string.
// Note that the length is immutable.
size_t string_get_length(const string* str);

// Constructor of type 'string'
string* new_string(const char* source);

// Destructor of type 'string'
void delete_string(string* str);

// Checks whether the string's last character is '\0'.
bool string_isvalid(const string* str);

// Works the same way as strcmp().
int string_compare(const string* str1, const string* str2);

// Checks whether the two strings are equal.
bool string_areequal(const string* str1,  const string* str2);

// Concatenates the two strings and returns it as a new object.
string* string_concatenate(const string* str1, const string* str2);

// Creates a substring based on the indices and returns it as a new object.
string* string_substring(const string* str, const size_t start_index, const size_t end_index);

// Checks whether 'substr' is a substring of 'str'.
bool string_issubstring(const string* str, const string* substr);

// strchr() but for 'string' type.
char* string_strchr(const string* str, char character);

// Checks whether the given character is present in the string.
// Often used to check for delimiters in a text.
bool string_contains_char(const string* str, const char character);

// Read input from a source (either a file or 'stdin') until it reaches a delimiter.
// Returns a 'string' pointer if it succeeded and a 'NULL' otherwise.
string* string_read(FILE* source, const char* delimiters);

// Reads a line from 'stdin' until the first 'new line' character.
string* string_read_line(void);

// Reads characters from 'stdin' until the first spcae (' ') character.
string* string_read_word(void);

/*---------------------------------------------------------------------*/

// Primitive building block of arrays (linked lists) of strings.
// This type does not have a 'public' constructor and destructor.
// It is supposed to be used as an iterator for looping through the given list.
typedef struct _strnode strnode;

// Getter to extract the 'string' component of the node.
string* strnode_get_string(const strnode* node);

// Getter to extract the raw char array of the node's 'string' component.
// Equivalent to 'string_get_data( strnode_get_string() )'.
const char* strnode_get_data(const strnode* node);

// Getter to extract the 'length' of the node's 'string' component.
// Equivalent to 'string_get_length( strnode_get_string() )'.
size_t strnode_get_length(const strnode* node);

// Getter for the 'next' field of the node.
strnode* strnode_get_next(const strnode* node);

// Getter for the 'index' field of the node.
// Note that index '0' may mean that it's the first element of the list of that it doesn't belong to any lists.
size_t strnode_get_index(const strnode* node);

// Definition of an array (linked list) of strings.
typedef struct _strarr strarr;

// Constructor of an array (linked list) of strings.
strarr* new_strarr(void);

// Destuctor of an array (linked list) of strings.
void delete_strarr(strarr* arr);

// Getter for the number of strings stored in the list.
size_t strarr_get_count(const strarr* arr);

// Getter for the head (field 'first') of the list.
strnode* strarr_get_first(const strarr* arr);

// Insert a string to the end of the list.
void strarr_append(const string* str, strarr** arr);

// Insert a string to the start of the list.
void strarr_prepend(const string* str, strarr** arr);

// Insert a string to a specified index of the list.
void strarr_insert_at(const string* str, const size_t index, strarr** arr);

// Remove the last string of the list.
string* strarr_remove_last(strarr** arr);

// Remove the first string of the list.
string* strarr_remove_first(strarr** arr);

// Remove the string from the list at a specified index.
string* strarr_remove_at(const size_t index, strarr** arr);

#endif