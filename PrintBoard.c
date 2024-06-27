#include <stdio.h>
#include <stdlib.h>

#include "data.h"

/*
    Display progress bar for user and uptick whenever a right answer is inputted
*/
void prog_bar()
{
    // Get size of progress bar
    int progress = player.Difficulty;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            
            if (player.boardState[i][j] == 0)
            {
                progress--;
            }
        }
    }
    // Create progress bar, show progress made vs progress left
    printf("[");
    for (int i = 1; i <= player.Difficulty; i++)
    {
        if (i <= progress)
        {
            printf("#");
        }
        else
        {
            printf("-");
        }
    }
    printf("]%d/%d\n\n", progress, player.Difficulty);
    sprintf(player.progress, "%d/%d", progress, player.Difficulty);

    // if progress bar is full then the game is complete
    if (player.Difficulty == progress)
    {
        printf("Game is completed!\n");
        return;
    }
}

/*
    Display Sudoku board to screen
*/
void sud_board() {
    printf("    a b c   d e f   g h i\n");
    for (int i = 0; i < 9; i++) {
        printf("%d ", (9 - i));
        for (int j = 0; j < 9; j++) {
            // Print all vertical lines
            if (j % 3 == 0 || j == 0) {
                printf("| ");
            }
            // Print the cordinate
            printf("%d ", player.boardState[i][j]);
        }
        // Line Break
        printf("| %d\n", (9 - i));
        
        // Print horizontal lines
        if (i % 3 == 2 && i != 8) {
            printf("  |-------+-------+-------|\n");
        }
    }
    printf("    a b c   d e f   g h i\n");
}