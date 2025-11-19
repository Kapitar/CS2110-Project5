#include "ag_utils.h"
#include "../letterboxd.h"
#include <criterion/criterion.h>
#include <criterion/new/assert.h>

TestSuite(test_create_movie, .timeout = UNREASONABLY_LONG);

/* ===============================
 * Failure Create Movie Tests
 * =============================== */

// Null Args
Test(test_create_movie, null_name) {
    cr_assert(
        zero(ptr, create_movie(NULL, "Peter Jackson", 2025)),
        "Should return NULL for NULL name"
    );
}

Test(test_create_movie, null_director) {
    cr_assert(
        zero(ptr, create_movie("The Return of the King", NULL, 2025)),
        "Should return NULL for NULL director"
    );
}

// Invalid Args
Test(test_create_movie, empty_name) {
    cr_assert(
        zero(ptr, create_movie("", "Peter Jackson", 2025)),
        "Should return NULL for empty name"
    );
}
Test(test_create_movie, empty_director) {
    cr_assert(
        zero(ptr, create_movie("The Return of the King", "", 2025)),
        "Should return NULL for empty director"
    );
}
Test(test_create_movie, negative_release_year) {
    cr_assert(
        zero(ptr, create_movie("The Return of the King", "Peter Jackson", -1)),
        "Should return NULL for negative release year"
    );
}

//Malloc Failures
Test(test_create_movie, struct_malloc_failure) {
    // Test failing on struct malloc
    bytes_until_fail = sizeof(Movie) - 1;
    cr_assert(
        zero(ptr, create_movie("abc", "xyz", 2025)),
        "Should return NULL upon malloc failure"
    );
}

Test(test_create_movie, name_malloc_failure) {
    // Test failing on name malloc
    bytes_until_fail = sizeof(Movie) + 3;
    cr_assert(
        zero(ptr, create_movie("abc", "xyz", 2025)),
        "Should return NULL upon malloc failure"
    );
}

Test(test_create_movie, director_malloc_failure) {
    // Test failing on director malloc
    bytes_until_fail = sizeof(Movie) + 7;
    cr_assert(
        zero(ptr, create_movie("abc", "xyz", 2025)),
        "Should return NULL upon malloc failure"
    );
}

/* ===============================
 * Success Create Movie Tests
 * =============================== */

Test(test_create_movie, basic_success) {
    char movie_name[] = "The Return of the King";
    char movie_director[] = "Peter Jackson";
    int release_year = 2025;

    Movie* new_movie = create_movie(movie_name, movie_director, release_year);

    cr_assert(
        not(zero(ptr, new_movie)),
        "Expected new movie to be created"
    );
    cr_assert(
        eq(str, new_movie->name, movie_name),
        "Expected created movie's name to be correct"
    );
    cr_assert(
        eq(str, new_movie->director, movie_director),
        "Expected created movie's director to be correct"
    );
    cr_assert(
        eq(int, new_movie->releaseYear, release_year),
        "Expected created movie's release year to be correct"
    );
    h_destroy_movie(new_movie);
}

Test(test_create_movie, zero_release_year_success) {
    char movie_name[] = "The Dark Night";
    char movie_director[] = "Christopher Nolan";
    int release_year = 0;

    Movie* new_movie = create_movie(movie_name, movie_director, release_year);

    cr_assert(
        not(zero(ptr, new_movie)),
        "Expected new movie to be created"
    );
    cr_assert(
        eq(str, new_movie->name, movie_name),
        "Expected created movie's name to be correct"
    );
    cr_assert(
        eq(str, new_movie->director, movie_director),
        "Expected created movie's director to be correct"
    );
    cr_assert(
        eq(int, new_movie->releaseYear, release_year),
        "Expected created movie's release year to be correct"
    );
    h_destroy_movie(new_movie);
}
