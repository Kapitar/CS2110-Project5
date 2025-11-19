#ifndef AG_UTILS_H
#define AG_UTILS_H

#include "../letterboxd.h"

// The Makefile script + Criterion bugs are causing weird interactions.
// `make run-tests` cannot be ^C'd (it has to be ^Z'd).
//
// As such, we need to impose a timeout so that tests will eventually stop
// in cases of infinite loops.
//
// However, we do not want to impose a timeout when debugging with GDB
// (since that wouldn't be a fun debugging experience).
//
// One way of doing this is defining ./tests --timeout N in make run-tests;
// however, this requires specifying a non-default timeout (because Criterion bug).
// You can't set +INFINITY because +INFINITY (also due to a bug) acts as a 0s timeout.
#define UNREASONABLY_LONG 86400

// These are helper functions for the autograder.
// You may not use these for your solution.
typedef int Result;
char *cr_user_Result_tostr(Result *value);
int cr_user_Result_eq(Result *a, Result *b);

//Initialization helpers
Movie *h_create_movie(char *name, char *director, int releaseYear);
Watchlist *h_create_watchlist(char *owner);
void h_initialize_heap(int initialCapacity);
Review *h_create_review(Movie *movie, int rating);

//Destroy helpers
void h_destroy_movie(Movie *movie);
void h_destroy_heap(void); // check
void h_destroy_review(Review *review);
void h_destroy_reviews(Review **reviews, int num_reviews);
void h_destroy_watchlist(Watchlist *watchlist);
void h_destroy_populated_watchlist(Watchlist *watchlist);

//Movie helpers
int h_movieeq(Movie *m1, Movie *m2); // check if need null check
void h_add_movie(Watchlist *watchlist, Movie *movie, int dayWatched); // check over to make sure don't need checks

//Review helpers
Review **h_prepare_reviews(int num_reviews); 

//Watchlist helpers
void h_populate_watchlist(Watchlist *watchlist, int num_movies);

#endif
