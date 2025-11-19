#ifndef LETTERBOXD_H
#define LETTERBOXD_H

/* DO NOT MODIFY FILE */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UNUSED(x) ((void)x)
#define FAILURE 0
#define SUCCESS 1

#define INCOMPLETE -1
#define INCOMPLETE_PTR NULL

#include "suites/fakemalloc.h"


typedef struct Movie {
    char *name;
    char *director;
    int releaseYear;
} Movie;

typedef struct Review {
    Movie *reviewedMovie;
    int rating;
} Review;

typedef struct WatchlistNode {
    struct WatchlistNode *next;
    struct WatchlistNode *prev;
    Movie *movie;
    int dayAdded;
} WatchlistNode;

typedef struct Watchlist {
    WatchlistNode *head;
    char *owner;
} Watchlist;

typedef struct Heap {
    Review **backingArray;
    int backingArrayLength;
    int numElements;
} Heap;

extern Heap *reviewList;

// Initializers
Movie *create_movie(char *name, char *director, int releaseYear);
Review *create_review(Movie *movie, int rating);
Watchlist *create_watchlist(char *owner);
int initialize_heap(int initialCapacity);

// Watchlist operations
int add_movie(Watchlist *watchlist, Movie *movie, int dayAdded);
int remove_movie(Watchlist *watchlist, Movie *movie);
int watchlist_contains_movie(Watchlist *watchlist, Movie *movie);

// Heap operations
int post_review(Review *review);
int resize_review_list(void);
int review_posted(Review *review);
int heapify(int index);
int swap(int i, int j);
Movie *get_highest_rated_movie(void);
Movie *get_best_from_watchlist(Watchlist *watchlist);

// Destroying
int destroy_watchlist(Watchlist *watchlist);
int destroy_reviewlist(void);

#endif