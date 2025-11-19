#include "ag_utils.h"
#include "../letterboxd.h"
#include <criterion/criterion.h>
#include <criterion/new/assert.h>

TestSuite(test_swap, .timeout = UNREASONABLY_LONG);

/* ===============================
 * Failure Swap Tests
 * =============================== */
Test(test_swap, null_reviewlist) {
    cr_assert(eq(type(Result), swap(1, 2), FAILURE),
        "Should return FAILURE when reviewList is NULL");
}

Test(test_swap, negative_i) {
    h_initialize_heap(1);

    cr_assert(eq(type(Result), swap(-1, 2), FAILURE),
        "Should return FAILURE when i is invalid");
    
    h_destroy_heap();
}

Test(test_swap, i_equals_num_elements) {
    h_initialize_heap(1);

    Review **reviews = h_prepare_reviews(1);
    reviewList->backingArray[0] = reviews[0];
    reviewList->numElements = 1;
    
    cr_assert(eq(type(Result), swap(1, 0), FAILURE),
        "Should return FAILURE when i is invalid");
    
    h_destroy_reviews(reviews, 1);
    h_destroy_heap();
}

Test(test_swap, i_exceeds_num_elements) {
    h_initialize_heap(1);

    Review **reviews = h_prepare_reviews(1);
    reviewList->backingArray[0] = reviews[0];
    reviewList->numElements = 1;
    
    cr_assert(eq(type(Result), swap(2, 0), FAILURE),
        "Should return FAILURE when i is invalid");
    
    h_destroy_reviews(reviews, 1);
    h_destroy_heap();
}

Test(test_swap, negative_j) {
    h_initialize_heap(1);

    cr_assert(eq(type(Result), swap(1, -1), FAILURE),
        "Should return FAILURE when j is invalid");
    
    h_destroy_heap();
}

Test(test_swap, j_equals_num_elements) {
    h_initialize_heap(1);

    Review **reviews = h_prepare_reviews(1);
    reviewList->backingArray[0] = reviews[0];
    reviewList->numElements = 1;
    
    cr_assert(eq(type(Result), swap(0, 1), FAILURE),
        "Should return FAILURE when j is invalid");
    
    h_destroy_reviews(reviews, 1);
    h_destroy_heap();
}

Test(test_swap, j_exceeds_num_elements) {
    h_initialize_heap(1);

    Review **reviews = h_prepare_reviews(1);
    reviewList->backingArray[0] = reviews[0];
    reviewList->numElements = 1;
    
    cr_assert(eq(type(Result), swap(0, 2), FAILURE),
        "Should return FAILURE when j is invalid");
    
    h_destroy_reviews(reviews, 1);
    h_destroy_heap();
}
/* ===============================
 * Success Swap Tests
 * =============================== */

Test(test_swap, basic_success) {
    h_initialize_heap(3);

    Review **reviews = h_prepare_reviews(3);
    for (int i = 0; i < 3; i ++) {
        reviewList->backingArray[i] = reviews[i];
    }
    reviewList->numElements = 3;
    
    cr_assert(eq(type(Result), swap(0, 2), SUCCESS),
        "Should return SUCCESS when valid swap made");
    //assert backing array correct
    cr_assert(eq(ptr, reviewList->backingArray[0], reviews[2]),
        "Should return SUCCESS when valid swap made");
    cr_assert(eq(ptr, reviewList->backingArray[1], reviews[1]),
        "Should return SUCCESS when valid swap made");
    cr_assert(eq(ptr, reviewList->backingArray[2], reviews[0]),
        "Should return SUCCESS when valid swap made");

    h_destroy_reviews(reviews, 3);
    h_destroy_heap();
}
Test(test_swap, multiple_success) {
    h_initialize_heap(5);

    Review **reviews = h_prepare_reviews(5);
    for (int i = 0; i < 5; i ++) {
        reviewList->backingArray[i] = reviews[i];
    }
    reviewList->numElements = 5;

    /*
        Original backing array: [1, 2, 3, 4, 5]

        Swap 1: Indicies 0, 1
        Backing array after swap: [2, 1, 3, 4, 5]
    */
    cr_assert(eq(type(Result), swap(0, 1), SUCCESS),
        "Should return SUCCESS when valid swap made");
    //assert backing array correct
    cr_assert(eq(ptr, reviewList->backingArray[0], reviews[1]),
        "Expected backing array to be correct at index 0");
    cr_assert(eq(ptr, reviewList->backingArray[1], reviews[0]),
        "Expected backing array to be correct at index 1");
    cr_assert(eq(ptr, reviewList->backingArray[2], reviews[2]),
        "Expected backing array to be correct at index 2");
    cr_assert(eq(ptr, reviewList->backingArray[3], reviews[3]),
        "Expected backing array to be correct at index 3");
    cr_assert(eq(ptr, reviewList->backingArray[4], reviews[4]),
        "Expected backing array to be correct at index 4");
    /*
        Swap 2: Indicies 3, 0
        Backing array after swap: [4, 1, 3, 2, 5]
    */
    cr_assert(eq(type(Result), swap(3, 0), SUCCESS),
        "Should return SUCCESS when valid swap made");
    //assert backing array correct
    cr_assert(eq(ptr, reviewList->backingArray[0], reviews[3]),
        "Expected backing array to be correct at index 0");
    cr_assert(eq(ptr, reviewList->backingArray[1], reviews[0]),
        "Expected backing array to be correct at index 1");
    cr_assert(eq(ptr, reviewList->backingArray[2], reviews[2]),
        "Expected backing array to be correct at index 2");
    cr_assert(eq(ptr, reviewList->backingArray[3], reviews[1]),
        "Expected backing array to be correct at index 3");
    cr_assert(eq(ptr, reviewList->backingArray[4], reviews[4]),
        "Expected backing array to be correct at index 4");
    /*
        Swap 3: Indicies 4, 2
        Backing array after swap: [4, 1, 5, 2, 3]
    */
    cr_assert(eq(type(Result), swap(4, 2), SUCCESS),
        "Should return SUCCESS when valid swap made");
    //assert backing array correct
    cr_assert(eq(ptr, reviewList->backingArray[0], reviews[3]),
        "Expected backing array to be correct at index 1");
    cr_assert(eq(ptr, reviewList->backingArray[1], reviews[0]),
        "Expected backing array to be correct at index 2");
    cr_assert(eq(ptr, reviewList->backingArray[2], reviews[4]),
        "Expected backing array to be correct at index 3");
    cr_assert(eq(ptr, reviewList->backingArray[3], reviews[1]),
        "Expected backing array to be correct at index 4");
    cr_assert(eq(ptr, reviewList->backingArray[4], reviews[2]),
        "Expected backing array to be correct at index 5");

    h_destroy_reviews(reviews, 5);
    h_destroy_heap();
}