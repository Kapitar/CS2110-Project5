#include "ag_utils.h"
#include "../letterboxd.h"
#include <criterion/criterion.h>
#include <criterion/new/assert.h>

TestSuite(test_review_posted, .timeout = UNREASONABLY_LONG);

/* ===============================
 * Review Posted Tests
 * =============================== */

Test(test_review_posted, null_review)
{
    h_initialize_heap(4);

    cr_assert(eq(type(Result), review_posted(NULL), FAILURE),
    "Passed NULL pointer for review, expected FAILURE");
    
    h_destroy_heap();
}

Test(test_review_posted, heap_uninitialized)
{
    Review **temp = h_prepare_reviews(1);

    cr_assert(eq(type(Result), review_posted(temp[0]), FAILURE),
    "Expected call with uninitialized reviewList to return FAILURE");

    h_destroy_reviews(temp, 1);
}

Test(test_review_posted, reviewlist_empty)
{
    h_initialize_heap(4);
    Review **temp = h_prepare_reviews(1);
    
    cr_assert(eq(type(Result), review_posted(temp[0]), FAILURE),
    "Expected trying to find a review that is not in reviewList to return FAILURE");

    h_destroy_reviews(temp, 1);
    h_destroy_heap();
}

Test(test_review_posted, not_found) {
    h_initialize_heap(4);
    
    Review **temp = h_prepare_reviews(5);
    for (int i = 0; i < 4; i++) 
    {
        reviewList->backingArray[i] = temp[i];
    }
    reviewList->numElements = 4;

    // Intentionally don't insert 5

    cr_assert(eq(type(Result), review_posted(temp[4]), FAILURE),
    "Expected trying to find a review that is not in reviewList to return FAILURE");

    h_destroy_reviews(temp, 5);
    h_destroy_heap();
}

Test(test_review_posted, rating_mismatch)
{
    h_initialize_heap(4);
    Review **temp = h_prepare_reviews(1);
    reviewList->backingArray[reviewList->numElements++] = temp[0]; // Insert it into the reviewList

    Review *mismatched = h_create_review(temp[0]->reviewedMovie, temp[0]->rating + 1);

    cr_assert(eq(type(Result), review_posted(mismatched), FAILURE),
    "Expected call to review_posted with a rating that doesn't match to return FAILURE");

    h_destroy_review(mismatched);
    h_destroy_reviews(temp, 1);
    h_destroy_heap();
}

Test(test_review_posted, name_mismatch)
{
    h_initialize_heap(4);
    Review **temp = h_prepare_reviews(1);
    reviewList->backingArray[reviewList->numElements++] = temp[0]; // Insert it into the reviewList

    Movie *wrong_movie = h_create_movie("Shrek", temp[0]->reviewedMovie->director, temp[0]->reviewedMovie->releaseYear);
    Review *mismatched = h_create_review(wrong_movie, 1);
    
    cr_assert(eq(type(Result), review_posted(mismatched), FAILURE),
    "Expected call to review_posted with a movie whose name doesn't match to return FAILURE");

    h_destroy_review(mismatched);
    h_destroy_movie(wrong_movie);
    h_destroy_reviews(temp, 1);
    h_destroy_heap();
}

Test(test_review_posted, director_mismatch)
{
    h_initialize_heap(4);
    Review **temp = h_prepare_reviews(1);
    reviewList->backingArray[reviewList->numElements++] = temp[0]; // Insert it into the reviewList

    Movie *wrong_movie = h_create_movie(temp[0]->reviewedMovie->name, "Suraj", temp[0]->reviewedMovie->releaseYear);
    Review *mismatched = h_create_review(wrong_movie, 1);
    
    cr_assert(eq(type(Result), review_posted(mismatched), FAILURE),
    "Expected call to review_posted with a movie whose name doesn't match to return FAILURE");

    h_destroy_review(mismatched);
    h_destroy_movie(wrong_movie);
    h_destroy_reviews(temp, 1);
    h_destroy_heap();
}

Test(test_review_posted, release_year_mismatch)
{
    h_initialize_heap(4);
    Review **temp = h_prepare_reviews(1);
    reviewList->backingArray[reviewList->numElements++] = temp[0]; // Insert it into the reviewList

    Movie *wrong_movie = h_create_movie(temp[0]->reviewedMovie->name, temp[0]->reviewedMovie->director, 2026);
    Review *mismatched = h_create_review(wrong_movie, 1);

    cr_assert(eq(type(Result), review_posted(mismatched), FAILURE),
    "Expected call to review_posted with a movie whose name doesn't match to return FAILURE");

    h_destroy_review(mismatched);
    h_destroy_movie(wrong_movie);
    h_destroy_reviews(temp, 1);
    h_destroy_heap();
}

Test(test_review_posted, basic_success)
{
    h_initialize_heap(4);
    Review **temp = h_prepare_reviews(1);
    reviewList->backingArray[reviewList->numElements++] = temp[0]; // Insert it into the reviewList

    cr_assert(eq(type(Result), review_posted(temp[0]), SUCCESS),
    "Expected call to review_posted with valid review to return SUCCESS");

    h_destroy_reviews(temp, 1);
    h_destroy_heap();
}

Test(test_review_posted, multiple_success)
{
    h_initialize_heap(4);
    Review **temp = h_prepare_reviews(4);
    // Insert reviews into the reviewList
    reviewList->backingArray[reviewList->numElements++] = temp[0];
    reviewList->backingArray[reviewList->numElements++] = temp[1];
    reviewList->backingArray[reviewList->numElements++] = temp[2];
    reviewList->backingArray[reviewList->numElements++] = temp[3];

    cr_assert(eq(type(Result), review_posted(temp[0]), SUCCESS),
    "Expected call to review_posted with valid review to return SUCCESS");

    cr_assert(eq(type(Result), review_posted(temp[1]), SUCCESS),
    "Expected call to review_posted with valid review to return SUCCESS");

    cr_assert(eq(type(Result), review_posted(temp[2]), SUCCESS),
    "Expected call to review_posted with valid review to return SUCCESS");

    cr_assert(eq(type(Result), review_posted(temp[3]), SUCCESS),
    "Expected call to review_posted with valid review to return SUCCESS");

    h_destroy_reviews(temp, 4);
    h_destroy_heap();
}


Test(test_review_posted, multiple_success_and_failure)
{
    h_initialize_heap(4);
    Review **temp = h_prepare_reviews(2);
    // Insert reviews into the reviewList
    reviewList->backingArray[reviewList->numElements++] = temp[0];
    reviewList->backingArray[reviewList->numElements++] = temp[1];

    Movie *test_movie = h_create_movie("Test Movie", "Test Director", 2020);

    Review *unposted_review_1 = h_create_review(test_movie, 3);
    Review *unposted_review_2 = h_create_review(test_movie, 7);

    cr_assert(eq(type(Result), review_posted(temp[0]), SUCCESS),
    "Expected call to review_posted with valid review to return SUCCESS");

    cr_assert(eq(type(Result), review_posted(temp[1]), SUCCESS),
    "Expected call to review_posted with valid review to return SUCCESS");

    cr_assert(eq(type(Result), review_posted(unposted_review_1), FAILURE),
    "Expected call to review_posted with unposted review to return FAILURE");

    cr_assert(eq(type(Result), review_posted(unposted_review_2), FAILURE),
    "Expected call to review_posted with unposted review to return FAILURE");

    h_destroy_reviews(temp, 2);
    h_destroy_review(unposted_review_1);
    h_destroy_review(unposted_review_2);
    h_destroy_movie(test_movie);
    h_destroy_heap();
}
