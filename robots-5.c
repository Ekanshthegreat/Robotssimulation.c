/*  Author: Ekansh Chawla
    Part of an Assignment for a course 
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//read outputfile from inputfile

enum initTypeList{Random = 1, Checkerboard, AllWhite};

enum Direction {north= 1, east, south, west};

enum colour{white = 1, red = 2, green = 3, blue = 4};

struct Robot{
        int x;
        int y;
        int direction;
        int paintColour;
    };

#define NUM_COLOURS 4
#define NUM_DIRECTIONS 4
// ANSI escape codes for terminal color
#define RESET_PRINT "\x1B[0m"
#define WHITE_PRINT "\x1B[37m"
#define RED_PRINT "\x1B[31m"
#define GREEN_PRINT "\x1B[32m"
#define BLUE_PRINT "\x1B[34m"



//void PrintBoardColoured(FILE* stdStream, int **board, int numRows, int numCols);
int InitBoard( int **boardpp, int numRows, int numCols, enum initTypeList mylist, unsigned int seed);

void InitBoardRand(int **board, int numRows, int numCols, unsigned int seed);

void InitBoardChecker(int **board, int numRows, int numCols);

void InitBoardAllWhite(int **board, int numRows, int numCols);

void Initrobot(int numCols, int numRows, unsigned int seed, int numRobots, struct Robot *robots, int **board) {
    srand(seed);                         // srand() is used to seed the random number generator rand()
    for (int j = 0; j<numRobots; j++){
        robots[j].x = rand() % (numCols);   // the % sign sets the rand() function to a specific range, and these lines
        robots[j].y = rand() % (numRows);      // essentially choose a coordinate (a row and a column) for each robot by random
        robots[j].direction = (rand() % NUM_DIRECTIONS + 1);
        robots[j].paintColour = (rand() % NUM_COLOURS + 1);

        board[robots[j].y][robots[j].x] = robots[j].paintColour;
    }
}


void printBoardToFileAndScreen(int **board, int numRows, int numCols, int turn, int interval, int nturns, FILE *outstream);

void moveTurns(int numRows, int numCols, int numRobots, int nturns, struct Robot *robots, int **board, int interval, FILE *outstream);

int parametersread(FILE *inputstreamp, int *rows, int *collumns, int *numRobots, int *initcolor, int *initseed, int *nturns, int *intervalturns, FILE *outputstreamp, char errors[10][256], char outputfile[256]) {
    int errorcount = 0;
    int fail = 0;
    int N = 0;
    
    //The number of rows in the board you wish to use (20 to 300 inclusive)
    N = fscanf(inputstreamp,"%d", rows);
    if (feof(inputstreamp)){
        sprintf(errors[errorcount], "ERROR: The number of rows was not in the input file (reached eof)");
        errorcount++;
        fail = 1;
    }
    
    if (N <= 0){
        sprintf(errors[errorcount], "ERROR: The number of rows could not be read due to corrupt data in the file");
        errorcount++;
        fail = 1;
    }
    if (*rows < 20 || *rows > 300){
        sprintf(errors[errorcount], "ERROR: The number of rows was outside the specified range (20 to 300 inclusive)");
        errorcount++;
        fail = 1;
    }
    N = fscanf(inputstreamp, "%d\n", collumns);
    if (feof(inputstreamp)){
        sprintf(errors[errorcount], "ERROR: The number of columns was not in the input file (reached eof)");
        errorcount++;
        fail = 1;
    } 
    if (N <= 0){
        sprintf(errors[errorcount], "ERROR: The number of columns could not be read due to corrupt data in the file");
        errorcount++;
        fail = 1;
    }
    if (*collumns < 20 || *collumns > 300){
       sprintf(errors[errorcount], "ERROR: The number of columns was outside the specified range (20 to 300 inclusive)");
       errorcount++;
        fail = 1;
    }
    N = fscanf(inputstreamp, "%d\n", numRobots);
    if (feof(inputstreamp)){
        sprintf(errors[errorcount], "ERROR: The number of robots was not in the input file (reached eof)");
        errorcount++;
        fail = 1;
    }
    if (N <= 0){
        sprintf(errors[errorcount], "ERROR: The number of robots could not be read due to corrupt data in the file");
        errorcount++;
        fail = 1;
    }
    if (*numRobots < 1 || *numRobots > 10){
       sprintf(errors[errorcount], "ERROR: The number of robots was outside the specified range (1 to 10 inclusive)");
       errorcount++;
        fail = 1;
    }
    N = fscanf(inputstreamp, "%d\n", initcolor);
    if (feof(inputstreamp)){
        sprintf(errors[errorcount], "ERROR: The initTypeValue was not in the input file (reached eof) ");
        errorcount++;
        fail = 1;
    }
    if (N <= 0){
        sprintf(errors[errorcount], "ERROR: The initTypeValue could not be read due to corrupt data in the file");
        errorcount++;
        fail = 1;
    }
    if (*initcolor < 1 || *initcolor > 3){
       sprintf(errors[errorcount], "ERROR: The initTypeValue was outside the specified range (1 to 3 inclusive)");
        errorcount++;
        fail = 1;
    }
    N = fscanf(inputstreamp, "%d\n", initseed);
    if (feof(inputstreamp)){
       sprintf(errors[errorcount], "ERROR: The initSeed was not in the input file (reached eof)");
       errorcount++;
      fail = 1;
    }
    if (N <= 0){
        sprintf(errors[errorcount], "ERROR: The initSeed could not be read due to corrupt data in the file ");
        errorcount++;
       fail = 1;
    }
    if (*initseed < 10 || *initseed > 32767){
        sprintf(errors[errorcount], "ERROR: The initSeed was outside the specified range (10 to 32767 inclusive)");
        errorcount++;
         fail = 1;
    }
    N = fscanf(inputstreamp, "%d", nturns);
    if (feof(inputstreamp)){
        sprintf(errors[errorcount], "ERROR: The turns was not in the input file (reached eof)");
        errorcount++;
        fail = 1;
    }
    if (N <= 0){
        sprintf(errors[errorcount], "ERROR: The turns could not be read due to corrupt data in the file");
        errorcount++;
        fail = 1;
    }
    if (*nturns < 10 || *nturns > 5000){
        sprintf(errors[errorcount], "ERROR: The turns was outside the specified range (10 to 5000 inclusive)");
        errorcount++;
        fail = 1;
    }
    N = fscanf(inputstreamp, "%d",  intervalturns);
    if (feof(inputstreamp)){
        sprintf(errors[errorcount], "ERROR: The interval was not in the input file (reached eof)");
        errorcount++;
        fail = 1;
    }
    if (N <= 0){
        sprintf(errors[errorcount], "ERROR: The interval could not be read due to corrupt data in the file");
        errorcount++;
        fail = 1;
    }
    if (*nturns < 10 || *intervalturns > *nturns){
        sprintf(errors[errorcount], "ERROR: The interval was outside the specified range (0 to %d inclusive)", *nturns);
        errorcount++;
        fail = 1;
    }
    fscanf(inputstreamp, "%s",  outputfile);
//printf("%d %d %d %d %d %d %d", *rows, *collumns, *numRobots, *initcolor, *initseed, *nturns, *intervalturns);
return fail;

}


int dynamicallocate(unsigned int seed, int rows, int collumns, int ***boardpp, int numRobots, struct Robot **robots, FILE* outputstreamp){
    *boardpp = (int **)malloc(rows * sizeof(int *));
    if (*boardpp == NULL){
    printf("ERROR: array of pointers for 2-D array could not be allocated");
    fprintf(outputstreamp, "ERROR: array of pointers for 2-D array could not be allocated\n");
    free(*boardpp);   
    *boardpp = NULL;     
    return 1;
    }
    (*boardpp)[0] = (int *)malloc(rows * collumns * sizeof(int));
    for (int i = 1; i < rows; i++) {
        (*boardpp)[i] = (*boardpp)[0] + collumns * i;
}
    if ((*boardpp[0]) == NULL){
        printf("ERROR: Array storage could not be allocated");
        fprintf(outputstreamp, "ERROR: Array storage could not be allocated");
        free(*boardpp[0]);
        *boardpp[0] = NULL;
        free(*boardpp);
        *boardpp = NULL;
        return 1;
    }

    *robots = (struct Robot *)malloc(numRobots * sizeof(struct Robot));
    Initrobot(collumns, rows, seed, numRobots, *robots, *boardpp);
    return 0;
}

int main() {
    char filename[100];
    FILE* inputstreamp = NULL;
    int counter = 0;

    do {
        if (counter >= 1) {
            printf("ERROR: Input file not opened correctly.\n");
        }

        printf("\nEnter the name of the input file: ");
        scanf("%s", filename);
        inputstreamp = fopen(filename, "r");
        counter++;
        

        if (counter == 5) {
            printf("ERROR: Failed to open the input file 5 times. Terminating the program. \n");
            return 1;
        }
    } while (inputstreamp == NULL && counter < 5);

    int rows = 0, collumns = 0, numRobots = 0, initcolor = 0, initseed = 0, nturns = 0, intervalturns = 0;
    
    // Read the output file name from the last line
    FILE* outstreamp;
    
    char outputfile[256];
    char errors[10][256] = {0};
    int fail = 0;

    
    fail = parametersread(inputstreamp, &rows, &collumns, &numRobots, &initcolor, &initseed, &nturns, &intervalturns, outstreamp, errors, outputfile);
    //printf("%d %d %d %d %d %d %d %s", rows,collumns,numRobots, initcolor, initseed,nturns, intervalturns,outputfile);
    outstreamp = fopen(outputfile,"w");
    for (int i = 0; i < 10; i++) {
        if (errors[i][0] != '\0') {
            printf("%s\n", errors[i]);
        }
    }
    //UNCOMMENT BELOW LINE IF YOU WANT THE ERRORS TO BE PRINTED OUT IN OUTFILE - AS WAS REQUIRED IN ASSIGNMENT1 VERSION 1
    // for (int i = 0; i < 10; i++) {
    //     if (errors[i][0] != '\0') {
    //         fprintf(outstreamp, "%s\n", errors[i]);
    //     }
    // }

    // Check for errors before proceeding
    if (fail){
        return 0;
    }

    struct Robot* robots = NULL;
    int** boardpp = NULL;
    if (dynamicallocate(initseed, rows, collumns, &boardpp, numRobots, &robots, outstreamp) == 1) {
        fclose(outstreamp);
        fclose(inputstreamp);
        free(boardpp[0]);
        boardpp[0] = NULL;
        free(boardpp);
        boardpp = NULL;

        return 1;
    }

    enum initTypeList mylist;
    InitBoard(boardpp, rows, collumns, (enum initTypeList)initcolor, initseed);
    moveTurns(rows, collumns, numRobots, nturns, robots, boardpp, intervalturns, outstreamp);

    fclose(outstreamp);
    fclose(inputstreamp);
    free(boardpp[0]);
    boardpp[0] = NULL;
    free(boardpp);
    boardpp = NULL;

    return 0;
}
    

int InitBoard( int **boardpp, int numRows, int numCols, enum initTypeList mylist, unsigned int seed){
    switch (mylist){
        case Random:
            InitBoardRand(boardpp, numRows, numCols, seed);
            break;
        case Checkerboard:
            InitBoardChecker(boardpp, numRows, numCols);
            break;
        case AllWhite:
            InitBoardAllWhite(boardpp, numRows, numCols); 
            break;
    }
    return 0;
 }

 void InitBoardRand(int **board, int numRows, int numCols, unsigned int seed)
{
	/* Please note that NUM_COLOURS is a global constant or a MACRO*/
	srand(seed);
	for (int K = 0; K < numRows; K++)
	{
		for (int J = 0; J < numCols; J++)
		{
			board[K][J] = rand() % NUM_COLOURS + 1;
		}
	}
}

 void InitBoardChecker(int **board, int numRows, int numCols){
    for (int k = 0; k < numRows; k++){
        for (int i = 0; i < numCols; i++){
            if ((i+k)%2 == 0){
                board[k][i] = white;
            }
            else {
                board[k][i] = red;
            }
        }
        
    }
 }

void InitBoardAllWhite(int **board, int numRows, int numCols){
    for (int k = 0; k < numRows; k++){
        for (int j = 0; j < numCols; j++){
            board[k][j] = white;
        }
    }
}

void moveTurns(int numRows, int numCols, int numRobots, int nturns, struct Robot *robots, int **board, int interval, FILE *outstream) {
    //printf("%d", robots[0].direction);
    //printf("%d\n", robots[1].direction);
    //printf("%d\n", robots[2].direction);

    
    
    for (int turn = 0; turn < nturns; turn++) {
        for (int j = 0; j < numRobots; j++) {
            // Store the current position
            int currentX = robots[j].x;
            int currentY = robots[j].y;

            // Update the position based on the direction
            switch(robots[j].direction){
                case north:
                    robots[j].y -= 1;
                    if (robots[j].y == -1){
                        robots[j].y = (numRows - 1);
                    }
                    break;
                case east:
                    robots[j].x += 1;
                    if (robots[j].x == numCols){
                        robots[j].x = 0;
                    }
                    break;
                case south:
                    robots[j].y += 1;
                    if (robots[j].y == numRows){
                        robots[j].y = 0;
                    }
                    break;
                case west:
                    robots[j].x -= 1;
                    if (robots[j].x == -1){
                        robots[j].x = (numCols - 1);
                    }
                    break;
            }

            switch(board[robots[j].y][robots[j].x]){
                case white:  // white
                    switch(robots[j].direction){                    //current direction
                        case north:
                            robots[j].direction = east;
                            break;
                        case east:
                            robots[j].direction = south;
                            break;
                        case south:
                            robots[j].direction = west;
                            break;
                        case west:
                            robots[j].direction = north;
                            break;
                    }
                    break;
                case red:     // red
                    switch(robots[j].direction){
                        case north:
                            robots[j].direction = south;
                            break;
                        case east:
                            robots[j].direction = west;
                            break;
                        case south:
                            robots[j].direction = north;
                            break;
                        case west:
                            robots[j].direction = east;
                            break;
                    }
                    break;
                case green:      // green
                    switch(robots[j].direction){
                        case north:
                            robots[j].direction = west;
                            break;
                        case east:
                            robots[j].direction = north;
                            break;
                        case south:
                            robots[j].direction = east;
                            break;
                        case west:
                            robots[j].direction = south;
                            break;
                    }
                    break;
                case blue:     // blue
                    switch(robots[j].direction){
                        case north:
                            robots[j].direction = north;      // directions stay same if blue
                            break;
                        case east:
                            robots[j].direction = east;
                            break;
                        case south:
                            robots[j].direction = south;
                            break;
                        case west:
                            robots[j].direction = west;
                            break;
                    }
                    break;
            }

            // Update the color on the board
            //board[newY][newX] = robots[j].paintColour;
            board[currentY][currentX] = robots[j].paintColour;
            //printf("%d", robots[j].direction);
        }

        printBoardToFileAndScreen(board, numRows, numCols, turn, interval, nturns,  outstream);
    }
}

/*for (int K = 0; K < numRows; K++)
	{
		for (int J = 0; J < numCols; J++)
		{
			fprintf(myStream, "%d", board[K][J]);
		}
		fprintf(myStream, "\n");
	}
	fprintf(myStream, "\n\n");
}*/


void printBoardToFileAndScreen(int **board, int numRows, int numCols, int turn, int interval, int nturns, FILE *outstream) {
    if ((turn % interval) == 0 || turn == 0 || turn == (turn-1)) {
            for (int i = 0; i < numRows; i++) {
                for (int k = 0; k < numCols; k++) {
                    fprintf(outstream, "%d", board[i][k]);
                    printf("%d", board[i][k]);
                }
                fprintf(outstream, "\n");
                printf("\n");
            }
            fprintf(outstream, "\n \n");
            printf("\n \n");
        }
        turn ++;
    

    }

