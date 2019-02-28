
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

/**
 * @brief cost of the movements between Nodes.
 */
///@{
#define TURN_COST 3
#define STRAIGHT_COST 1
///@}

#include "MapMaze.h"
#include <stdlib.h>
#include <stdio.h>


void mapmaze(Mouse* mouse)
{
    Stack openlist = NULL;
    Stack history = NULL;
    
    
    //setup all mapping stuff
    SetupMapping(mouse);
    
    checkcurrentcell(mouse, &openlist);
    
    //undo dead end stuff
    mouse->DeadEnd = 0;
    turn(2, mouse);
    
    printStatus(mouse, &openlist);
    
    //while openlist is not empty
    while ( openlist )
    {
        //goto first item in openlist
        ExploreNewCell(mouse, &openlist, &history);
        
        printStatus(mouse, &openlist);

        checkcurrentcell(mouse, &openlist);
        
        printStatus(mouse, &openlist);
    }
    printStatus(mouse, &openlist);
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
    cell* Nodecell = &(mouse->maze.cellno[0][index]);
    
    Nodecell->isNode = 1;
    Nodecell->nodeAddress = newNode;
    
    return newNode;
}


void checkcurrentcell(Mouse* mouse, Stack* openlist)
{
    int i, j;
    cell* currentcell;
    
    
    currentcell = &(mouse->maze.cellno[0][mouse->index]);
    
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
    
    // COUNT WALLS
    unsigned int walls = currentcell->walls;
    for ( i=0; i<4; i++)
    {
        //if first bit of walls is 1, increment noOfWalls
        if ( walls & 0x01 )
            currentcell->noOfWalls++;

        walls = walls >> 1;
    }
    
   
    //  Check if dead end or Node
    if ( currentcell->noOfWalls == 3 ) {
        mouse->DeadEnd = 1;
        turn(2, mouse);

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
    
    mouse->parentNode = CurrentNode;
}


void ExploreNewCell(Mouse* mouse, Stack* openlist, Stack* history)
{
    //set target as most recently found unexplored cell
    unsigned int target = pop(openlist);
    
    unsigned int direction = identifyDirection(mouse, target);
    
    //while first item in openlist is not adjacent
    while ( !direction )
    {
        //set target as last cell visited
        unsigned int tempTarget = pop(history);
        
        //find the direction of that cell
        direction = identifyDirection(mouse, tempTarget);
        
        //move into the cell
        moveToAdjacentCell(mouse, direction);    
        
        printStatus(mouse, openlist);
        
        cell* currentCell = &(mouse->maze.cellno[0][mouse->index]);
        
        //if the dead end bit is set and the current cell is a Node 
        if ( mouse->DeadEnd && currentCell->isNode ) {
            //correct node
            
            //if there are no walls ( 3 possible paths )
            if ( !currentCell->noOfWalls ) {
                
                //place wall behind
                turn(2, mouse);
                currentCell->walls |= mouse->dir;
                turn(2, mouse);
                
            } else if ( currentCell->noOfWalls == 1 ) {
                //if only 1 wall (2 possible direction)
                //one has been determined to be a dead end,
                //so it can be considered a corridor.
                
                if ( !currentCell->nodeAddress->noOfConnections ) {
                    //if there are no connections then destroy the Node
                    //the mouse will then see this as a corridor
                      
                    //set parent as pointer to the Node connected to the current one
                    //and update all working information about the parent cell
                    
                    mouse->currentConnection = mouse->maze.cellno[0][mouse->index].nodeAddress->connections[0];
                    mouse->parentNode = mouse->maze.cellno[0][mouse->currentConnection.connection].nodeAddress;
                    
                    //destroy node at current location
                    mouse->maze.cellno[0][mouse->index].isNode = 0;
                    free(mouse->maze.cellno[0][mouse->index].nodeAddress);
                    
                    mouse->DeadEnd = 0;
                }//IF NO CONNECTIONS
            }//IF NO OF WALLS
        }
        
        //check if target is reachable
        direction = identifyDirection(mouse, target);
    }
    push(history, mouse->index);
    
    //target is adjacent
    //direction points to target cell (not mouse->dir)
    moveToAdjacentCell(mouse, direction);
    
    
}


unsigned int identifyDirection(Mouse* mouse, unsigned int target)
{

    if ( target == mouse->index + WIDTH ) {
        //target is above
        if ( ~(mouse->maze.cellno[0][mouse->index].walls) & 0x08 )
            return 0x08;

    } else if ( target == mouse->index + 1 ) {
        //target is left
        if ( ~(mouse->maze.cellno[0][mouse->index].walls) & 0x04 )
            return 0x04;

    } else if ( target == mouse->index - WIDTH ) {
        //target is below
        if ( ~(mouse->maze.cellno[0][mouse->index].walls) & 0x02 )
            return 0x02;

    } else if ( target == mouse->index - 1 ) {
        //target is right
        if ( ~(mouse->maze.cellno[0][mouse->index].walls) & 0x01 )
            return 0x01;
        
    }
    return 0;
}

void moveToAdjacentCell(Mouse* mouse, unsigned int direction)
{
    
    if ( !(direction & mouse->dir) ) {
        //if mouse is not facing the correct direction
        //look right
        
        turn(1, mouse);
        
        mouse->currentConnection.cost += TURN_COST;
        
        //set turn to RIGHT
        int turnDir = RIGHT;
        
        if ( !(direction & mouse->dir) ) {
            //if mouse is still not facing correct direction
            //look left
            
            turn(2, mouse);
            
            //set turn to LEFT
            turnDir = LEFT;
        }//IF TURN LEFT
        
        MouseTurn(turnDir);        
    }//IF TURN
    
    mouse->currentConnection.cost += STRAIGHT_COST;
    
    incrementIndex(mouse);
    ForwardOneCell();
}