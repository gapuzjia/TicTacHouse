#include <stdio.h>
#include <stdlib.h>

//node representing each cell, now four-way connected 
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

int checkWinner(char player, int dimensions, Cell* gameBoard)
{
	//declare and init top left cell
	Cell* anchor;
	Cell* rowPtr = gameBoard;
	Cell* topRightWall;
	Cell* topLeftWall;
	
	//traverse entire gameBoard
        for (int i = 0; i < dimensions; i++)
        {

                anchor = rowPtr;

                for (int j = 1; j <= dimensions; j++)
                { 
			//checks if roof is present
                        if(anchor->val == player &&
                        (anchor->left->down && anchor->right->down && anchor->left->left->down && anchor->right->right->down) &&
			(anchor->left->down->val == player && anchor->right->down->val == player) &&
			(anchor->left->left->down->down->val == player && anchor->right->right->down->down->val == player))		 
                        {
				//track the top of both walls
                                topLeftWall = anchor->left->down->down->down;
                                topRightWall = anchor->right->down->down->down;

				//check if walls and floor is present
                                if(topLeftWall && topRightWall &&
				(topLeftWall->down->val && topRightWall->down->val) &&
				(topLeftWall->down->down->val && topRightWall->down->down->val) &&
				(topLeftWall->val == player && topRightWall->val == player) &&
				(topLeftWall->down->val == player && topRightWall->down->val == player) &&
				(topLeftWall->down->down->val == player && topRightWall->down->down->val == player) &&
				topLeftWall->down->down->right->val == player)
				{
					printf("Player %c WINS!!!\n", player);
					return 1;
				}
			}
			
			//move anchor to the right	
			anchor = anchor->right;
                }

		//move row pointer down
                rowPtr = rowPtr->down;
        }

	//code falls through, means no winner yet
	return 0;
}
 
 
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
		isPlaying = !checkWinner(player, dimensions, gameBoard);


		
		
		//update turns counter
		turns++;




	}
	

	return 0;
}




