#include "ag_utils.h"
#include "../letterboxd.h"
#include <criterion/criterion.h>
#include <criterion/new/assert.h>

TestSuite(test_get_best_from_watchlist, .timeout = UNREASONABLY_LONG);

/* =====================================
 * Failure Get Best from Watchlist Tests
 * ===================================== */

Test(test_get_best_from_watchlist, null_watchlist) {
    h_initialize_heap(3);

    cr_assert(
        zero(ptr, get_best_from_watchlist(NULL)),
        "Expected NULL when input watchlist is NULL"
    );

    h_destroy_heap();
}

Test(test_get_best_from_watchlist, null_reviewlist) {
    Watchlist *watchlist = h_create_watchlist("Daniel");

    cr_assert(
        zero(ptr, get_best_from_watchlist(watchlist)),
        "Expected NULL when review list is NULL"
    );

    h_destroy_watchlist(watchlist);
}

Test(test_get_best_from_watchlist, null_backing_array) {
    Watchlist *watchlist = h_create_watchlist("Jason");
    reviewList = malloc(sizeof(Heap));
    reviewList->backingArray = NULL;

    cr_assert(
        zero(ptr, get_best_from_watchlist(watchlist)),
        "Expected NULL when backing array is NULL"
    );

    free(reviewList);
    h_destroy_watchlist(watchlist);
}

Test(test_get_best_from_watchlist, empty_watchlist) {
    h_initialize_heap(4);
    Watchlist *watchlist = h_create_watchlist("Bianca");

    cr_assert(
        zero(ptr, get_best_from_watchlist(watchlist)),
        "Expected NULL when watchlist is empty"
    );

    h_destroy_watchlist(watchlist);
    h_destroy_heap();
}

/* =====================================
 * Success Get Best from Watchlist Tests
 * ===================================== */

Test(test_get_best_from_watchlist, single_movie) {
    h_initialize_heap(4);
    
    Review **temp = h_prepare_reviews(1);

    temp[0]->rating = 5;
    reviewList->backingArray[0] = temp[0]; // Insert it into the reviewList
    reviewList->numElements++;

    Movie *movie = temp[0]->reviewedMovie;
    Watchlist *watchlist = h_create_watchlist("Henry");
    h_add_movie(watchlist, movie, 1);

    Movie *result = get_best_from_watchlist(watchlist);
    cr_assert(eq(ptr, result, movie), "Expected the highest rated movie in the watchlist to be returned");

    h_destroy_watchlist(watchlist);
    // the movies are part of the reviews, so this should free them properly
    h_destroy_reviews(temp, 1);
    h_destroy_heap();
}

Test(test_get_best_from_watchlist, multiple_movies_1) {
    h_initialize_heap(4);
    
    Review **temp = h_prepare_reviews(4);

    /// NOTE: these ratings have the heap property
    int ratings[] = {4, 3, 1, 2};
    for (int i = 0; i < 4; i++) {
        temp[i]->rating = ratings[i];
        reviewList->backingArray[i] = temp[i];
        reviewList->numElements++;
    }

    Watchlist *watchlist = h_create_watchlist("Shivani");

    h_add_movie(watchlist, temp[3]->reviewedMovie, 2); // rating 2
    h_add_movie(watchlist, temp[1]->reviewedMovie, 1); // rating 4

    Movie *result = get_best_from_watchlist(watchlist);
    cr_assert(eq(ptr, result, temp[1]->reviewedMovie), "Expected the highest rated movie in the watchlist to be returned");

    h_destroy_watchlist(watchlist);
    // the movies are part of the reviews, so this should free them properly
    h_destroy_reviews(temp, 4);
    h_destroy_heap();
}

Test(test_get_best_from_watchlist, multiple_movies_2) {
    h_initialize_heap(8);
    
    Review **temp = h_prepare_reviews(8);

    /// NOTE: these ratings have the heap property
    int ratings[] = {7, 3, 6, 2, 1, 4, 5, 0};
    for (int i = 0; i < 8; i++) {
        temp[i]->rating = ratings[i];
        reviewList->backingArray[i] = temp[i];
        reviewList->numElements++;
    }

    Watchlist *watchlist = h_create_watchlist("Andy");

    h_add_movie(watchlist, temp[1]->reviewedMovie, 1); // rating 3
    h_add_movie(watchlist, temp[5]->reviewedMovie, 3); // rating 4
    h_add_movie(watchlist, temp[3]->reviewedMovie, 2); // rating 2

    Movie *result = get_best_from_watchlist(watchlist);
    cr_assert(eq(ptr, result, temp[5]->reviewedMovie), "Expected the highest rated movie in the watchlist to be returned");

    h_destroy_watchlist(watchlist);
    // the movies are part of the reviews, so this should free them properly
    h_destroy_reviews(temp, 8);
    h_destroy_heap();
}

Test(test_get_best_from_watchlist, reviewless_movies) {
    h_initialize_heap(4);
    
    // we use this to generate sample movies for us for all 8 review, but only put 4 reviews in the reviewList
    Review **temp = h_prepare_reviews(8);

    /// NOTE: these ratings have the heap property
    int ratings[] = {5, 3, 4, 2};
    for (int i = 0; i < 4; i++) {
        temp[i]->rating = ratings[i];
        reviewList->backingArray[i] = temp[i];
        reviewList->numElements++;
    }

    Watchlist *watchlist = h_create_watchlist("Other Andy");

    h_add_movie(watchlist, temp[3]->reviewedMovie, 2); // rating 2
    h_add_movie(watchlist, temp[7]->reviewedMovie, 1); // no review
    h_add_movie(watchlist, temp[1]->reviewedMovie, 1); // rating 3
    h_add_movie(watchlist, temp[5]->reviewedMovie, 1); // no review
    h_add_movie(watchlist, temp[6]->reviewedMovie, 1); // no review

    Movie *result = get_best_from_watchlist(watchlist);
    cr_assert(eq(ptr, result, temp[1]->reviewedMovie), "Expected the highest rated movie in the watchlist to be returned");

    h_destroy_watchlist(watchlist);
    // the movies are part of the reviews, so this should free them properly
    h_destroy_reviews(temp, 8);
    h_destroy_heap();
}

Test(test_get_best_from_watchlist, multiple_reviews) {
    h_initialize_heap(6);

    Movie *movieA = h_create_movie("Movie A", "Director A", 2000);
    Movie *movieB = h_create_movie("Movie B", "Director B", 2001);
    Movie *movieC = h_create_movie("Movie C", "Director C", 2002);

    /// NOTE: these ratings have the heap property
    int ratings[] = {8, 5, 7, 3, 4, 6};
    Movie *movies[] = {movieA, movieB, movieA, movieC, movieB, movieC};

    for (int i = 0; i < 6; i++) {
        Review *review = h_create_review(movies[i], ratings[i]);
        reviewList->backingArray[i] = review;
        reviewList->numElements++;
    }

    Watchlist *watchlist = h_create_watchlist("Kepler");

    h_add_movie(watchlist, movieC, 3); // highest rating 6
    h_add_movie(watchlist, movieA, 1); // highest rating 8
    h_add_movie(watchlist, movieB, 2); // highest rating 5

    Movie *result = get_best_from_watchlist(watchlist);
    cr_assert(eq(ptr, result, movieA), "Expected the highest rated movie in the watchlist to be returned");

    h_destroy_watchlist(watchlist);
    // movies are reused so we need to free them manually
    h_destroy_movie(movieA);
    h_destroy_movie(movieB);
    h_destroy_movie(movieC);
    for (int i = 0; i < 6; i++) {
        free(reviewList->backingArray[i]);
    }
    h_destroy_heap();
}
