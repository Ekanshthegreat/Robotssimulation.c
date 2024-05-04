# Robotssimulation.c

#Reading Input Parameters: We prompt the user to enter the name of the input file containing the game parameters. We make several attempts to open the file, displaying appropriate error messages if unsuccessful.
Reading Parameters from Input File: We read the required quantities from the input file in the specified order: number of rows, number of columns, number of robots, initialization type, seed, number of turns, printing interval, and output file name. We ensure that each value is valid, and if not, we print an error message to stderr.
Dynamic Memory Allocation: We dynamically allocate memory for a 2D integer array to represent the game board (boardpp) and a 1D array of structures to hold robot information.
Board Initialization: We initialize the board based on the selected initialization type by calling the appropriate initialization function (InitBoardRand, InitBoardChecker, or InitBoardAllWhite).
Robot Placement: We randomly place each robot on the board, assign its facing direction, and assign the color of paint it carries. We ensure that the random numbers generated are consistent by seeding the random number generator (srand(seed)).
Game Execution: We run the game for the specified number of turns. In each turn, every robot moves forward, rotates, and changes the color of the square it moves onto. We handle special cases where a robot moves off the board by making it reappear on the opposite side.
Output Printing: We print the board to both the output file and the screen every interval turns, starting from turn 0. We use a provided function to display the board in color on the terminal for debugging purposes.
Error Handling: Throughout the program, we perform error checking for invalid input values, failed memory allocations, and unsuccessful file operations. We print appropriate error messages to stderr and clean up resources before terminating the program.
