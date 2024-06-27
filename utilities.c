#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "cJSON.h"

#include "data.h"

/*
    Check if input is sudoku valid
    @param sud[9][9]: the array of the board
    @param row: the row to check against
    @param col: the column to check against
    @param num: the value to validate
    @return bool: if value is sudoku valid 
*/
bool isValid(int sud[9][9], int row, int col, int num) 
{
    // Check if 'num' is present in the current row and column
    for (int i = 0; i < 9; i++) 
    {
        if (sud[row][i] == num && i != col) // Exclude the current cell
        {
            return false;
        }
        if (sud[i][col] == num && i != row) // Exclude the current cell
        {
            return false;
        }
    }

    // Check if 'num' is not present in the 3x3 subgrid (box)
    int squareRow = row - row % 3;
    int squareCol = col - col % 3;

    for (int i = 0; i < 3; i++) 
    {
        for (int j = 0; j < 3; j++) 
        {
            if (sud[squareRow + i][squareCol + j] == num && (squareRow + i != row || squareCol + j != col)) // Exclude the current cell
            {
                return false;
            }
        }
    }
    return true;
}

/*
    Add/Update data to the JSON
    @param json: the JSON object
    @param boardStateStr: all values in the sudoku board represented as a string 
*/
void addDataToJSON(cJSON *json, const char* boardStateStr) {
    // Check if player ID is not null
    if (player.id != 0) 
    { 
        char idString[10];
        snprintf(idString, sizeof(idString), "%d", player.id);

        // Find the existing data with the player ID and update it with new
        cJSON *existingId = cJSON_GetObjectItemCaseSensitive(json, idString);
        if (existingId != NULL) 
        {
            cJSON_ReplaceItemInObjectCaseSensitive(existingId, "Player", cJSON_CreateString(player.playerName));
            cJSON_ReplaceItemInObjectCaseSensitive(existingId, "Board State", cJSON_CreateString(boardStateStr));
            cJSON_ReplaceItemInObjectCaseSensitive(existingId, "Difficulty", cJSON_CreateNumber(player.Difficulty));
            cJSON_ReplaceItemInObjectCaseSensitive(existingId, "Progress", cJSON_CreateString(player.progress));
            return;
        }
    }

    // Create a new JSON object for the player
    cJSON *playerObj = cJSON_CreateObject();
    
    // Add player information to the player object
    cJSON_AddStringToObject(playerObj, "Player", player.playerName); 
    cJSON_AddStringToObject(playerObj, "Board State", boardStateStr); 
    cJSON_AddNumberToObject(playerObj, "Difficulty", player.Difficulty); 
    cJSON_AddStringToObject(playerObj, "Progress", player.progress); 

    // If player ID is null or not found, add new data to the JSON
    int highestID = findHighestID(json);
    char idString[10];
    snprintf(idString, sizeof(idString), "%d", highestID + 1);
    
    // Add player object to the main JSON object with player's ID as key
    cJSON_AddItemToObject(json, idString, playerObj); 

    // Tell player their ID
    printf("Your game ID is %d\n", highestID + 1);
}

/*
    Create new ID for JSON values
    @param json: the JSON object
    @return id: new id for json
*/
int findHighestID(cJSON *json) {

    if (json == NULL) {
        printf("Error parsing JSON.\n");
        return -1; // Return -1 to indicate failure
    }
    
    int highestID = cJSON_GetArraySize(json); // Get the number of objects
    
    return highestID;
}

/*
    Update new values to JSON
*/
void saveGame() {
    // Read existing JSON data from the file
    FILE *fp_read = fopen("data.json", "r");
    cJSON *json = NULL;
    if (fp_read != NULL) {
        // Parse file to JSON
        fseek(fp_read, 0, SEEK_END);
        long file_size = ftell(fp_read);
        fseek(fp_read, 0, SEEK_SET);
        char *file_content = (char *)malloc(file_size + 1);
        fread(file_content, 1, file_size, fp_read);
        fclose(fp_read);
        
        file_content[file_size] = '\0';
        json = cJSON_Parse(file_content);
        free(file_content);
    }

    // if json is null then create new json object
    if (json == NULL) 
        json = cJSON_CreateObject();

    char boardStateStr[82]; // 82 is always the board size
    boardStateStr[0] = '\0'; // Initialize the string with a null terminator
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            char temp[2]; // Buffer to hold string representation of each integer
            snprintf(temp, sizeof(temp), "%d", player.boardState[i][j]);
            // concatenate temp onto end of boardStateStr
            strcat(boardStateStr, temp);
        }
    }

    // Add player data to the JSON
    addDataToJSON(json, boardStateStr);

    // Convert the cJSON object to a JSON string
    char *json_str = cJSON_Print(json);

    // Write the updated JSON string to the file
    FILE *fp_write = fopen("data.json", "w");
    if (fp_write == NULL) {
        printf("Error: Unable to open the file for writing.\n");
        cJSON_Delete(json);
        return;
    }
    
    // Write merged JSON data to the file
    fputs(json_str, fp_write);
    fclose(fp_write);

    // Free the JSON string and cJSON object
    cJSON_free(json_str);
    cJSON_Delete(json);

    // Return to the Menu
    return;
}

/*
    Create new sudoku board
*/
void newGame()
{
    // Get playerName
    printf("Enter Player Name: \n");
    scanf("%50s", player.playerName);

    // Set id to 0 to create a new record
    player.id = 0;

    // Get game difficulty
    bool check = true;
    while (check)
    {
        printf("Select Your Difficulty:\nE: Easy\nM: Medium\nH: Hard\nC: Custom\n");
        char input;
        scanf(" %c", &input);

            switch (input)
            {
            case 'E':
                printf("Selected Easy!");
                player.Difficulty = 20;
                check = false;
                break;

            case 'M':
                printf("Selected Medium!");
                player.Difficulty = 40;
                check = false;
                break;

            case 'H':
                printf("Selected Hard!");
                player.Difficulty = 60;
                check = false;
                break;

            case 'C':
                printf("Selected Custom!\n enter how many squares to be removed from the board: ");
                scanf("%d", &player.Difficulty);
                check = false;
                break;

            default:
            printf("Error! Input is not recognised, only a single character should be inputed!\n");
        }

    }
    printf("Test 1");
    // Initialize all elements of boardState to 0
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            player.boardState[i][j] = 0;
        }
    }
    printf("Test 2");
    // set player progress based on difficulty
    sprintf(player.progress, "0/%d", player.Difficulty);

    /*
     * Generate the Sudoku board
     * Give user instructions
     * call play_game()
    */
   printf("Test 3");
    generateSud();
    printf("Test 4");
    printf("Inputting '0' by itself will save and exit the game\n");
    printf("User must input values onto the sudoku board using the format [row][column][value]. An example would be 1b6.\n");
    play_game();
}

/*
    Load previous game data and create game
*/
void loadGame() {

    // get id to search for 
    printf("Enter your Game ID: ");
    int id;
    scanf("%d", &id);

    printf("Loading Game %d\n", id);

    FILE *fp_read = fopen("data.json", "r");
    cJSON *json = NULL;
    if (fp_read != NULL) {
        // Parse file to JSON
        fseek(fp_read, 0, SEEK_END);
        long file_size = ftell(fp_read);
        fseek(fp_read, 0, SEEK_SET);
        char *file_content = (char *)malloc(file_size + 1);
        fread(file_content, 1, file_size, fp_read);
        fclose(fp_read);
        
        file_content[file_size] = '\0';
        json = cJSON_Parse(file_content);
        free(file_content);
    }

    if (json == NULL) {
        printf("ERROR: parsing json/no values in json\n");
        return;
    }

    // Find the game with the given ID
    char idString[3]; 
    snprintf(idString, sizeof(idString), "%d", id);
    cJSON *gameData = cJSON_GetObjectItemCaseSensitive(json, idString);
    if (gameData == NULL) {
        // ID not found, return to menu
        printf("Game with ID %d not found.\n", id);
        cJSON_Delete(json);
        return;
    }

    // Retrieve data
    char *playerName = cJSON_GetObjectItemCaseSensitive(gameData, "Player")->valuestring;
    char *boardState = cJSON_GetObjectItemCaseSensitive(gameData, "Board State")->valuestring;
    int difficulty = cJSON_GetObjectItemCaseSensitive(gameData, "Difficulty")->valueint;
    char *progress = cJSON_GetObjectItemCaseSensitive(gameData, "Progress")->valuestring;

    // Update player data
    player.id = id;
    strcpy(player.playerName, playerName);
    player.Difficulty = difficulty;
    strcpy(player.progress, progress);


int index = 0;
for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
        char temp[2]; // Buffer to hold string representation of each integer
        temp[0] = boardState[index]; // Get the character from the boardState string
        temp[1] = '\0'; // Null-terminate the string
        player.boardState[i][j] = atoi(temp); // Convert the character to integer and set to relevant cordinate
        index++; // uptick index
    }
}

    // Give user some context
    printf("Loaded Game ID: %d\n", id);
    printf("Player Name: %s\n", player.playerName);
    printf("Difficulty: %d\n", difficulty);
    printf("Progress: %s\n", progress);
    printf("Inputting '0' by itself will save and exit the game\n");
    printf("User must input values onto the sudoku board using the format [row][column][value]. An example would be 1b6.\n");

    // Set up board and start the game
    prog_bar();
    sud_board();
    play_game();
}