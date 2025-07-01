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

    for(int i = 0; i < dimensions; i++)
	    printf("%d ", i);
    printf("\n");

    while (rowPtr) 
    {
        Cell* cellPtr = rowPtr->head;
        
	while (cellPtr)
	{
            printf("%c ", cellPtr->val);
            cellPtr = cellPtr->right;
        }

        printf("\n");

        rowPtr = rowPtr->down;
    }
}




int main() 
{

	int dimensions;

	//prompt for dimensions of the board
	printf("Enter board size (ie enter 10 for a 10x10 board): ");
	scanf("%d", &dimensions);
	
	Row* gameBoard = createBoard(dimensions, dimensions);
	printBoard(gameBoard, dimensions);
	

	return 0;
}
