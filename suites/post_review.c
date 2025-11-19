#include "ag_utils.h"
#include "../letterboxd.h"
#include <criterion/criterion.h>
#include <criterion/new/assert.h>

TestSuite(test_post_review, .timeout = UNREASONABLY_LONG);

/* ===============================
 * Failure Post Review Tests
 * =============================== */

Test(test_post_review, heap_uninitialized)
{
    Review temp_review = {
        .reviewedMovie = NULL,
        .rating = 7
    };
    cr_assert(eq(type(Result), post_review(&temp_review), FAILURE),
    "Expected posting review with uninitialized heap to return FAILURE");
}

Test(test_post_review, null_review)
{
    h_initialize_heap(4);
    Review **temp = h_prepare_reviews(1);

    reviewList->backingArray[reviewList->numElements++] = temp[0]; // for the sake of something being there

    cr_assert(eq(type(Result), post_review(NULL), FAILURE),
    "Null pointer passed for review, expected to return FAILURE");
    
    h_destroy_reviews(temp, 1);
    h_destroy_heap();
}

Test (test_post_review, realloc_failure) {

    h_initialize_heap(4);

    Review **temp_reviews = h_prepare_reviews(5);

    for (int i = 0; i < 4; i++) 
    {
        cr_assert(eq(type(Result), post_review(temp_reviews[i]), SUCCESS),
        "Expected succesful call to post_review to return SUCCESS");
        cr_assert(eq(int, reviewList->numElements, i+1),
        "Expected successful call to post_review to increase the number of elements in the heap");

    }

    // The next post will overflow the heap, so it will have to resize
    bytes_until_fail = reviewList->backingArrayLength * 2 * sizeof(Review *) - 1; // realloc fails

    cr_assert(eq(type(Result), post_review(temp_reviews[4]), FAILURE),
    "Expected successful call to post_review to return SUCCESS, even when resizing");

    cr_assert(eq(int, reviewList->numElements, 4),
        "Expected successful call to post_review to increase the number of elements in the heap");

    /*
        Heap should look like:
                    3
                   / \
                  2   1
                 / 
                0

    */

    cr_assert(eq(ptr, reviewList->backingArray[0], temp_reviews[3])); 
    cr_assert(eq(ptr, reviewList->backingArray[1], temp_reviews[2]));
    cr_assert(eq(ptr, reviewList->backingArray[2], temp_reviews[1]));
    cr_assert(eq(ptr, reviewList->backingArray[3], temp_reviews[0]));

    h_destroy_reviews(temp_reviews, 5);
    h_destroy_heap();
}
/* ===============================
 * Success Post Review Tests
 * =============================== */

Test(test_post_review, basic_success)
{
    h_initialize_heap(4);
    Review **temp_reviews = h_prepare_reviews(1);
    
    cr_assert(eq(type(Result), post_review(temp_reviews[0]), SUCCESS),
    "Expected succesful call to post_review to return SUCCESS");

    cr_assert(eq(int, reviewList->numElements, 1),
    "Expected successful posting to increase number of elements in heap by 1");

    cr_assert(eq(ptr, reviewList->backingArray[0], temp_reviews[0]),
    "Expected reviewList to contain newly posted review");

    h_destroy_reviews(temp_reviews, 1);
    h_destroy_heap();
}

Test(test_post_review, post_multiple)
{
    h_initialize_heap(4);
    Review **temp_reviews = h_prepare_reviews(4);
    
    for (int i = 0; i < 4; i++)
    {
        cr_assert(eq(type(Result), post_review(temp_reviews[i]), SUCCESS),
        "Expected succesful call to post_review to return SUCCESS");
        cr_assert(eq(int, reviewList->numElements, i+1),
        "Expected successful call to post_review to increase the number of elements in the heap");
    }
    /*

        In indices of temp_reviews, the heap should look like:
            3
           / \
          2   1
         /
        0

    */
   for (int i = 0; i < 4; i++) // validate the heap's entries now
   {
        cr_assert(eq(ptr, reviewList->backingArray[i], temp_reviews[3-i]),
        "Expected heap's backing array to contain review of movie \"%s\", instead found \"%s\"",
        temp_reviews[i]->reviewedMovie->name, reviewList->backingArray[i]->reviewedMovie->name);
   }

   h_destroy_reviews(temp_reviews, 4);
   h_destroy_heap();
}

Test (test_post_review, resize_required) {

    h_initialize_heap(4);

    Review **temp_reviews = h_prepare_reviews(5);

    for (int i = 0; i < 4; i++) 
    {
        cr_assert(eq(type(Result), post_review(temp_reviews[i]), SUCCESS),
        "Expected succesful call to post_review to return SUCCESS");
        cr_assert(eq(int, reviewList->numElements, i+1),
        "Expected successful call to post_review to increase the number of elements in the heap");

    }

    // The next post will overflow the heap, so it will have to resize

    cr_assert(eq(type(Result), post_review(temp_reviews[4]), SUCCESS),
    "Expected successful call to post_review to return SUCCESS, even when resizing");

    cr_assert(eq(int, reviewList->numElements, 5),
        "Expected successful call to post_review to increase the number of elements in the heap");

    /*
        Heap should look like:
                    4
                   / \
                  3   1
                 / \  
                0   2 

    */

    cr_assert(eq(ptr, reviewList->backingArray[0], temp_reviews[4])); 
    cr_assert(eq(ptr, reviewList->backingArray[1], temp_reviews[3]));
    cr_assert(eq(ptr, reviewList->backingArray[2], temp_reviews[1]));
    cr_assert(eq(ptr, reviewList->backingArray[3], temp_reviews[0]));
    cr_assert(eq(ptr, reviewList->backingArray[4], temp_reviews[2]));

    h_destroy_reviews(temp_reviews, 5);
    h_destroy_heap();
}