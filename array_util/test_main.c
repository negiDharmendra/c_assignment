#include <stdio.h>
#include "arrayUtil_test.C"
int main(void) {
test_create_array();
test_are_equal();
test_array_with_defferent_type_size_are_not_equal();
test_array_with_defferent_length_are_not_equal();
test_array_with_defferent_element_are_not_equal();
test_resize();
test_find_index();
}