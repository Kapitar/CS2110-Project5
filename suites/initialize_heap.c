#include "ag_utils.h"
#include "../letterboxd.h"
#include <criterion/criterion.h>
#include <criterion/new/assert.h>

TestSuite(test_initialize_heap, .timeout = UNREASONABLY_LONG);

/* ===============================
 * Failure Initialize Heap Tests
 * =============================== */

//Invalid Args
Test(test_initialize_heap, zero_initial_capacity) {
    cr_assert(
        eq(type(Result), initialize_heap(0), FAILURE),
        "Should return FAILURE for zero initial capacity"
    );
}
Test(test_initialize_heap, negative_initial_capacity) {
    cr_assert(
        eq(type(Result), initialize_heap(-1), FAILURE),
        "Should return FAILURE for negative initial capacity"
    );
}

//Malloc Failure
Test(test_initialize_heap, heap_malloc_failure) {
    // Test failing on Heap struct malloc
    bytes_until_fail = sizeof(Heap) - 1;
    cr_assert(
        eq(type(Result), initialize_heap(4), FAILURE),
        "Should return FAILURE upon malloc failure"
    );
}
Test(test_initialize_heap, backing_array_malloc_failure) {
    // Test failing on backing array malloc
    bytes_until_fail = sizeof(Heap) + sizeof(Review*) * 4 - 1;
    cr_assert(
        eq(type(Result), initialize_heap(4), FAILURE),
        "Should return FAILURE upon malloc failure"
    );
}

/* ===============================
 * Success Initialize Heap Tests
 * =============================== */

Test(test_initialize_heap, basic_success) {
    cr_assert(
        eq(type(Result), initialize_heap(4), SUCCESS),
        "Should return SUCCESS upon successful heap initialization"
    );
    cr_assert(
        not(zero(ptr, reviewList)),
        "Global reviewList should be a valid pointer upon success"
    );
    cr_assert(
        not(zero(ptr, reviewList->backingArray)),
        "Global reviewList backingArray should be a valid pointer"
    );
    cr_assert(
        eq(int, reviewList->backingArrayLength, 4),
        "Global reviewList backingArrayLength should be 4"
    );
    cr_assert(
        eq(int, reviewList->numElements, 0),
        "Global reviewList numElements should be 0"
    );
    h_destroy_heap();
}
