#include "ag_utils.h"
#include "../letterboxd.h"
#include <criterion/criterion.h>
#include <criterion/new/assert.h>

TestSuite(test_create_review, .timeout = UNREASONABLY_LONG);

/* ===============================
 * Failure Create Review Tests
 * =============================== */

//Null args
Test(test_create_review, null_movie) {
    cr_assert(
        zero(ptr, create_review(NULL, 1)),
        "Should return NULL for NULL name"
    );
}

//Invalid args
Test(test_create_review, negative_rating) {
    Movie* test_movie = h_create_movie("TestName", "TestDirector", 2026);
    cr_assert(
        zero(ptr, create_review(test_movie, -1)),
        "Should return NULL when rating < 0"
    );
    h_destroy_movie(test_movie);
}

Test(test_create_review, zero_rating) {
    Movie* test_movie = h_create_movie("TestName", "TestDirector", 2026);
    cr_assert(
        zero(ptr, create_review(test_movie, 0)),
        "Should return NULL when rating is 0"
    );
    h_destroy_movie(test_movie);
}

Test(test_create_review, rating_exceed_max) {
    Movie* test_movie = h_create_movie("TestName", "TestDirector", 2026);
    cr_assert(
        zero(ptr, create_review(test_movie, 11)),
        "Should return NULL when rating > 10"
    );
    h_destroy_movie(test_movie);
}

//Malloc Failure
Test(test_create_review, malloc_failure) {
    Movie* test_movie = h_create_movie("TestName", "TestDirector", 2026);

    bytes_until_fail = sizeof(Review) - 1;
    cr_assert(
        zero(ptr, create_review(test_movie, 1)),
        "Should return NULL upon malloc failure"
    );
    h_destroy_movie(test_movie);
}

/* ===============================
 * Success Create Review Tests
 * =============================== */

Test(test_create_review, basic_success) {
    Movie* test_movie = h_create_movie("TestName", "TestDirector", 2026);
    Review* test_review = create_review(test_movie, 1);
    cr_assert(
        not(zero(test_review)),
        "Expected new review to be created"
    );
    cr_assert(
        eq(ptr, test_review->reviewedMovie, test_movie),
        "Expected created review's reviewed movie to be correct"
    );
    cr_assert(
        eq(int, test_review->rating, 1),
        "Expected created review's rating to be correct"
    );
    h_destroy_review(test_review);
    h_destroy_movie(test_movie);
}

Test(test_create_review, multiple_success) {
    Movie* test_movie = h_create_movie("TestName", "TestDirector", 2026);
    Review* test_review_1 = create_review(test_movie, 1);
    Review* test_review_2 = create_review(test_movie, 10);
    cr_assert(
        not(zero(test_review_1)),
        "Should return valid pointer upon success"
    );
    cr_assert(
        eq(ptr, test_review_1->reviewedMovie, test_movie),
        "Field reviewedMovie should point to same movie that was passed into initializer"
    );
    cr_assert(
        eq(int, test_review_1->rating, 1),
        "Rating should be 1"
    );
    cr_assert(
        not(zero(test_review_2)),
        "Should return valid pointer upon success"
    );
    cr_assert(
        eq(ptr, test_review_2->reviewedMovie, test_movie),
        "Field reviewedMovie should point to same movie that was passed into initializer"
    );
    cr_assert(
        eq(int, test_review_2->rating, 10),
        "Rating should be 10"
    );
    h_destroy_movie(test_movie);
    h_destroy_review(test_review_1);
    h_destroy_review(test_review_2);
}
