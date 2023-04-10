# String.h
`String.h` is an attempt to implement a string type in C. The library contains the following type definitions: `String` and `StringArray`.

## Features

### String
`String` has the following features:
* storing string: `myString->string`
  * under the hood, it's a classic `char*` variable, so individual characters can be edited: `myString->string[i]`
  * it is not protected in any way, so make sure to modify it responsibly (i.e. beware the null-terminating character `'\0'`)
* storing its length: `myString->length`

They are meant to be used as _pointers_. As such, a string's initialisation looks like this:
```c
String* string01 = newString("Hello, World!");
String* string02 = newString("");
```

Note that we **have to manually delete** it after finishing working with it.
```c
deleteString(string01);
```

There are some auxiliary functions defined, not meant to be used by the general public.
* `isValidString(string)`: checks whether the string's terminating character is equal to `\0`.
* `isDelimiter(char, delimiters)`: equivalent to `strchr`
* `stringCompare(string_1, string_2)`: takes pointer variables of type `String` and compares them similarly how `strcmmp` does
* `stringSegment(string, start_index, end_index)`: creates a substring of a string from the given range of characters


### StringArray
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
removeFromList(1);
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
* `stringSplit` - a function splitting a string by "word boundaries" (i.e. separator characters) and making an array out f them
* `StringList` - strings using linked lists
