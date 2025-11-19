#include "ag_utils.h"
#include "../letterboxd.h"
#include <criterion/criterion.h>
#include <criterion/new/assert.h>

TestSuite(test_destroy_reviewlist, .timeout = UNREASONABLY_LONG);

/* ===============================
 * Destroy Review List Tests
 * =============================== */

Test(test_destroy_reviewlist, null_reviewlist) {
    cr_assert(eq(type(Result), destroy_reviewlist(), FAILURE),
    "Expected FAILURE when review list is uninitialized");
}

Test(test_destroy_reviewlist, empty_backing_array) {
    h_initialize_heap(4);
    cr_assert(eq(type(Result), destroy_reviewlist(), SUCCESS), 
    "Expected SUCCESS when review list is destroyed");
}

Test(test_destroy_reviewlist, populated_input) {
    h_initialize_heap(4);
    Review **reviews = h_prepare_reviews(4);

    for (int i = 0; i < 4; i++) {
        reviewList->backingArray[i] = reviews[i];
        reviewList->numElements++;
    }

    cr_assert(eq(type(Result), destroy_reviewlist(), SUCCESS), 
    "Expected SUCCESS when review list is destroyed");

    
    for (int i = 0; i < 4; i++) {
        cr_assert(not(zero(ptr, reviews[i]->reviewedMovie)), 
        "Expected movie at index %d to still exist", i);
    }

    h_destroy_reviews(reviews, 4);
}
