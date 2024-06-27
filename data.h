#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

// Struct to hold neccesary data
struct jsonData {   // Structure declaration
  int id;
  char playerName[50];     
  int boardState[9][9];
  int Difficulty;
  char progress[5];
};

struct jsonData player;

// Main
void play_game();
void menu();

// Print Board
void prog_bar();
void sud_board();

// Generate Sudoku Board
void generateSud();
bool input_numbers();

// Utilities
void saveGame();
void newGame();
bool isValid(int sud[9][9], int row, int col, int num);
void loadGame();
