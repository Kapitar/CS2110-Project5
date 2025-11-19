#include "ag_utils.h"
#include "../letterboxd.h"
#include <criterion/criterion.h>
#include <criterion/new/assert.h>

TestSuite(test_get_highest_rated_movie, .timeout = UNREASONABLY_LONG);

/* =====================================
 * Failure Get Highest Rated Movie Tests
 * ===================================== */

Test(test_get_highest_rated_movie, null_review_list) {
    cr_assert(
        zero(ptr, get_highest_rated_movie()),
        "Should return NULL for NULL review list"
    );
}

Test(test_get_highest_rated_movie, null_backing_array) {
    reviewList = malloc(sizeof(Heap));
    reviewList->backingArray = NULL;
        cr_assert(
        zero(ptr, get_highest_rated_movie()),
        "Should return NULL for NULL backing array"
    );
    free(reviewList);
}

Test(test_get_highest_rated_movie, zero_num_elements) {
    h_initialize_heap(4); // initialize heap sets num_elements = 0

    cr_assert(
        zero(ptr, get_highest_rated_movie()),
        "Should return NULL when num elements = 0"
    );
    h_destroy_heap();
}

Test(test_get_highest_rated_movie, neg_num_elements) {
    h_initialize_heap(4);
    reviewList->numElements = -1;

    cr_assert(
        zero(ptr, get_highest_rated_movie()),
        "Should return NULL when num elements < 0"
    );
    h_destroy_heap();
}

/* =====================================
 * Success Get Highest Rated Movie Tests
 * ===================================== */

Test(test_get_highest_rated_movie, single_movie_success) {
    h_initialize_heap(4);

    Movie *movie = h_create_movie("Dune", "Denis Villeneuve", 2021);
    Review *review = h_create_review(movie, 9);

    reviewList->backingArray[0] = review;
    reviewList->numElements = 1;

    cr_assert(
        eq(ptr, get_highest_rated_movie(), movie),
        "Expected highest rated movie to be correct"
    );

    h_destroy_review(review);
    h_destroy_movie(movie);
    h_destroy_heap();
}

Test(test_get_highest_rated_movie, multiple_movies_success) {
    h_initialize_heap(5);

    Movie* movie_1 = h_create_movie("The Shawshank Redemption", "Frank Darabont", 1994);
    Movie* movie_2 = h_create_movie("Cool Movie", "CS2110 TAs", 2025);
    Movie* movie_3 = h_create_movie("The Dark Knight", "Christopher Nolan", 2008);

    Review *review_1 = h_create_review(movie_1, 1);
    Review *review_2 = h_create_review(movie_2, 8);
    Review *review_3 = h_create_review(movie_2, 9);
    Review *review_4 = h_create_review(movie_3, 7);
    Review *review_5 = h_create_review(movie_3, 8);

    //put in backing array as if heapify had been called
    reviewList->backingArray[0] = review_3;
    reviewList->backingArray[1] = review_2;
    reviewList->backingArray[2] = review_5;
    reviewList->backingArray[3] = review_4;
    reviewList->backingArray[4] = review_1;
    
    reviewList->numElements = 5;

    cr_assert(
        eq(ptr, get_highest_rated_movie(), movie_2),
        "Expected highest rated movie to be correct"
    );

    h_destroy_review(review_1);
    h_destroy_review(review_2);
    h_destroy_review(review_3);
    h_destroy_review(review_4);
    h_destroy_review(review_5);

    h_destroy_movie(movie_1);
    h_destroy_movie(movie_2);
    h_destroy_movie(movie_3);

    h_destroy_heap();
}
