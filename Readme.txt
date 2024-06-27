# Sudoku Game README

## Introduction
This README provides instructions for building and running the Sudoku game application.

## Prerequisites
Before running the application, make sure you have the following dependencies installed:
- C compiler (e.g., gcc)
- cJSON library (https://github.com/DaveGamble/cJSON) (this should already come with the code)

## Building and Running the Game

1. download the source files to your local machine
2. Open a terminal or command prompt and navigate to the directory containing the source code files.
3. Use the provided Makefile to compile the source code into an executable. Run the following command:

```
    make Game
```
This command will compile the source files (`Main.c`, `utilities.c`, `PrintBoard.c`, `GenerateValues.c`, `cJSON.c`) and create an executable named `Main`.

## Execution Instructions
Once the application is built, follow the makefile should automatically open the game, if not, follow these instructions below:

1. Find executable file (main.exe) in your directory and execute it
2. Follow the on-screen instructions to interact with the Sudoku game.

## Usage

- When the game starts, you will be given an option to enter your Game ID.
- You can load a saved game by entering the Game ID.
- If no saved game exists with the provided ID, you can start a new game.
- Follow the on-screen instructions to play the Sudoku game.
- Input '0' by itself to save and exit the game.

## Additional Notes
- The game data is stored in a JSON file named `data.json`. Make sure this file is present in the same directory as the executable.
- The game supports loading and saving game progress.
