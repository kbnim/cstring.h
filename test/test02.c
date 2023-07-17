#include <stdio.h>
#include "../src/cstring.h"

int main() {
    string* s01 = new_string("apple");
    string* s02 = new_string("banana");
    string* s03 = new_string("coconut");
    string* s04 = new_string("Spain");
    string* s05 = new_string("pain");

    strarr* array = new_strarr();

    strarr_append(s01, &array);
    strarr_append(s02, &array);
    strarr_prepend(s03, &array);
    strarr_prepend(s04, &array);
    strarr_insert_at(s05, 2, &array);

    for (strnode* i = strarr_get_first(array); i != NULL; i = strnode_get_next(i)) {
        printf("[%lu] %s (%lu)\n", strnode_get_index(i), strnode_get_data(i), strnode_get_length(i));
    }

    string* removed_from_head  = strarr_remove_first(&array);
    string* removed_from_tail  = strarr_remove_last(&array);
    string* removed_from_index = strarr_remove_at(1, &array);

    puts("");

    for (strnode* i = strarr_get_first(array); i != NULL; i = strnode_get_next(i)) {
        printf("[%lu] %s (%lu)\n", strnode_get_index(i), strnode_get_data(i), strnode_get_length(i));
    }


    delete_strarr(array);
    delete_string(s01);
    delete_string(s02);
    delete_string(s03);
    delete_string(s04);
    delete_string(s05);
    delete_string(removed_from_head);
    delete_string(removed_from_tail);
    delete_string(removed_from_index);

    return 0;
}