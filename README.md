# String.h
`String.h` is an attempt to implement a string type in C. The library contains the following type definitions: `String` and `StringArray`.

## Features

### String
`String` has the following features:
* storing string: `myString->string`
  * under the hood, it's a classic `char*` variable, so individual characters can be edited: `myString->string[i]`
  * it is not protected in any way, so make sure to modify it responsibly (i.e. beware the null-terminating character `'\0'`)
* storing its length: `myString->length`

`String` provides the following functions:
* constructor
```c
String* string01 = newString("Hello, World!");
String* string02 = newString("");
```
* destructor
```c
deleteString(string01);
```

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
* `isValidString()`: checks whether the string's terminating character is equal to `\0`.


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
### StringList

## Installation
Coming soon.

## Further ideas
* `stringSplit` - a function splitting a string by "word boundaries" (i.e. separator characters) and making an array out f them
* `StringList` - strings using linked lists
