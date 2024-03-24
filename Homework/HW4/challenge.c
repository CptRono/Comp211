#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

//define size of game
#ifndef SIZE 
#define SIZE 3
#define TOTALCOLORS 6
#define ALLOWEDGUESSES 4
#endif

enum color{GREEN, BLUE, RED, YELLOW, WHITE, ORANGE};

void printarray(int array[])
//prints an array of integers --> for testing purposes
{
    printf("\n");
    for (int i = 0; i < SIZE; i += 1)
    {
        printf("%d,", array[i]);
    }
    printf("\n");
}

void printchararray(char array[])
{
    for (int i = 0; i < SIZE; i += 1)
    {
        printf("%c", array[i]);
    }
    printf("\n");
}

bool duplicate(int array[], int lastindex)
//check whether the LAST element of an array is a duplicate of another prev element
//array MUST have at least TWO elements
{
    for (int j = lastindex - 1; j >= 0; j--)
    {
        if (array[lastindex] == array[j])
        {
            return true;
        }
    }
    return false;
}
// generate string 
void generatestring(int codemaker[])
{
    srand48(time(NULL));

    for(int i=0; i<SIZE; i+=1)
    {
        codemaker[i] = lrand48() % TOTALCOLORS;

        //check if generated string has a duplicate up to this point
        while (i > 0 && duplicate(codemaker, i) == true)
        {
            codemaker[i] = lrand48() % TOTALCOLORS;
        }
    }
}
//input string and play

//mapping letters entered by user to colors
void mapcolors(char codebreaker[], int codebreaker_colors[])
{
    for(int i = 0; i < SIZE; i += 1)
    {
        // switch syntax --> switch(variable){case value1:statements; break;}
        switch (codebreaker[i])
        {
            case 'G': codebreaker_colors[i] = GREEN; break;
            case 'B': codebreaker_colors[i] = BLUE; break;
            case 'R': codebreaker_colors[i] = RED; break;
            case 'Y': codebreaker_colors[i] = YELLOW; break;
            case 'W': codebreaker_colors[i] = WHITE; break;
            case 'O': codebreaker_colors[i] = ORANGE; break;
        }
    }
}

/**
 * unmapcolors(codebreaker_colors,colorschar)=maps color constants
 *                              back to their original color letters
 * colorschar is the only array whose values will be manipulated
*/
void unmapcolors(int codebreaker_colors[], char colorschar[])
{
    for (int i = 0; i < SIZE; i += 1)
    {
        switch(codebreaker_colors[i])
        {
            case GREEN: colorschar[i] = 'G'; break;
            case BLUE: colorschar[i] = 'B'; break;
            case RED: colorschar[i] = 'R'; break;
            case YELLOW: colorschar[i] = 'Y'; break;
            case WHITE: colorschar[i] = 'W'; break;
            case ORANGE: colorschar[i] = 'O'; break;
        }
    }
}


//get guess and convert to color constants
bool guess(int codemaker[])
{
    char codebreaker[SIZE + 1];     //+1 accomodates null terminator
    printf("Please enter your string as a sequence of exactly 4 characters: ");
    scanf("%s", codebreaker);      
    
    int codebreaker_colors[SIZE + 1];   //array that has color constants matching usr input
   
    mapcolors(codebreaker, codebreaker_colors); 

    //compare codemaker and codebreaker
    int correctpositon = 0, wrongposition = 0;

    for (int i = 0; i < SIZE; i += 1)
    {
        if (codebreaker_colors[i] == codemaker[i])
        {
            correctpositon += 1;
        }
        else
        {
            for (int j = 0; j < SIZE; j += 1)
            {
                // exists but in wrong position
                if (codemaker[j] == codebreaker_colors[i] && 
                    codemaker[j] != codebreaker_colors[j])
                {
                    wrongposition += 1;
                    break;
                }
            }
        }
    }
    if (correctpositon == SIZE && wrongposition == 0)
    {
        printf("You got %d correct colors in the right position and %d colors in the wrong position\n", correctpositon, wrongposition);
        return true;
    }
    else
    {
        printf("%d correct positions\n%d wrong positions\n", correctpositon, wrongposition);
        return false;
    }
}

// One entire game 

bool gameplay()
{
    int codemaker[SIZE];          //array to store codemaker's string in int form
    generatestring(codemaker);    //generate codemaker secret values(int) for gameplay
    
    char codemakerchar[SIZE + 1];        //array to store generated secret code in char form
    unmapcolors(codemaker, codemakerchar);
    printf("The secret code is: ");
    printchararray(codemakerchar);
    
    bool won = false;
    for (int i = 0; i < ALLOWEDGUESSES && won == false; i += 1)
    {
        won = guess(codemaker);
    }
    if (won == false)
    {
        printf("Too bad you lost, the code was: ");
        printchararray(codemakerchar);
    }
    else
    {
        printf("Congratulations, you win!");
    }
    return won;
}

int main(void)
{    
    

    /**
     * 
    enum color code[4];

    printf("Welcome to Mastermind!\
    \nEnter a guess as a string of 4 characters, where they must be:\n\
    G - Green\n\
    B - Blue\n\
    R - Red\n\
    Y - Yellow\n\
    W - White\n\
    O - Orage\n\
    Warning: if you enter too many colors for your guess, colors after the\
    \nfourth will be used as part of your next guess.\n");

    */

    char play = 'y';
    bool won = false;
    int timesplayed = 0, timeswon = 0;
    while (play == 'y')
    {
        won = gameplay();
        timesplayed += 1;
        if (won){
            timeswon += 1;
        }
        printf("Would you like to play again? (y/n)");
        scanf(" %c", &play);
    }
    printf("You won %d/%d games\n", timeswon, timesplayed);
    return 0;
}