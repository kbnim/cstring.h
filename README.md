# cstring.h
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

### strarr
`StringArray` has the following characteristics:
* individual elements can be accessed: `strArr->tokens[i]`
  * we can also access it's "lower level" components: `strArr->tokens[i]->string[j]`
  * any element can be modified, just like in a regular array
* number of elements: `strArr->count`
* like a traditional array, it's size cannot be modified - no elements can be added or removed

Note that they're _used as a pointer_ (just like above), even though their name suggests otherwise. Keep in mind that the **number of elements must be declared** when initialising them. The function has no way of checking whether the number of stings correspond to the given integer value, so it remains the programmer's responsibility.
```c
StringArray* strArr = newStringArray(2, newString("Hello"), newString("World"));
````

Deletion is mandatory to avoid memory leak.
```c
deleteStringArray(strArr);
```

Auxiliary functions:
* `splitString(char*, delimiters)`: splits the given `char*` string along the given delimiters
* `printStringArray(string, bool)`: prints out the contents of the array, with or without indices
* `countTokens(string, delimiters)`: counts how many tokens can be found in the string - used for background operations

### StringList

`StringList` has the following features:
* it uses a singly linked list with a head (`StringH1L`)
  * it stores the node, the index of the node and a pointer to the next node
* it stores the number of elements in the list

Note that when you "instantiate" a `StringList`, it creates an empty list.
```c
StringList* strList = newStringList();
```

These are the following ways to add a new element to a list.
```c
appendToList(strList, "appended element");   // adds string to the end of the list
prependToList(strList, "prepended element"); // adds string to the beginning of the list
insertToList(strList, "inserted element");   // adds string to the given index and moves the rest
```

It's possible to remove an element at a given index.
```c
removeFromList(strList, 1);
```

The entire string can be accessed through an index.
```c
String* stringInList = listAtIndex(strList, 1);
puts(stringInList->string);
```

Deletion is similar to those discussed above
```c
deleteStringList(strList);
```
Other functions include:
* `printStringList(list, bool)`: prints the contents of the list, including or excluding indices
* `refactorIndices(list)`: resets the indices of the list starting from `0` to `list->count - 1`

## Installation
Coming soon.

## Further ideas
* coming soon
