#include "ag_utils.h"
#include "../letterboxd.h"
#include <criterion/criterion.h>
#include <criterion/new/assert.h>

TestSuite(test_resize_review_list, .timeout = UNREASONABLY_LONG);

/* ===============================
 * Resize Review List Tests
 * =============================== */

Test(test_resize_review_list, heap_uninitialized) 
{
   cr_assert(eq(type(Result), resize_review_list(), FAILURE),
    "Expected resizing uninitalized review list to return FAILURE"); 
}

Test(test_resize_review_list, malloc_failure) 
{
    h_initialize_heap(4);
    Review **temp_reviews = h_prepare_reviews(1);

    bytes_until_fail = reviewList->backingArrayLength * 2 * sizeof(Review *) - 1;

    cr_assert(eq(type(Result), resize_review_list(), FAILURE),
    "Expected a malloc failure to return FAILURE");

    h_destroy_reviews(temp_reviews, 1);
    h_destroy_heap();
}

Test(test_resize_review_list, basic_success) 
{
    int init_heap_size = 4;
    h_initialize_heap(init_heap_size);
    Review **temp_reviews = h_prepare_reviews(1);

    cr_assert(eq(type(Result), resize_review_list(), SUCCESS),
    "Expected a successful call to resize_review_list to return SUCCESS");
    
    cr_assert(eq(int, reviewList->backingArrayLength, init_heap_size * 2),
    "Expected size of backing array to double after resizing");

    h_destroy_reviews(temp_reviews, 1); 
    h_destroy_heap();
}

Test(test_resize_review_list, success_validate_reviewlist)
{
    h_initialize_heap(5);
    Review **temp_reviews = h_prepare_reviews(5);

    // Set the backing array manually, not through student function
    int expected_heap[] = {4, 3, 1, 0, 2};
    for (int i = 0; i < 5; i++) 
    {
        reviewList->backingArray[i] = temp_reviews[expected_heap[i]];
    }

    reviewList->numElements = 5;

    cr_assert(eq(type(Result), resize_review_list(), SUCCESS),
    "Expected a successful call to resize_review_list to return SUCCESS");

    for (int i = 0; i < 5; i++) 
    {
        cr_assert(eq(ptr, reviewList->backingArray[i], temp_reviews[expected_heap[i]]), 
        "Expected backing array to be correct at index %d", i);
    }

    h_destroy_reviews(temp_reviews, 5);
    h_destroy_heap();
}

