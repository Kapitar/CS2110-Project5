#include "ag_utils.h"
#include "../letterboxd.h"
#include <criterion/criterion.h>
#include <criterion/new/assert.h>

TestSuite(test_heapify, .timeout = UNREASONABLY_LONG);

/* ===============================
 * Failure Heapify Tests
 * =============================== */
Test(test_heapify, null_reviewlist) {
    cr_assert(eq(type(Result), heapify(1), FAILURE),
        "Should return FAILURE when reviewlist is NULL");
}

Test(test_heapify, negative_index) {
    h_initialize_heap(3);

    cr_assert(eq(type(Result), heapify(-1), FAILURE),
        "Should return FAILURE when index is negative");

    h_destroy_heap();
}

Test(test_heapify, index_equals_num_elements) {
    h_initialize_heap(3);
    Review **reviews = h_prepare_reviews(3);

    //fill backing array
    for (int i = 0; i < 3; i++) {
        reviewList->backingArray[i] = reviews[i];
    }
    reviewList->numElements = 3;

    cr_assert(eq(type(Result), heapify(3), FAILURE),
        "Should return FAILURE when index is too large");
    
    h_destroy_reviews(reviews, 3);
    h_destroy_heap();
}

Test(test_heapify, index_exceeds_num_elements) {
    h_initialize_heap(3);
    Review **reviews = h_prepare_reviews(3);

    //fill backing array
    for (int i = 0; i < 3; i++) {
        reviewList->backingArray[i] = reviews[i];
    }
    reviewList->numElements = 3;

    cr_assert(eq(type(Result), heapify(4), FAILURE),
        "Should return FAILURE when index is too large");
    
    h_destroy_reviews(reviews, 3);
    h_destroy_heap();
}

Test(test_heapify, index_exceeds_num_elements_empty_heap) {
    h_initialize_heap(3);

    cr_assert(eq(type(Result), heapify(1), FAILURE),
        "Should return FAILURE when index is too large");
    
    h_destroy_heap();
}

/* ===============================
 * Success Heapify Tests
 * =============================== */

Test(test_heapify, single_element_success) {
    h_initialize_heap(3);
    Review **reviews = h_prepare_reviews(1);
    
    reviewList->backingArray[0] = reviews[0];
    reviewList->numElements = 1;

    cr_assert(eq(type(Result), heapify(0), SUCCESS),
        "Should return SUCCESS for valid index");

    //no change to backing array since single element
    cr_assert(eq(ptr, reviewList->backingArray[0], reviews[0]),
        "Expected backing array to be in correct order after heapify");

    h_destroy_reviews(reviews, 1);
    h_destroy_heap();
}

Test(test_heapify, multiple_success) {
    h_initialize_heap(4);
    Review **reviews = h_prepare_reviews(4);
    
    for (int i = 0; i < 4; i++) {
        reviewList->backingArray[i] = reviews[i];
    }
    reviewList->numElements = 4;
    /*
        Prior to heapify calls, heap looks like:
            1
           / \
          2   3
         /
        4

        Heapify Call 1: Index 0
        After call, heap should look like (no change):
            1
           / \
          2   3
         /
        4
    */
    cr_assert(eq(type(Result), heapify(0), SUCCESS),
        "Should return SUCCESS for valid index");
    cr_assert(eq(ptr, reviewList->backingArray[0], reviews[0]),
        "Expected backing array at index 0 to be in correct order after heapify");
    cr_assert(eq(ptr, reviewList->backingArray[1], reviews[1]),
        "Expected backing array at index 1 to be in correct order after heapify");
    cr_assert(eq(ptr, reviewList->backingArray[2], reviews[2]),
        "Expected backing array at index 2 to be in correct order after heapify");
    cr_assert(eq(ptr, reviewList->backingArray[3], reviews[3]),
        "Expected backing array at index 3 to be in correct order after heapify");
    /*
        Heapify Call 2: Index 1
        After call, heap should look like:
            2
           / \
          1   3
         /
        4
    */
    cr_assert(eq(type(Result), heapify(1), SUCCESS),
        "Should return SUCCESS for valid index");
    cr_assert(eq(ptr, reviewList->backingArray[0], reviews[1]),
        "Expected backing array at index 0 to be in correct order after heapify");
    cr_assert(eq(ptr, reviewList->backingArray[1], reviews[0]),
        "Expected backing array at index 1 to be in correct order after heapify");
    cr_assert(eq(ptr, reviewList->backingArray[2], reviews[2]),
        "Expected backing array at index 2 to be in correct order after heapify");
    cr_assert(eq(ptr, reviewList->backingArray[3], reviews[3]),
        "Expected backing array at index 3 to be in correct order after heapify");
    /*
        Heapify Call 3: Index 2
        After call, heap should look like:
            3
           / \
          1   2
         /
        4
    */
    cr_assert(eq(type(Result), heapify(2), SUCCESS),
        "Should return SUCCESS for valid index");
    cr_assert(eq(ptr, reviewList->backingArray[0], reviews[2]),
        "Expected backing array at index 0 to be in correct order after heapify");
    cr_assert(eq(ptr, reviewList->backingArray[1], reviews[0]),
        "Expected backing array at index 1 to be in correct order after heapify");
    cr_assert(eq(ptr, reviewList->backingArray[2], reviews[1]),
        "Expected backing array at index 2 to be in correct order after heapify");
    cr_assert(eq(ptr, reviewList->backingArray[3], reviews[3]),
        "Expected backing array at index 3 to be in correct order after heapify");
    /*
        Heapify Call 4: Index 3
        After call, heap should look like:
            4
           / \
          3   2
         /
        1
    */
    cr_assert(eq(type(Result), heapify(3), SUCCESS),
        "Should return SUCCESS for valid index");
    cr_assert(eq(ptr, reviewList->backingArray[0], reviews[3]),
        "Expected backing array at index 0 to be in correct order after heapify");
    cr_assert(eq(ptr, reviewList->backingArray[1], reviews[2]),
        "Expected backing array at index 1 to be in correct order after heapify");
    cr_assert(eq(ptr, reviewList->backingArray[2], reviews[1]),
        "Expected backing array at index 2 to be in correct order after heapify");
    cr_assert(eq(ptr, reviewList->backingArray[3], reviews[0]),
        "Expected backing array at index 3 to be in correct order after heapify");

    h_destroy_reviews(reviews, 4);
    h_destroy_heap();
}
