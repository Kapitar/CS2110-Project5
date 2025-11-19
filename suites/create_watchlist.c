#include "ag_utils.h"
#include "../letterboxd.h"
#include <criterion/criterion.h>
#include <criterion/new/assert.h>

TestSuite(test_create_watchlist, .timeout = UNREASONABLY_LONG);

/* ===============================
 * Failure Create Watchlist Tests
 * =============================== */
//Null arguments
Test(test_create_watchlist, null_owner) {
    cr_assert(
        zero(ptr, create_watchlist(NULL)),
        "Should return NULL for NULL owner"
    );
}

//Empty arguments
Test(test_create_watchlist, empty_owner) {
    cr_assert(
        zero(ptr, create_watchlist("")),
        "Should return NULL for empty owner"
    );
}

//Malloc Failure
Test(test_create_watchlist, malloc_failure_struct) {
    // Test failing on struct malloc
    bytes_until_fail = sizeof(Watchlist) - 1;
    cr_assert(
        zero(ptr, create_watchlist("abc")),
        "Should return NULL upon malloc failure"
    );
}
Test(test_create_watchlist, malloc_failure_owner) {
    // Test failing on owner malloc
    bytes_until_fail = sizeof(Watchlist) + 3;
    cr_assert(
        zero(ptr, create_watchlist("abc")),
        "Should return NULL upon malloc failure"
    );
}

/* ===============================
 * Success Create Watchlist Tests
 * =============================== */
Test(test_create_watchlist, success) {
    char owner[] = "Ralof";
    Watchlist* watchlist = create_watchlist(owner);

    cr_assert(
        not(zero(ptr, watchlist)),
        "Should return valid pointer upon success"
    );
    cr_assert(
        zero(ptr, watchlist->head),
        "Expected created watchlist's head to be correct"
    );
    cr_assert(
        eq(str, watchlist->owner, owner),
        "Expected created watchlist's owner to be correct"
    );
    h_destroy_watchlist(watchlist);
}
