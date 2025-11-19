#include "ag_utils.h"
#include "../letterboxd.h"
#include <criterion/criterion.h>
#include <criterion/new/assert.h>

TestSuite(test_remove_movie, .timeout = UNREASONABLY_LONG);

/* ===============================
 * Failure Remove Movie Tests
 * =============================== */

//Null args
Test(test_remove_movie, null_watchlist) {
    Movie *test_movie = h_create_movie("Tanay's Movie", "Tanay", 8);

    cr_assert(eq(type(Result), remove_movie(NULL, test_movie), FAILURE),
        "Should return FAILURE for NULL watchlist");

    h_destroy_movie(test_movie);
}
Test(test_remove_movie, null_movie) {
    Watchlist *test_watchlist = h_create_watchlist("Tanay");

    cr_assert(eq(type(Result), remove_movie(test_watchlist, NULL), FAILURE),
        "Should return FAILURE for NULL movie");

    h_destroy_watchlist(test_watchlist);
}

//Movie not in watchlist
Test(test_remove_movie, no_match_empty_watchlist) {
    Watchlist *test_watchlist = h_create_watchlist("Other Andy");
    Movie *test_movie = h_create_movie("Toy Story", "John Lasseter", 1995);

    cr_assert(eq(type(Result), remove_movie(test_watchlist, test_movie), FAILURE),
        "Should return FAILURE for movie not in watchlist");

    h_destroy_movie(test_movie);
    h_destroy_watchlist(test_watchlist);
}
Test(test_remove_movie, no_match) {
    Watchlist *test_watchlist = h_create_watchlist("Tanay");
    Movie *test_movie = h_create_movie("Toy Story", "John Lasseter", 1995);
    h_populate_watchlist(test_watchlist, 4);

    cr_assert(eq(type(Result), remove_movie(test_watchlist, NULL), FAILURE),
        "Should return FAILURE for NULL movie");

    h_destroy_movie(test_movie);
    h_destroy_populated_watchlist(test_watchlist);
}

/* ===============================
 * Success Remove Movie Tests
 * =============================== */

Test(test_remove_movie, basic_remove) {
    Watchlist *test_watchlist = h_create_watchlist("Rick");
    Movie *test_movie = h_create_movie("Toy Story", "John Lasseter", 1995);
    h_add_movie(test_watchlist, test_movie, 1);

    cr_assert(eq(type(Result), remove_movie(test_watchlist, test_movie), SUCCESS),
        "Should return SUCCESS for removing movie existing in watchlist");
    cr_assert(zero(ptr, test_watchlist->head),
        "Expected watchlist to be empty after removal");

    h_destroy_movie(test_movie);
    h_destroy_watchlist(test_watchlist);
}

Test(test_remove_movie, multiple_remove) {
    Watchlist *test_watchlist = h_create_watchlist("Other Andy");
    Movie *test_movie_1 = h_create_movie("Test Movie 1", "Henry", 2020);
    Movie *test_movie_2 = h_create_movie("Test Movie 2", "Shivani", 2003);
    Movie *test_movie_3 = h_create_movie("Test Movie 3", "Andy", 1998);
    Movie *test_movie_4 = h_create_movie("Test Movie 4", "Bianca", 2000);

    h_add_movie(test_watchlist, test_movie_1, 1);
    h_add_movie(test_watchlist, test_movie_2, 2);
    h_add_movie(test_watchlist, test_movie_3, 3);
    h_add_movie(test_watchlist, test_movie_4, 4);
    // Original Watchlist: 1 <-> 2 <-> 3 <-> 4

    // Removal 1: remove movie 1 (remove from front)
    // After: 2 <-> 3 <-> 4
    cr_assert(eq(type(Result), remove_movie(test_watchlist, test_movie_1), SUCCESS),
        "Should return SUCCESS for removing movie existing in watchlist");
    cr_assert(eq(ptr, test_watchlist->head->movie, test_movie_2),
        "Expected watchlist to point to the correct movie after removal");
    cr_assert(eq(ptr, test_watchlist->head->next->movie, test_movie_3),
        "Expected watchlist to point to the correct movie after removal");
    cr_assert(eq(ptr, test_watchlist->head->next->next->movie, test_movie_4),
        "Expected watchlist to point to the correct movie after removal");
    cr_assert(zero(ptr, test_watchlist->head->next->next->next),
        "Expected watchlist tail's next to be NULL after removal");
    cr_assert(zero(ptr, test_watchlist->head->prev),
        "Expected watchlist head's prev to be NULL after removal");
    cr_assert(eq(ptr, test_watchlist->head->next->prev->movie, test_movie_2),
        "Expected watchlist to point to the correct movie after removal");
    cr_assert(eq(ptr, test_watchlist->head->next->next->prev->movie, test_movie_3),
        "Expected watchlist to point to the correct movie after removal");
    
    // Removal 2: remove movie 3 (remove from middle)
    // After: 2 <-> 4
    cr_assert(eq(type(Result), remove_movie(test_watchlist, test_movie_3), SUCCESS),
        "Should return SUCCESS for removing movie existing in watchlist");
    cr_assert(eq(ptr, test_watchlist->head->movie, test_movie_2),
        "Expected watchlist to point to the correct movie after removal");
    cr_assert(eq(ptr, test_watchlist->head->next->movie, test_movie_4),
        "Expected watchlist to point to the correct movie after removal");
    cr_assert(zero(ptr, test_watchlist->head->prev),
        "Expected watchlist head's prev to be NULL after removal");
    cr_assert(eq(ptr, test_watchlist->head->next->prev->movie, test_movie_2),
        "Expected watchlist to point to the correct movie after removal");
    cr_assert(zero(ptr, test_watchlist->head->next->next),
        "Expected watchlist tail's next to be NULL after removal");

    // Removal 3: remove movie 4 (remove from back)
    // After: 2
    cr_assert(eq(type(Result), remove_movie(test_watchlist, test_movie_4), SUCCESS),
        "Should return SUCCESS for removing movie existing in watchlist");
    cr_assert(eq(ptr, test_watchlist->head->movie, test_movie_2),
        "Expected watchlist to point to the correct movie after removal");
    cr_assert(zero(ptr, test_watchlist->head->prev),
        "Expected watchlist head's prev to be NULL after removal");
    cr_assert(zero(ptr, test_watchlist->head->next),
        "Expected watchlist tail's next to be NULL after removal");

    // Removal 4:remove movie 2
    // After: empty
    cr_assert(eq(type(Result), remove_movie(test_watchlist, test_movie_2), SUCCESS),
        "Should return SUCCESS for removing movie existing in watchlist");
    cr_assert(zero(ptr, test_watchlist->head),
        "Expected watchlist to be empty after removal");

    h_destroy_movie(test_movie_1);
    h_destroy_movie(test_movie_2);
    h_destroy_movie(test_movie_3);
    h_destroy_movie(test_movie_4);
    h_destroy_watchlist(test_watchlist);
}
