// Standard headers
#include <stdio.h>

// Internal headers
#include "direction.h"
#include "position.h"
#include "spy.h"
#include <stdlib.h>

// Main header
#include "attacker.h"

position_t last_position = { -1, -1 };
direction_t last_direction = DIR_LEFT;

// Functions

// avoid repeating the same movement if an obstacle is found
int test_direction(position_t attacker_position, direction_t direction){
    if (equal_positions(last_position, attacker_position) && last_direction.i == direction.i && last_direction.j == direction.j){
        return 0;
    }
    return 1;
}

/**
 * Main algorithm to move Attacker player in a Game.
 * Given the player position, it should decide the next direction
 * they will take in the field.
 */
direction_t execute_attacker_strategy(position_t attacker_position,
                                      Spy defender_spy){
    direction_t prefered_directions[] = {DIR_UP_RIGHT, DIR_RIGHT, DIR_DOWN_RIGHT};
    int tested_directions[3];
    int tested_directions_amount = 0;
    int random_direction_index = rand() % 3;
    // tries to move in one of the preferred directions, randomly chosen
    while (tested_directions_amount < 3 
        && !test_direction(attacker_position, prefered_directions[random_direction_index])){
        tested_directions[random_direction_index] = 1;
        tested_directions_amount +=1;
        random_direction_index = rand() % 3;
    }
    if (tested_directions_amount < 3) {
        last_position = attacker_position;
        last_direction = prefered_directions[random_direction_index]; 
        return prefered_directions[random_direction_index];
    }
    // if unable to move in all of the preferred directions, move towards one of the "spare" directions left, randomly chosen
    direction_t spare_directions[] = {DIR_LEFT, DIR_UP, DIR_DOWN, DIR_UP_LEFT, DIR_DOWN_LEFT};
    random_direction_index = rand() % 5;
    while (!test_direction(attacker_position, spare_directions[random_direction_index])){
        random_direction_index = rand()%5;
    }
    last_position = attacker_position;
    last_direction = spare_directions[random_direction_index]; 
    return spare_directions[random_direction_index];
}


/*----------------------------------------------------------------------------*/
