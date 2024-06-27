#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "cJSON.h" 

#include "data.h"

/* 
Recursive function for inputing values onto the sudoku board
Input: "0" results in the saveGame() being called and breaking the loop
Input: "[sudoku input]" will call:
    * isValid() check if input is valid
        * if true: call prog_bar(), sud_board() and play_game()
        * if false: call play_game()
*/
void play_game()
{
    char c[3];

    // Loop till valid user input
    while (true)
    {    
        // User input for sudoku
        printf("Enter Sudoku input: \n");
        scanf("%3s", c);
        c[3] = '\0';

        // Save Game if '0' is entered
        if (c[0] == '0')
        {
            saveGame();
            return; 
        }

        // Check if valid sudoku input
        if (!(c[1] >= 'a' && c[1] <= 'i') || 
            !(c[0] >= '1' && c[0] <= '9') || 
            !(c[2] >= '1' && c[2] <= '9')) 
            printf("Invalid input. Please enter coordinates in the format 'a1' to 'i9' followed by value.\n");
        else
            break;
    }

    // Convert the individual char's to int
    int rowCord = c[0] - '0'; // first character represents row
    int colCord = c[1] - 'a'; // second character represents column
    int value = c[2] - '0'; // third character represents input value

    //Check if valid then input onto board
    bool valid = isValid(player.boardState, -rowCord + 9, colCord, value);
    printf("%s\n", valid ? "true" : "false");
    if (valid == true)
    {
        // set coordinate to value
        player.boardState[-rowCord + 9][colCord] = value;
        prog_bar();
        sud_board();
        play_game();
    }else if (valid == false)
    {
        printf("This input is not sudoku valid!\n");
        play_game();
    }
    
}

/*
Function for accessing different sections of the game from menu
Input: '1' to create a new game - newGame()
Input: '2' to load a previous game - loadGame()
Input '3' to exit the program
*/
void menu ()
{
    char input;
    while (true)
    {
        printf("MENU!\n1: Play New Game\n2: Load Game\n3: Exit\n");
        scanf(" %c", &input);
        switch (input)
        {
            case '1':
                newGame();
                break;

            case '2':
                loadGame();
                break;

            case '3':
                printf("Exiting...\n");
                return;

            default:
            printf("Error! Input is not correct\n");
        }
    }
}

/*
Call menu() 
*/
int main ( int argc , char **argv )
{
   // clock_t t;
   // printf("start: %d \n", (int) (t=clock()));
    menu();
   // printf("stop: %d \n", (int) (t=clock()-t));
   // printf("Elapsed: %f seconds\n", (double) t / CLOCKS_PER_SEC);
}