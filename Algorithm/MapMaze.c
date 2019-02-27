
/** 
 * @brief Use simulator or Mouse.
 * 
 * If the variable is set to 1, the simulator will be used. Otherwise the target will be
 * the actual mouse.
 */
///@{
#define SIMULATOR 1

#if SIMULATOR
	#include "simulator.h"
#else
    #include "MappingFunctions.h"
#endif
///@}

#include "MapMaze.h"
#include <stdlib.h>
#include <stdio.h>


void mapmaze(Mouse* mouse)
{
    Stack openlist = NULL;
    //setup all mapping stuff
    SetupMapping(mouse);
    
    //print mouse's maze (empty)
    printStatus(mouse, &openlist);
    
    checkcurrentcell(mouse, &openlist);
    
    printStatus(mouse, &openlist);
    
    //while openlist isn't empty
    while(openlist->nextitem);
    
    
    
}


void SetupMapping(Mouse* mouse)
{
    //initialise mouse
    mouse->index = 0;
    mouse->dir = 0x08;
    
    /* initialise maze */
    int i;
    
    //set top and bottom walls of max size maze
    for ( i=0; i<WIDTH; i++ )
    {
        //set south walls
        mouse->maze.cellno[0][i].walls = 0x02;
        
        //set North walls
        (mouse->maze.cellno[HEIGHT-1][i]).walls = 0x08;
    }
    
    //set east and west walls
    for ( i=0; i<HEIGHT; i++ )
    {
        //set east walls
        mouse->maze.cellno[i][WIDTH-1].walls |= 0x04;
        
        //set West Walls
        mouse->maze.cellno[i][0].walls |= 0x01;
    }
    
    //set LEDs
    mouse->LEDs = 0x00;
    
    //set start cell as node
    Node* StartNode = createNode(mouse, 0);
    
    //set as parent Node
    mouse->parentNode = StartNode;
    mouse->currentConnection.cost = 0;
    mouse->currentConnection.direction = mouse->dir;
  
}

Node* createNode(Mouse* mouse, unsigned int index)
{
    //make new Node and add info
    Node* newNode = malloc(sizeof(Node));
    
    newNode->index              = index;
    newNode->noOfConnections    = 0;
    newNode->distToCentre       = -1;
    newNode->isEnd              = 0;
    
    //update cell info
    cell* Nodecell = &(mouse->maze.cellno[index][0]);
    
    Nodecell->isNode = 1;
    Nodecell->nodeAddress = newNode;
    
    return newNode;
}


void checkcurrentcell(Mouse* mouse, Stack* openlist)
{
    int i, j;
    cell* currentcell;
    
    
    currentcell = &(mouse->maze.cellno[mouse->index][0]);
    
    currentcell->explored = 1;
    
    for ( i=0; i<3; i++)
    {
        //rotate in such a way that all directions are checked except backwards
        turn(i, mouse);
        
        
        int sensorval = readSensor(mouse->index, mouse->dir);
        
        //repeat twice
        for ( j=0; j<2; j++ )
        {
            
            //if there is a wall, add the wall by ORing the walls with the direction
            if (sensorval){
                currentcell->walls |= mouse->dir;
                
            } else {
                //if no wall, then if it's unexplored, add to the openlist
                if (!currentcell->explored) {
                    push(openlist, mouse->index);
                }
                
            }//IF
            
            //move into cell ahead and turn around to append relevant wall
            incrementIndex(mouse);
            turn(2, mouse);
            
            
            currentcell = &(mouse->maze.cellno[0][mouse->index]);
            
        }//FOR j
        
        
    }//FOR i
    
    turn(1, mouse);

    /*  UPDATE CELL INFO    */
    //  Check if dead end or Node
    if ( currentcell->noOfWalls == 1 ) {
        mouse->DeadEnd = 1;

    } else if ( currentcell->noOfWalls <= 1 ) {
        //if current cell is a Node, connect it to the parent Node
        ConnectNodes(mouse);
    }
    
    
    /*  VIRTUAL MOUSE WILL RUN HERE  */
}

void ConnectNodes(Mouse* mouse)
{
    //shortcut to parent node
    Node* ParentNode = mouse->parentNode;
    
    //save connection in ParentNode
    ParentNode->connections[ParentNode->noOfConnections] = mouse->currentConnection;
    ParentNode->noOfConnections++;
    
    //if current cell not already a Node
    if ( !mouse->maze.cellno[0][mouse->index].isNode ) {
        //create a New Node at the current cell
        createNode(mouse, mouse->index);
    }
    
    //add connection to the node at the current cell
    Node* CurrentNode = mouse->maze.cellno[0][mouse->index].nodeAddress;
    
    CurrentNode->connections[CurrentNode->noOfConnections] = mouse->currentConnection;
    
    //Set opposite direction as direction to Parent from current Node
    turn(2, mouse);
    CurrentNode->connections[CurrentNode->noOfConnections].direction = mouse->dir;
    turn(2, mouse);
    
    
}