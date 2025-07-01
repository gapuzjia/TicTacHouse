
#include <stdio.h>
#include <stdlib.h>

//node representing each cell 
typedef struct Cell{

	char val;
	struct Cell* right;

}Cell;

//node representing each row
typedef struct Row{

	Cell* head;
	struct Row* down; 

}Row;

//create a board with defined dimensions
Row* createBoard(int rows, int cols)
{
	Row* top = NULL;
	Row* prevRow = NULL;

	for (int i = 0; i < rows; i++)
	{
		Row* newRow = malloc(sizeof(Row));
		newRow->down = NULL;

		Cell* rowHead = NULL;
		Cell* prevCell = NULL;

        	for (int j = 0; j < cols; j++)
		{
            		Cell* newCell = malloc(sizeof(Cell));
            		newCell->val = '*';
            		newCell->right = NULL;

            		if (!rowHead)
                		rowHead = newCell;
            		else
                		prevCell->right = newCell;

            		prevCell = newCell;
        	}

        	newRow->head = rowHead;

        	if (!top)
            		top = newRow;
        	else
            		prevRow->down = newRow;

        	prevRow = newRow;
    	}

	return top;
}

//print board
void printBoard(Row* board, int dimensions) 
{
	Row* rowPtr = board;

    int y = 0;
    while (rowPtr && y < dimensions) 
    {
        //print y-axis labels (set backwards to mimic Q1 on Cartesian plane
        printf("%2d ", (dimensions - y));

        Cell* cellPtr = rowPtr->head;
        while (cellPtr) {
            printf(" %c ", cellPtr->val);
            cellPtr = cellPtr->right;
        }

        printf("\n");
        rowPtr = rowPtr->down;
        y++;
    
    }

	
    //print x axis labels and buffer
    printf("   ");
    for(int i = 1; i <= dimensions; i++)
        printf("%2d ", i);
    printf("\n");

}

int checkIllegalMove(int x, int y, int dimensions, char player, Row* gameBoard)
{
	//init rowPtr to first row
	Row* rowPtr = gameBoard;

	//adjust definition of y since coordinates are modeled backwards
	y = dimensions - y;

	//keep moving down until correct row is reached
	for(int i = 0; i < y; i++)
		rowPtr = rowPtr->down;
	
	//init cellPtr to first cell in row
	Cell* cellPtr = rowPtr->head;

	//keep moving to the right until correct column is reached
	for(int j = 1; j < x; j++)
		cellPtr = cellPtr->right;

	//if the contents of the cell is anything except a '*' then it is occupied
	if(cellPtr->val != '*')
	{
		printf("Cell is occupied!\n");
		return 1;
	}

	//fall through, means position is valid
	//EDIT APPROACH- get rid of modify board fucntion, can do here instead
	cellPtr->val = player;

	return 0;
}

int checkWalls(int xAnchor, int yAnchor, int dimensions, char player, Row* gameBoard)
{
        //init/declare rowPtr and cellPtr
        Row* rowPtr = gameBoard;
        Cell* cellPtr;

        //-----check top of walls
        //move rowPtr to 2 above yAnchor
        for(int i = 0; i < dimensions - yAnchor - 2; i++)
                rowPtr = rowPtr->down;

        //init cellPtr
        cellPtr = rowPtr->head;

        //move cellPtr to xAnchor
        for(int i = 0; i < xAnchor; i++)
                cellPtr = cellPtr->right;

        //top of walls are not in place, house is not made
        if(cellPtr->val != player || cellPtr->right->right->val != player)
                return 0;

        //------now check middle brick
        //move rowPtr down
        rowPtr = rowPtr->down;

        //re-initialize cellPtr
        cellPtr = rowPtr->head;

        //move cellPtr to xAnchor
        for(int i = 0; i < xAnchor; i++)
                cellPtr = cellPtr->right;

        //top of walls are not in place, house is not made
        if(cellPtr->val != player || cellPtr->right->right->val != player)
                return 0;


        //code falls through, means walls are in place and correct
        return 1;

}

int checkWinner(char player, int dimensions, Row* gameBoard)
{
	//declare tracking variables
	int yAnchor = dimensions - 5;
	int xAnchor;
	
	//init current rowPtr to the 5th row, base can only start at that row
	Row* rowPtr = gameBoard;
	for(int i = 0; i < 5; i++)
		rowPtr = rowPtr->down;

	while(rowPtr->down)
	{
		//init current cellPtr to one in, base can only start there
		Cell* cellPtr = rowPtr->head;
		cellPtr = cellPtr->right;

		//traverse all rows for 3 of the symbol in a row
		//dimensions - 2 prevents looking two to the right being null 
		for(int i = 1; i < dimensions - 2; i++)
		{
			xAnchor = i;
			
			//executes if a 3 in a row was found
			if(cellPtr->val == player && cellPtr->val == cellPtr->right->val && cellPtr->val == cellPtr->right->right->val)
			{
				printf("found 3 in a row\n");
				if(checkWalls(xAnchor, yAnchor, dimensions, player, gameBoard))
					printf("base and walls exist!");

			}
			
			//move to next pointer
			cellPtr = cellPtr->right;
		}
		
		//move rowPtr and update anchor tracker
		rowPtr = rowPtr->down;
		yAnchor--;
	}

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
	Row* gameBoard = createBoard(dimensions, dimensions);

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
