#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#ifndef WORLD_SIZE
#define WORLD_SIZE 8
#endif

int usr_input(void)
/**
 * takes in user input on number of simulations
 * returns number of simulations to be ran
*/
{
    int simulations;
    printf("How many simulations?\n");
    scanf("%d", &simulations);
    return (simulations);
}

int die(int low, int high)
/**
 * Returns a randomly picked number btwn low and high
*/
{
    int die = lrand48() % 4;
    return die;
}

bool size(x, y);
/**
 * checks if a value is at the bounds of worldsize
 * 
*/


int main(void)
{
    srand48(time(NULL)) ;

    int simulations = usr_input();
    int homex = WORLD_SIZE/2;
    int homey = WORLD_SIZE/2;

    die(0,4);

    for(int count = 0; count <= simulations; count++)
    {
        // get random initial locations for each simulation
        int loc_rabX = die(0,WORLD_SIZE);
        int loc_rabY = die(0,WORLD_SIZE);
        int loc_foxX = die(0,WORLD_SIZE);
        int loc_foxY = die(0,WORLD_SIZE);
        int foodx = die(0,WORLD_SIZE);
        int foody = die(0,WORLD_SIZE);

        int movt = die(1, 5); // 1-north, 2-south, 3-east, 4-west
        bool flag_food;
        bool north;
        bool south;
        bool east;
        bool west;
        int steps = 1;
        for (steps = 1; !(loc_rabX == homex && loc_rabY == homey); steps += 1)
        {
            if (loc_foxX == loc_rabX && loc_foxY == loc_rabY)
            // rabbit eaten
            {
                printf("Fox catches the rabbit in %d steps", steps);
                continue;
            }
            // if food is found
            if (loc_foxX == foodx && loc_foxY == foody){flag_food = true;}




            if (movt = 1) {north = true;}
            if (movt = 2) {north = false;}
            if (movt = 3) {east = true;}
            if (movt = 4) {east = false;}
            
            if (movt == 1 || movt ==2)
            // movements along y axis (north or south)
            {
                if (north = true && loc_foxY >= 1)
                {
                    if (loc_foxY == 1)
                    {
                        north = false;  // flag to turn back to south
                    }
                    else{
                        loc_foxY = loc_foxY - 1; //continue going north
                    }

                    steps += 1;
                }
                if (north = false && loc_foxY <= WORLD_SIZE)
                {
                    if (loc_foxY == WORLD_SIZE)
                    {
                        north = true; // flag to turn back to north
                    }
                    else
                    {
                        loc_foxY = loc_foxY + 1;  //continue goinf south;
                    }

                    steps += 1;
                }
            }

            else if (movt == 2 || movt == 3)
            // movements along x axis (east or west)
            {
                if (east = true && loc_foxX >= 1)
                {
                    if (loc_foxX == 1)
                    {
                        east = false;  // flag to turn back to west
                    }
                    else{
                        loc_foxX = loc_foxX - 1; //continue going east
                    }

                    steps += 1;
                }
                if (east = false && loc_foxX <= WORLD_SIZE)
                {
                    if (loc_foxX == WORLD_SIZE)
                    {
                        east = true; // flag to turn back to east
                    }
                    else
                    {
                        loc_foxX = loc_foxX + 1;  //continue goinf west;
                    }

                    steps += 1;
                }
            }



            //fox moves
            if(movt == 1 && loc_foxY > 1 && north == true)
            {
                loc_foxY -= 1;
            }   //add along y axis for north
            else if(movt == 1 && loc_foxY == 1)
            {
                north = false;
                loc_foxY += 1;
            }
            if(movt == 2){loc_foxY += 1;}   //minus along y axis for south
            if(movt == 3){loc_foxX += 1;}   //add along x axis for east
            if(movt == 4){loc_foxX -= 1;}   //minus along x axis for west

            //rabbit moves
            if(movt == 1){loc_rabY -= 1;}   //add along y axis for north
            if(movt == 2){loc_rabY += 1;}   //minus along y axis for south
            if(movt == 3){loc_rabX += 1;}   //add along x axis for east
            if(movt == 4){loc_rabX -= 1;}   //minus along x axis for west
        }
        if (flag_food == true)
        {
            printf("Rabbit makes it home in %d steps and is fed", steps);
        }
        else
        {
            printf("Rabbit makes it home in %d steps but is hungry", steps);
        }
    }
    return 0;
}

/**
 * 1. roll die x4- get rabbit, food, fox loc
 * 2. roll die *2 - choose movt for rabbit and fox
 * 
 * 3. define loc_rabbit and loc_fox and loc_food
 *      rabx, raby = random (0,4) twice
 *      foodx, foody = random (0,4)
 *      foxx, foxy = random (0,4)
 *      homex, homey = (4,4)
 * 4. roll 4 side die and assign initial movement
 * 5. define count 
 * 6. flag_food = false
 * 
 * loop using user input for no. of sims
    * dir_fox_x = random()
    * dir_fox_y = random()
    * dir_rab_x = random()
    * dir_rab_y = random()
    * loop (Do this till loc_rabbit == home )
    *      
    *      move fox by 1
    *      if (dir_fox == 0 and locfoxy !> : 3)
    *           locfoxy += 1 #add along y axis for north
    * 
    *       if (dir_fox == 0 and locfoxy !> : 3)
    *           locfoxy += 1 #add along y axis for north
    *      count++
    * 
    *      if loc_rabbit == loc_fox:
    *          print (rabbit dead)
    *          print (moves)
    *          return count
    *      if loc_rabbit == loc_food
    *          flag_food == true
    * 
    * if flag_food == true:
    *      print (moves, rabbit home with food)
    * else:
    *      print (moves, rabbit home but hungry)
*/