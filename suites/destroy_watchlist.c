#include "ag_utils.h"
#include "../letterboxd.h"
#include <criterion/criterion.h>
#include <criterion/new/assert.h>

TestSuite(test_destroy_watchlist, .timeout = UNREASONABLY_LONG);

/* ===============================
 * Destroy Watchlist Tests
 * =============================== */

Test(test_destroy_watchlist, null_watchlist) {
    cr_assert(eq(type(Result), destroy_watchlist(NULL), FAILURE),
    "Expected FAILURE when watchlist is NULL");
}

Test(test_destroy_watchlist, empty_watchlist) {
    Watchlist *watchlist = h_create_watchlist("Tanay");
    cr_assert(eq(type(Result), destroy_watchlist(watchlist), SUCCESS),
    "Expected SUCCESS when watchlist is destroyed");

}

Test(test_destroy_watchlist, populated_watchlist) {
    h_initialize_heap(5);
    Review **temp_reviews = h_prepare_reviews(5);

    Watchlist *watchlist = h_create_watchlist("Rohit");

    for (int i = 0; i < 5; i++) {
        h_add_movie(watchlist, temp_reviews[i]->reviewedMovie, (i + 1) * 3 % 7);
    }

    cr_assert(eq(type(Result), destroy_watchlist(watchlist),
    SUCCESS), "Expected SUCCESS when watchlist is destroyed");

    //assert ptrs to reviews and movies were not freed
    for (int i = 0; i < 5; i++) {
        cr_assert(not(zero(ptr, temp_reviews[i]->reviewedMovie)), 
        "Expected movie at index %d to still exist", i);
    }

    h_destroy_reviews(temp_reviews, 5); // also destroys movies
    h_destroy_heap();
}
