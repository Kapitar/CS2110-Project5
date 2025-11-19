#include "ag_utils.h"
#include "../letterboxd.h"
#include <criterion/criterion.h>
#include <criterion/new/assert.h>

TestSuite(test_add_movie, .timeout = UNREASONABLY_LONG);

/* ===============================
 * Failure Add Movie Tests
 * =============================== */

// Null Args
Test(test_add_movie, null_watchlist) {
    Movie* test_movie = h_create_movie("TestName", "TestDirector", 2020);
    cr_assert(
        eq(int, add_movie(NULL, test_movie, 1), FAILURE),
        "Should return FAILURE for NULL watchlist"
    );
    h_destroy_movie(test_movie);
}
Test(test_add_movie, null_movie) {
    Watchlist* test_watchlist = h_create_watchlist("Henry");
    cr_assert(
        eq(int, add_movie(test_watchlist, NULL, 1), FAILURE),
        "Should return FAILURE for NULL movie"
    );
    h_destroy_watchlist(test_watchlist);
}

// Invalid Args
Test(test_add_movie, negative_day_watched) {
    Movie* test_movie = h_create_movie("TestName", "TestDirector", 2020);
    Watchlist* test_watchlist = h_create_watchlist("Daniel");

    cr_assert(
        eq(int, add_movie(test_watchlist, test_movie, -1), FAILURE),
        "Should return FAILURE for NULL movie"
    );

    h_destroy_movie(test_movie);
    h_destroy_watchlist(test_watchlist);
}
Test(test_add_movie, zero_day_watched) {
    Movie* test_movie = h_create_movie("TestName", "TestDirector", 2020);
    Watchlist* test_watchlist = h_create_watchlist("Rohit");

    cr_assert(
        eq(int, add_movie(test_watchlist, test_movie, 0), FAILURE),
        "Should return FAILURE for NULL movie"
    );

    h_destroy_movie(test_movie);
    h_destroy_watchlist(test_watchlist);
}

// Add existing movie
Test(test_add_movie, add_existing_movie_same_pointer) {
    Watchlist* test_watchlist = h_create_watchlist("Jason");
    Movie* test_movie = h_create_movie("TestName", "TestDirector", 2020);
    
    //First add should succeed
    cr_assert(
        eq(int, add_movie(test_watchlist, test_movie, 1), SUCCESS),
        "Should return SUCCESS for adding valid movie"
    );

    //Second add of same movie should fail
    cr_assert(
        eq(int, add_movie(test_watchlist, test_movie, 2), FAILURE),
        "Should return FAILURE for adding duplicate movie"
    );

    h_destroy_movie(test_movie);
    h_destroy_watchlist(test_watchlist);
}

Test(test_add_movie, add_existing_movie_different_pointer) {
    Watchlist* test_watchlist = h_create_watchlist("Huy");
    Movie* test_movie = h_create_movie("TestName", "TestDirector", 2020);
    Movie* duplicate_test_movie = h_create_movie("TestName", "TestDirector", 2020);
    
    //First add should succeed
    cr_assert(
        eq(int, add_movie(test_watchlist, test_movie, 1), SUCCESS),
        "Should return SUCCESS for adding valid movie"
    );

    //Second add of same movie should fail
    cr_assert(
        eq(int, add_movie(test_watchlist, duplicate_test_movie, 2), FAILURE),
        "Should return FAILURE for adding duplicate movie"
    );

    h_destroy_movie(test_movie);
    h_destroy_movie(duplicate_test_movie);
    h_destroy_watchlist(test_watchlist);
}

//Malloc Failure
Test(test_add_movie, malloc_failure) {
    // Test failing on watchlist node malloc
    Watchlist* test_watchlist = h_create_watchlist("Bianca");
    Movie* test_movie = h_create_movie("The Godfather", "Francis Coppola", 1972);

    bytes_until_fail = sizeof(WatchlistNode) - 1;
    cr_assert(
        eq(int, add_movie(test_watchlist, test_movie, 20), FAILURE),
        "Should return FAILURE upon malloc failure"
    );

    h_destroy_movie(test_movie);
    h_destroy_watchlist(test_watchlist);
}

/* ===============================
 * Success Add Movie Tests
 * =============================== */

Test(test_add_movie, basic_success) {
    Watchlist* test_watchlist = h_create_watchlist("Shivani");
    Movie* test_movie = h_create_movie("The Godfather", "Francis Coppola", 1972);
    int test_day_added = 10;

    cr_assert(eq(int, add_movie(test_watchlist, test_movie, test_day_added), SUCCESS),
        "Should return SUCCESS upon adding valid movie");
    cr_assert(not(zero(ptr, test_watchlist->head)),
        "Watchlist head should not be null after movie successfully added");
    cr_assert(zero(ptr, test_watchlist->head->prev),
        "Watchlist head should be null after only one movie added");
    cr_assert(zero(ptr, test_watchlist->head->next),
        "Watchlist head should be null after only one movie added");
    cr_assert(eq(ptr, test_watchlist->head->movie, test_movie),
        "Watchlist head should point to the correct movie");
    cr_assert(eq(int, test_watchlist->head->dayAdded, test_day_added),
        "Watchlist head should have correct day added");

    h_destroy_movie(test_movie);
    h_destroy_watchlist(test_watchlist);
}

Test(test_add_movie, duplicate_name_director_success) {
    Watchlist* test_watchlist = h_create_watchlist("Navin");
    Movie* test_movie = h_create_movie("Casablanca", "Michael Curtiz", 1943);
    Movie* duplicate_test_movie = h_create_movie("Casablanca", "Michael Curtiz", 2020); // diff releaseDate
    int days[2] = {8, 10};

    //Add movies
    cr_assert(eq(int, add_movie(test_watchlist, test_movie, days[0]), SUCCESS),
        "Should return SUCCESS upon adding valid movie");
    cr_assert(eq(int, add_movie(test_watchlist, duplicate_test_movie, days[1]), SUCCESS),
        "Should return SUCCESS upon adding valid movie");

    //Verify head node (first movie added)
    WatchlistNode* head_node = test_watchlist->head;
    cr_assert(not(zero(ptr, head_node)),
        "Watchlist head should not be NULL after movie successfully added");
    cr_assert(zero(ptr, head_node->prev),
        "Watchlist head's prev should be NULL");
    cr_assert(eq(ptr, head_node->movie, test_movie),
        "Watchlist head should point to the correct movie");
    cr_assert(eq(int, head_node->dayAdded, days[0]),
        "Watchlist head should have correct day added");
    cr_assert(not(zero(ptr, head_node->next)),
        "Watchlist head's next should not be NULL");

    //Verify second node (second movie added)
    WatchlistNode* second_node = head_node->next;
    cr_assert(not(zero(ptr, second_node)),
        "Second node should not be NULL");
    cr_assert(eq(ptr, second_node->prev, head_node),
        "Second node's prev should point to correct node");
    cr_assert(eq(ptr, second_node->movie, duplicate_test_movie),
        "Second node should point to the correct movie");
    cr_assert(eq(int, second_node->dayAdded, days[1]),
        "Second node should have correct day added");
    cr_assert(zero(ptr, second_node->next),
        "Second node's next should be null (it's the tail)");

    //Destroy malloced memory
    h_destroy_movie(test_movie);
    h_destroy_movie(duplicate_test_movie);
    h_destroy_watchlist(test_watchlist);
}

Test(test_add_movie, multiple_add_success) {
    Watchlist* test_watchlist = h_create_watchlist("Andy");
    Movie* movies[4] = {
        h_create_movie("Casablanca", "Michael Curtiz", 1943),
        h_create_movie("Pulp Fuction", "Quentin Tarantino", 1994),
        h_create_movie("Ratatouille", "Brad Bird", 2007),
        h_create_movie("Wicked", "Jon Chu", 2024),
    };
    int days[4] = {8, 10, 11, 33};

    //Add movies
    for (int i = 0; i < 4; i++) {
        cr_assert(eq(int, add_movie(test_watchlist, movies[i], days[i]), SUCCESS),
            "Should return SUCCESS upon adding valid movie %d", i);
    }

    //FORWARD PASS
    //Starts from head node, ensures data and next pointers correct
    WatchlistNode* curr = test_watchlist->head;
    WatchlistNode* prev = NULL;
    
    for (int i = 0; i < 4; i++) {
        cr_assert(not(zero(ptr, curr)),
            "Node %d should exist during forward traversal", i);
        
        //Verify movies and day added
        cr_assert(eq(ptr, curr->movie, movies[i]),
            "Node %d should point to correct movie", i);
        cr_assert(eq(int, curr->dayAdded, days[i]),
            "Node %d should have correct day added", i);
        
        //Verify prev pointer points to correct node
        cr_assert(eq(ptr, curr->prev, prev),
            "Node %d's prev should point to previous node", i);
        
        //Verify next pointer exists
        if (i == 3) { // tail node
            cr_assert(zero(ptr, curr->next),
                "Last node's next should be NULL");
        } else {
            cr_assert(not(zero(ptr, curr->next)),
                "Node %d's next should not be NULL", i);
        }
        
        prev = curr;
        curr = curr->next;
    }

    // BACKWARD PASS
    // Starts from tail node (prev from forward pass), ensures data and prev pointers correct
    curr = prev; // tail
    WatchlistNode* next_node = NULL;
    
    for (int i = 3; i >= 0; i--) {
        cr_assert(not(zero(ptr, curr)),
            "Node %d should exist during backward traversal", i);
        
        // Verify data
        cr_assert(eq(ptr, curr->movie, movies[i]),
            "Watchlist node %d should point to correct movie", i);
        cr_assert(eq(int, curr->dayAdded, days[i]),
            "Watchlist node %d should have correct day added", i);
        
        // Verify next pointer points to correct node
        cr_assert(eq(ptr, curr->next, next_node),
            "Watchlist node %d's next should point to correct node", i);
        
        // Verify next pointer exists
        if (i == 0) { // head node
            cr_assert(zero(ptr, curr->prev),
                "Head node's prev should be NULL");
        } else {
            cr_assert(not(zero(ptr, curr->prev)),
                "Watchlist node %d's prev should not be NULL", i);
        }
        next_node = curr;
        curr = curr->prev;
    }

    //Destroy malloced memory
    for (int i = 0; i < 4; i++) {
        h_destroy_movie(movies[i]);
    }
    h_destroy_watchlist(test_watchlist);
}
