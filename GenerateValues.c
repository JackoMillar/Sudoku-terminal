#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "data.h"

/*
    check if player input is valid in comparison to the board state and input onto the board
*/
bool input_numbers()
{
    bool check = false;
    int i, j;


    for (i = 0; i < 9; i++) 
    {
        for (j = 0; j < 9; j++) 
        {
            if (player.boardState[i][j] == 0)
            {
                check = true;
                break;
            }
        }
        if (check)
        {
            break;
        }
    }

    // If no empty element is found, the Sudoku is solved!
    if (!check)
    {
        return true;
    }

    // Try placing a number in the empty
    for (int num = 1; num <= 9; num++)
    {
        if (isValid(player.boardState, i, j, num)) 
        {
            player.boardState[i][j] = num;

            // Recursively try to solve the sodoku
            if (input_numbers()) 
            {
                return true; // return true if a solution is found
            }

            // If placing num doesnt work then set back to 0
            player.boardState[i][j] = 0;
        }
        }
        return false;
}

/*
    Generate board with random values 
*/
void generateSud()
{

    // Generate a solved Sudoku board
    input_numbers();

    // Revert numbers back to zero
    int removeCount = player.Difficulty;  // Adjust the difficulty level by changing the number of removed cells, will be done later
    while (removeCount > 0) 
    {
        int row = rand() % 9; // find a random row
        int col = rand() % 9; // find a random column

        // Check if the cell is already empty
        if (player.boardState[row][col] != 0) 
        {
            player.boardState[row][col] = 0;
            removeCount--;
        }
    }

    // Display progress bar and sudoku board
    prog_bar();
    sud_board();
}