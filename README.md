# cstring.h
**ATTENTION**: THIS PROJECT HAS BEEN MOVED TO THE "DATASTRUCTS.H" REPOSITORY UNDER MY ACCOUNT. WHAT YOU SEE HERE ARE THE REMNANTS OF THE OLD CODE BASE (THAT HAS BEED LARGELY REWRITTEN ANYWAY).

PLEASE VISIT THE REVISED PROJECT HERE: https://github.com/kbnim/datastructs.h

`cstring.h` is an attempt to implement a practical string type in C. The library contains the following type definitions: `string` and `strarr` (a linked list of strings).

## Features

### string
`string` offers a safe way to store strings dynamically.
```c
string* str = new_string("Hello, World!");
delete_string(str);
```
It comes with the ability to query the length of the string as well as to get the raw, C-style character array to ensure compatibility with the standard library.
```c
size_t length = string_get_length(str);
puts(string_get_data(str));
```
It provides some protection against malicious or accidental modifications of the internal components - meaning that the struct fields are only accessible through the getter functions.

Other useful functions include:
* `bool string_isvalid(string* str)` - checks whether the string actually ends with a '\0' character
* `bool string_areequal(string* s1, string* s2)` - checks whether the two strings are equal
* `string* string_concatenate(string* s1, string* s2)` - concatenates the two strings and returns it as a new one
* `string* string_substring(string* s, size_t start_index, size_t end_index)` - creates a substring within the given interval
* `bool string_issubstring(string* str, string* substr)` - checks whether `substr` is a substring of `str`
* `bool string_contains_char(string* s, char c)` - checks if `c` is present in `s`

As reading strings from the standard input in C is kind of a pain in the neck, the library comes with a few functions intended to facilitate the simple task of _asking for user input_ (or reading the contents of a file for that matter).
* `string* sting_read(FILE* source, char* delimiters)` - allows the user to read from an input (be it a file or `stdio`) until it meets a delimiter character
* `string* sting_read_line()` - reads from the standard input until the first '\n' character
* `string* sting_read_word()` - reads from the standard input until you hit a space

As an example, reading a file line by line may be achieved like so:
```c
FILE* source = fopen("filename", "r");
// assume the file exists
string* line;
while ((line = string_read(source, "\n") != NULL)) {
 // perform actions using the received line
 delete_string(line);
}
delete_string(line);
// Note that we need to deallocate it, as it broke out of the loop
```

### strarr
`strarr` (a contraction of _string array_) is a singly linked list implementation to store strings. It is used dynamically.
```c
strarr* array = new_strarr();
// ...
delete_strarr(array);
```
Insertion of elements can be accompliushed the following ways:
```c
strarr_append(s1, &array);  // to the end of the list
strarr_prepend(s2, &array); // to the front of the list
strarr_insert_at(s3, index, &array); // insert an element to a specified index
```

The same goes for the removal of elements.
```c
string* s1 = strarr_remove_last(&array); 
string* s2 = strarr_remove_first(&array); 
string* s3 = strarr_remove_at(index, &array);
```

Looping through requires a helper type called `strnode`. On its own, it cannot be instantiated nor can it be removed, as it's meant to be as an implementation detail. However, with the help of an `strnode` pointer, we can loop through a list the following ways:
1. Using a while loop
```c
strnode* i = strarr_get_first(array);
while (i != NULL) {
 // perform actions using the list
 i = strnode_get_next(i);
}
```

2. Using a for loop
```c
for (strnode* i = strarr_get_first(); i != NULL; i = strnode_get_next(i)) {
 // perform actions using the list
}
```

## Installation
Coming soon.

## Further ideas
* Query any element of the list by referring to its index
