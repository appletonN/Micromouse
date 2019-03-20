

#include "simulator.h"

#include <stdio.h>

/**
 * @name Maze Actual Simulated Dimensions
 *
 * @brief The actual size of the simulated maze.
 *
 * This section defines sizes that the simulated maze actually is.
 * The maze is used in the readSensors function as all the other functions
 * will refer to the mouses view of the maze.
 */
///@{
#define ACTUAL_WIDTH 6		/**< the Width the simulated maze actually is */
#define ACTUAL_HEIGHT 8		/**< the Height the simulated maze actually is */
///@}

#define DELAY 20000


int readSensor(int index, int direction)
{

	static int completeMaze[ACTUAL_HEIGHT][ACTUAL_WIDTH][4] = {
	{0,1,1,1, 0,0,1,1, 0,0,1,0, 0,0,1,0, 0,1,1,0, 0,1,1,1},
	{0,0,0,1, 0,1,0,0, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1},
	{0,1,0,1, 0,0,0,1, 1,0,0,1, 1,0,0,0, 0,1,0,0, 0,1,0,1},
	{0,0,0,1, 0,1,0,0, 0,0,1,1, 0,1,1,0, 0,1,0,1, 0,1,0,1},
	{0,1,0,1, 0,1,0,1, 1,0,0,1, 1,0,0,0, 0,1,0,0, 0,1,0,1},
	{0,0,0,1, 0,0,0,0, 1,0,1,0, 0,0,1,0, 1,0,0,0, 0,1,0,0},
	{0,1,0,1, 1,0,0,1, 0,1,1,0, 0,0,0,1, 0,0,1,0, 0,1,0,0},
	{1,0,1,1, 1,0,1,0, 1,0,0,0, 1,1,0,0, 1,1,0,1, 1,1,0,1}
	};

	/** @brief Which wall is being checked */
	int wall = 0;

	switch (direction) {
		case 0x01:
			wall++;
		case 0x02:
			wall++;
		case 0x04:
			wall++;
	}
    
	if (completeMaze[0][index][wall])
		return 1;
	else
		return 0;

}


 void printStatus(Mouse* mouse, Stack* openlist, Node* nodelist)
 {
 	int i, j;
    
 	for (i = HEIGHT-1 ; i>=0 ; i--)	//for every row (top-down)
 	{
 		//Start by drawing the North facing walls of the row
 		for (j = 0; j < WIDTH ; j++)
 		{
 			
 			if (mouse->maze->cellno[i][j].walls & 0x08) {
 				//print a wall if there is a wall to the North of the cell
 				printf("+---");

 			} else {
 				printf("+   ");
 			}

 		} //FOR j

 		printf("+\n"); 	//finish off row


 		//Next draw the West walls, and cell info
 		for (j = 0; j < WIDTH ; j++)
 		{ 
 			//draw West wall
 			if (mouse->maze->cellno[i][j].walls & 0x01) {
 				//print a wall if there is a wall to the West of the cell
 				printf("|");

 			} else {
 				printf(" ");
 			}

 			//draw cell info
 			// if (current cell == mouse cell)
 			if ( WIDTH*i + j == mouse->index ){
 				//print the mouse in red faving the correct direction
 				switch (mouse->dir){
 					case 0x08:
 						printf(" A ");
 						break;
 					case 0x04:
 						printf(" > ");
 						break;
 					case 0x02:
 						printf( " v " );
 						break;
 					case 0x01:
 						printf( " < " );
 						break;
 				}//SWITCH

 			} else if ( mouse->maze->cellno[i][j].isNode ) {
                //print N if it is a Node, or E for End, or S for start
                if ( nodelist[mouse->maze->cellno[i][j].nodeAddress].isEnd == 1 )
                    printf(" E ");
                else if ( mouse->maze->cellno[i][j].nodeAddress == 0 )
                    printf(" S ");
                else
                    printf( " N " );
                           
 			} else if ( WIDTH*i + j == openlist->data[openlist->head-1] ) {
                //if it's the first item in the openlist, print *
                printf(" X ");
                
            } else {
                printf("   ");
            }
 		} //FOR j
        
        printf("|\n");

 	} //FOR i
    
    //print bottom wall
    for (j = 0; j < WIDTH ; j++)
    {
        printf("+---");
    } //FOR j
    printf("+\n");
    
}
 
void MouseTurn(int direciton){}

void ForwardOneCell(void){}

void FollowRoute(Stack route){}