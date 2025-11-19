/**
 * CS 2110 - Fall 2025 - Project 5
 *
 * @author YOUR NAME HERE
 */

#include "letterboxd.h"

// Global variable - do not change this!
Heap *reviewList;

/** INITIALIZERS */

/**
 * Creates a new movie.
 * 
 * @param name the name of the movie
 * @param director the director of the movie
 * @param releaseYear the release year of the movie
 * 
 * @return NULL upon invalid arguments or malloc failure, a pointer to the new movie otherwise
 */
Movie *create_movie(char *name, char *director, int releaseYear){
    UNUSED(name);
    UNUSED(director);
    UNUSED(releaseYear);
    return INCOMPLETE_PTR;
}

/**
 * Creates a new review.
 * 
 * @param movie the movie that the review is about
 * @param rating a number 1-10 representing the number of stars the review gave the movie
 * 
 * @return NULL upon invalid arguments or malloc failure, a pointer to the new review otherwise
 */
Review *create_review(Movie *movie, int rating) {
    UNUSED(movie);
    UNUSED(rating);
    return INCOMPLETE_PTR;
}

/** 
 * Creates a new watchlist.
 * 
 * @param owner the name of the owner of the watchlist
 * 
 * @return NULL upon invalid arguments or malloc failure, a pointer to the new review otherwise
 */
Watchlist *create_watchlist(char *owner) {
    UNUSED(owner);
    return INCOMPLETE_PTR;
}

/**
 * Initializes the review list as a heap.
 * 
 * @param initialCapacity the initial capacity of the backing array of the heap
 * 
 * @return FAILURE upon malloc failure or invalid initial capacity and SUCCESS otherwise
 */
int initialize_heap(int initialCapacity) {
    UNUSED(initialCapacity);
    return INCOMPLETE;
}


/** WATCHLIST OPERATIONS */

/**
 * Adds a movie to a specific watchlist.
 * 
 * @param watchlist the watchlist to add to
 * @param movie the movie to add
 * @param dayAdded the day the movie was watched
 * 
 * @return FAILURE upon malloc failure, invalid inputs, or duplicate movie and SUCCESS otherwise
 */
int add_movie(Watchlist *watchlist, Movie *movie, int dayAdded) {
    UNUSED(watchlist);
    UNUSED(movie);
    UNUSED(dayAdded);
    return INCOMPLETE;
}

/**
 * Removes a movie from a specific watchlist, if it exists there.
 * 
 * @param watchlist the watchlist to remove from
 * @param movie the movie to remove
 * 
 * @return FAILURE upon invalid inputs, or movie not in watchlist and SUCCESS otherwise
 */
int remove_movie(Watchlist *watchlist, Movie *movie) {
    UNUSED(watchlist);
    UNUSED(movie);
    return INCOMPLETE;
}

/**
 * Checks if a movie is in a specific watchlist.
 * 
 * @param watchlist the watchlist to check
 * @param movie the movie to check for
 * 
 * @return FAILURE upon invalid inputs, or movie not in watchlist and SUCCESS otherwise
 */
int watchlist_contains_movie(Watchlist *watchlist, Movie *movie) {
    UNUSED(watchlist);
    UNUSED(movie);
    return INCOMPLETE;
}

/** HEAP FUNCTIONS */

/** 
 * Adds a review to the review list. Don't forget to call heapify!
 * 
 * @param review the review to add
 * 
 * @return FAILURE upon malloc failure or invalid inputs and SUCCESS otherwise
 */
int post_review(Review *review) {
    UNUSED(review);
    return INCOMPLETE;
}

/**
 * Resizes the review list to two times its size.
 * 
 * @return FAILURE if the review list in uninitialized, SUCCESS otherwise
 */
int resize_review_list(void) {
    return INCOMPLETE;
}

/**
 * Checks if a review is in the review list.
 * 
 * @param review the review to look for
 * 
 * @return FAILURE if the review is not found or the input is invalid, SUCCESS otherwise
 */
int review_posted(Review *review) {
    UNUSED(review);
    return INCOMPLETE;
}

/**
 * Moves elements of the backing array of the review list into an order to maintain heap property.
 * 
 * @param index the index of the new element (that could be out of order)
 * 
 * @return FAILURE upon invalid inputs and SUCCESS otherwise
 */
int heapify(int index) {
    if (reviewList == NULL || index >= reviewList -> numElements || index < 0) {
        return FAILURE;
    }

    if (index == 0) {
        return SUCCESS;
    }
    
    int parent = (index - 1) / 2;
    Review *parentReview = *(reviewList -> backingArray + parent);
    Review *childReview = *(reviewList -> backingArray + index);

    int parentRating = parentReview -> rating;
    int childRating = childReview -> rating;

    if (childRating > parentRating) {
        swap(index, parent);
        heapify(parent);
    }
    return SUCCESS;
}

/**
 * Swaps elements at indices i and j in reviewList's backing array.
 * 
 * @param i one index to swap
 * @param j the other index to swap
 * 
 * @return FAILURE upon invalid inputs and SUCCESS otherwise
 */
int swap(int i, int j) {
    UNUSED(i);
    UNUSED(j);
    return INCOMPLETE;
}

/**
 * Gets the highest rated movie out of all posted reviews.
 * 
 * @return A pointer to the highest rated movie
 */
Movie *get_highest_rated_movie(void) {
    return INCOMPLETE_PTR;
}

/**
 * Gets the highest rated movie in the given watchlist.
 * 
 * @param watchlist the watchlist to check against
 * 
 * @return A pointer to the highest rated movie that also exists in the watchlist
 */
Movie *get_best_from_watchlist(Watchlist *watchlist) {
    UNUSED(watchlist);
    return INCOMPLETE_PTR;
}

/** DESTROYING */

/**
 * Destroys and frees the given watchlist.
 * 
 * @param watchlist the watchlist to destroy
 * 
 * @return FAILURE upon invalid inputs and SUCCESS otherwise
 */
int destroy_watchlist(Watchlist *watchlist) {
    UNUSED(watchlist);
    return INCOMPLETE;
}

/**
 * Destroys and frees the review list.
 * 
 * @return FAIURE if the review list is uninitialized, SUCCESS otherwise
 */
int destroy_reviewlist(void) {
    return INCOMPLETE;
}
