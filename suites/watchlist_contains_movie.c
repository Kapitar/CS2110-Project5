#include "ag_utils.h"
#include "../letterboxd.h"
#include <criterion/criterion.h>
#include <criterion/new/assert.h>

TestSuite(test_watchlist_contains_movie, .timeout = UNREASONABLY_LONG);

/* ===============================
 * Watchlist Contains Movie Tests
 * =============================== */

//Null Args
Test(test_watchlist_contains_movie, null_watchlist) {
    Movie* movie = h_create_movie("Test Movie", "Tanay", 2006);

    cr_assert(eq(type(Result), watchlist_contains_movie(NULL, movie), FAILURE),
    "Should return FAILURE for NULL watchlist");

    h_destroy_movie(movie);
}

Test(test_watchlist_contains_movie, null_movie) {
    Watchlist* watchlist = h_create_watchlist("Henry");

    cr_assert(eq(type(Result), watchlist_contains_movie(watchlist, NULL), FAILURE),
    "Should return FAILURE for NULL movie");

    h_destroy_watchlist(watchlist);
}

//Movie not in watchlist
Test(test_watchlist_contains_movie, failure_empty_watchlist) {
    Watchlist* watchlist = h_create_watchlist("Henry");
    Movie* movie = h_create_movie("Test Movie", "Test Director", 2021);

    cr_assert(eq(type(Result), watchlist_contains_movie(watchlist, movie), FAILURE),
    "Should return FAILURE for empty watchlist");

    h_destroy_watchlist(watchlist);
    h_destroy_movie(movie);
}

Test(test_watchlist_contains_movie, failure_nonempty_watchlist) {
    Watchlist* watchlist = h_create_watchlist("Bianca");
    h_populate_watchlist(watchlist, 5);

    Movie* movie = h_create_movie("The Shining", "Stanley Kubrick", 1980);

    cr_assert(eq(type(Result), watchlist_contains_movie(watchlist, movie), FAILURE),
    "Should return FAILURE when movie not in watchlist");

    h_destroy_populated_watchlist(watchlist);
    h_destroy_movie(movie);
}

//Success 
Test(test_watchlist_contains_movie, basic_success) {
    Watchlist* watchlist = h_create_watchlist("Andy");
    h_populate_watchlist(watchlist, 10);

    Movie* movie = h_create_movie("The Shawshank Redemption", "Frank Darabont", 1994);

    cr_assert(eq(type(Result), watchlist_contains_movie(watchlist, movie), SUCCESS),
    "Should return SUCCESS for when watchlist contains movie");

    h_destroy_populated_watchlist(watchlist);
    h_destroy_movie(movie);
}

//Success and failure
Test(test_watchlist_contains_movie, multiple_success_and_failure) {
    Watchlist* watchlist = h_create_watchlist("Andy");
    h_populate_watchlist(watchlist, 10);

    Movie* movie_1 = h_create_movie("The Shawshank Redemption", "Frank Darabont", 1994);
    Movie* movie_2 = h_create_movie("Test Movie", "Tanay", 2006);
    Movie* movie_3 = h_create_movie("The Dark Knight", "Christopher Nolan", 2008);
    Movie* movie_4 = h_create_movie("The Shining", "Stanley Kubrick", 1980);

    cr_assert(eq(type(Result), watchlist_contains_movie(watchlist, movie_1), SUCCESS),
    "Should return SUCCESS for when watchlist contains movie");
    cr_assert(eq(type(Result), watchlist_contains_movie(watchlist, movie_2), FAILURE),
    "Should return FAILURE when movie not in watchlist");
    cr_assert(eq(type(Result), watchlist_contains_movie(watchlist, movie_3), SUCCESS),
    "Should return SUCCESS for when watchlist contains movie");
    cr_assert(eq(type(Result), watchlist_contains_movie(watchlist, movie_4), FAILURE),
    "Should return FAILURE when movie not in watchlist");

    h_destroy_populated_watchlist(watchlist);
    h_destroy_movie(movie_1);
    h_destroy_movie(movie_2);
    h_destroy_movie(movie_3);
    h_destroy_movie(movie_4);
}