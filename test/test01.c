#include <stdio.h>
#include "../src/cstring.h"

void print_string(const string* str);
void check_equality(const string* s01, const string* s02);
void check_relation(const string* s01, const string* s02);
void check_subset(const string* s01, const string* s02);

int main() {
    string* s01 = new_string("apple");
    string* s02 = new_string("banana");
    string* s03 = new_string("coconut");

    print_string(s01);
    print_string(s02);
    print_string(s03);

    check_equality(s01, s02);
    check_relation(s01, s02);

    string* concat = string_concatenate(s02, s03);
    print_string(concat);

    string* s04 = new_string("Spain");
    string* s05 = new_string("pain");
    check_subset(s04, s05);

    delete_string(s01);
    delete_string(s02);
    delete_string(s03);
    delete_string(concat);
    delete_string(s04);
    delete_string(s05);

    return 0;
}

void print_string(const string* str) {
    printf("%s\t(length: %lu)\t", string_get_data(str), string_get_length(str));
    string_isvalid(str) ? puts("valid") : puts("not valid");
}

void check_equality(const string* s01, const string* s02) {
    string_areequal(s01, s02) ? printf("%s == %s\n", string_get_data(s01), string_get_data(s02)) : printf("%s != %s\n", string_get_data(s01), string_get_data(s02));
}

void check_relation(const string* s01, const string* s02) {
    int i = string_compare(s01, s02);

    if (i > 0)
        printf("%s > %s\n", string_get_data(s01), string_get_data(s02));
    else
        printf("%s < %s\n", string_get_data(s01), string_get_data(s02));

}

void check_subset(const string* s01, const string* s02) {
    const char* s1 = string_get_data(s01);
    const char* s2 = string_get_data(s02);
    string_issubstring(s01, s02) ? printf("%s is a substring of %s\n", s2, s1) : printf("%s is not a substring of %s\n", s2, s1);

    char character = 'a';
    string_contains_char(s01, character) ? printf("%s contains '%c'\n", s1, character) : printf("%s does not contain '%c'\n", s1, character);
}