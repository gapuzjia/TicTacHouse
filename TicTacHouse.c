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
	printBoard(gameBoard, dimensions);


	//start gameplay
	while(isPlaying)
	{

		//determine who's turn it is
		player = playerSymbols[(turns - 1) % NUM_PLAYERS];
		
		
		//get player's move
		do
		{
			printf("Player %c Enter Position\n", player);
			printf("X coordinate: ");
			scanf("%d", &xCoord);
			printf("Y coordinate: ");
			scanf("%d", &yCoord);
			printf("Placing symbol at coordinates (%d,%d)\n", xCoord, yCoord);


		}while(1);
		













	}
	

	return 0;
}
