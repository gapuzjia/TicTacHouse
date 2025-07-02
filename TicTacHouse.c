#include <stdio.h>
#include <stdlib.h>

//node representing each cell 
typedef struct Cell{

	char val;
	struct Cell* up;
	struct Cell* down;
	struct Cell* left;
	struct Cell* right;

}Cell;

//create a board with defined dimensions
Cell* createBoard(int rows, int cols)
{
	Cell* topLeft = NULL;
    	Cell* prevRowStart = NULL;

    	for (int i = 0; i < rows; i++) 
	{
        	Cell* rowStart = NULL;
        	Cell* prev = NULL;
        	Cell* upper = prevRowStart;

        	for (int j = 0; j < cols; j++) 
		{
            		Cell* newCell = malloc(sizeof(Cell));
            		newCell->val = '*';
            		newCell->up = newCell->down = newCell->left = newCell->right = NULL;

            		if (!rowStart)
                		rowStart = newCell;

            		if (prev) 
			{
                		prev->right = newCell;
                		newCell->left = prev;
            		}

            		if (upper) 
			{
                		newCell->up = upper;
                		upper->down = newCell;
                		upper = upper->right;
            		}

            		prev = newCell;
        	}

        	if (!topLeft)
            		topLeft = rowStart;

        	prevRowStart = rowStart;
    	}

    	return topLeft;
}

//print board
void printBoard(Cell* gameBoard, int dimensions) 
{
	//init top left cell
 	Cell* rowPtr = gameBoard;


    	for (int i = 0; i < dimensions; i++) 
	{
        	//adjust to go backwards to mimic cartesian coordinates
        	printf("%2d ", dimensions - i);

        	Cell* cellPtr = rowPtr;

        	for (int j = 1; j <= dimensions; j++) 
		{
            		printf(" %c ", cellPtr->val);
            		cellPtr = cellPtr->right;
        	}

        	printf("\n");
        	rowPtr = rowPtr->down;
    	}

    	//print labels for x-axis
    	printf("   ");

    	for (int i = 1; i <= dimensions; i++)
        	printf("%2d ", i);
    
    	printf("\n");
}

int checkIllegalMove(int x, int y, int dimensions, char player, Cell* gameBoard)
{

    	//declare and init top left cell
    	Cell* cellPtr = gameBoard;
	
	//adjust y coordinate to mimic cartesian coordiantes
    	y = dimensions - y;

	//traverse downward
    	for (int i = 0; i < y; i++)
        	cellPtr = cellPtr->down;
    	
	//traverse to the right
	for (int i = 1; i < x; i++)
        	cellPtr = cellPtr->right;

    	//check if position is occupied
    	if (cellPtr->val != '*') 
	{
        	printf("Invalid position, please choose another cell!\n");
        	return 1;
    	}

    //modify position if legal
    cellPtr->val = player;
    return 0;
}

// int checkWalls(int xAnchor, int yAnchor, int dimensions, char player, Row* gameBoard)
// {
//         //init/declare rowPtr and cellPtr
//         Row* rowPtr = gameBoard;
//         Cell* cellPtr;
// 
//         //-----check top of walls
//         //move rowPtr to 2 above yAnchor
//         for(int i = 0; i < dimensions - yAnchor - 2; i++)
//                 rowPtr = rowPtr->down;
// 
//         //init cellPtr
//         cellPtr = rowPtr->head;
// 
//         //move cellPtr to xAnchor
//         for(int i = 0; i < xAnchor; i++)
//                 cellPtr = cellPtr->right;
// 
//         //top of walls are not in place, house is not made
//         if(cellPtr->val != player || cellPtr->right->right->val != player)
//                 return 0;
// 
//         //------now check middle brick
//         //move rowPtr down
//         rowPtr = rowPtr->down;
// 
//         //re-initialize cellPtr
//         cellPtr = rowPtr->head;
// 
//         //move cellPtr to xAnchor
//         for(int i = 0; i < xAnchor; i++)
//                 cellPtr = cellPtr->right;
// 
//         //top of walls are not in place, house is not made
//         if(cellPtr->val != player || cellPtr->right->right->val != player)
//                 return 0;
// 
// 
//         //code falls through, means walls are in place and correct
//         return 1;
// 
// }
// 
// int checkWinner(char player, int dimensions, Row* gameBoard)
// {
// 	//declare tracking variables
// 	int yAnchor = dimensions - 5;
// 	int xAnchor;
// 	
// 	//init current rowPtr to the 5th row, base can only start at that row
// 	Row* rowPtr = gameBoard;
// 	for(int i = 0; i < 5; i++)
// 		rowPtr = rowPtr->down;
// 
// 	while(rowPtr->down)
// 	{
// 		//init current cellPtr to one in, base can only start there
// 		Cell* cellPtr = rowPtr->head;
// 		cellPtr = cellPtr->right;
// 
// 		//traverse all rows for 3 of the symbol in a row
// 		//dimensions - 2 prevents looking two to the right being null 
// 		for(int i = 1; i < dimensions - 2; i++)
// 		{
// 			xAnchor = i;
// 			
// 			//executes if a 3 in a row was found
// 			if(cellPtr->val == player && cellPtr->val == cellPtr->right->val && cellPtr->val == cellPtr->right->right->val)
// 			{
// 				printf("found 3 in a row\n");
// 				if(checkWalls(xAnchor, yAnchor, dimensions, player, gameBoard))
// 					printf("base and walls exist!");
// 
// 			}
// 			
// 			//move to next pointer
// 			cellPtr = cellPtr->right;
// 		}
// 		
// 		//move rowPtr and update anchor tracker
// 		rowPtr = rowPtr->down;
// 		yAnchor--;
// 	}
// 
// 	return 0;
// }
// 
// 
int main() 
{
	
	//delcare all variables
	const int NUM_PLAYERS = 4;
	char playerSymbols[4] = {'X','O','W','B'};

	//TO CALCULATE: NUMBER OF MAX MOVES THAT WILL RESULT IN A DRAW GAME--- ADD THIS CONDT LATER
	//const int MAX_TURNS = 

	int dimensions;
	int xCoord, yCoord;
	char player;
	int isPlaying = 1;

	//tracks number of turns and which player is next
	int turns = 1;
		
	//prompt for dimensions of the board
	printf("Enter board size (ie enter 10 for a 10x10 board): ");
	scanf("%d", &dimensions);
	
	//create instance of the gameBoard
	Cell* gameBoard = createBoard(dimensions, dimensions);

	printf("Generating board with dimensions %dx%d:\n", dimensions, dimensions);


	//start gameplay
	while(isPlaying)
	{

		//determine who's turn it is
		player = playerSymbols[(turns - 1) % NUM_PLAYERS];
		
		//printgameBoard
		printBoard(gameBoard, dimensions);


		//get player's move
		do
		{
			printf("Player %c Enter Position\n", player);
			printf("X coordinate: ");
			scanf("%d", &xCoord);
			printf("Y coordinate: ");
			scanf("%d", &yCoord);
			printf("Placing symbol at coordinates (%d,%d)\n", xCoord, yCoord);


		}while(checkIllegalMove(xCoord,yCoord, dimensions, player, gameBoard));

		
		//check if a player won
		//isPlaying = !checkWinner(player, dimensions, gameBoard);


		
		
		//update turns counter
		turns++;




	}
	

	return 0;
}




