
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


void mapmaze(Mouse* mouse, Node* nodelist)
{
    Stack openlist = {{0}};
    Stack history = {{0}};
    int i, j;
    
    //setup all mapping stuff
    SetupMapping(mouse, nodelist);
    
    checkcurrentcell(mouse, &openlist, nodelist);
    
    //undo dead end stuff
    mouse->DeadEnd = 0;
    mouse->dir = turn(2, mouse->dir);
    
    printStatus(mouse, &openlist);
    
    //while openlist is not empty
    while ( openlist.head )
    {
        /*  goto first item in openlist  */
        ExploreNewCell(mouse, &openlist, &history, nodelist);
        
        /*  Map Current Cell   */
        checkcurrentcell(mouse, &openlist, nodelist); 
        
        printStatus(mouse, &openlist);
             
        virtualMouse(&(mouse->maze));
        
        /* Check No Openlist Conflicts*/
               
        //check first item
        if ( mouse->maze.cellno[0][openlist.data[openlist.head-1]].explored ) {
            //if the cell at the top of the openlist is explored,
            //discard the top item in the list
            pop(&openlist);
        }
                
        //while check is not = 0
        for (i=0; i<openlist.head; i++)
        {
            if ( mouse->maze.cellno[0][openlist.data[i]].explored ) {
                
                //if next item in openlist is explored, remove
                for(j=i; j < openlist.head; j++) {
                    openlist.data[j] = openlist.data[j+1];
                }
                openlist.head--;
            }
            
        }
        
    }
    
    printStatus(mouse, &openlist);
            
}


void SetupMapping(Mouse* mouse, Node* nodelist)
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
    unsigned int StartNode = createNode(mouse, 0, nodelist);
    
    //set as parent Node
    mouse->parentNode = StartNode;
    mouse->currentConnection.cost = 0;
    mouse->currentConnection.direction = mouse->dir;
  
}

unsigned int createNode(Mouse* mouse, unsigned int index, Node* nodelist)
{
    unsigned int newNode;
    
    //count how many Nodes have been initialised
    while ( nodelist[newNode].distToCentre == -1 ) {
        //while item in nodelist is not 0
        newNode++;
    }
    
    nodelist[newNode].index              = index;
    nodelist[newNode].noOfConnections    = 0;
    nodelist[newNode].distToCentre       = -1;
    nodelist[newNode].isEnd              = 0;
    
    //update cell info
    cell* Nodecell = &(mouse->maze.cellno[0][index]);
    
    Nodecell->isNode = 1;
    Nodecell->nodeAddress = newNode;
    
    return newNode;
}


void checkcurrentcell(Mouse* mouse, Stack* openlist, Node* nodelist)
{
    int i, j;
    unsigned int GoBack = 0;
    cell* currentcell;
    
    
    currentcell = &(mouse->maze.cellno[0][mouse->index]);
    
    currentcell->explored = 1;
    
    for ( i=0; i<3; i++)
    {
        //rotate in such a way that all directions are checked except backwards
        mouse->dir = turn(i, mouse->dir);
        
        
        int sensorval = readSensor(mouse->index, mouse->dir);
        
        //repeat twice
        for ( j=0; j<2; j++ )
        {
            
            //if there is a wall, add the wall by ORing the walls with the direction
            if (sensorval){
                currentcell->walls |= mouse->dir;
                
            } else {
                //if no wall, then if it's unexplored, add to the openlist
                if ( !(currentcell->explored) ) {
                    push(openlist, mouse->index);
                    
                //else if it is a Node, connect with parent    
                } else if ( currentcell->isNode ) {
                    ConnectNodes(mouse, nodelist);
                    GoBack = 1;
                }//IF UNEXPLORED / NODE
                
            }//IF
            
            //move into cell ahead and turn around to append relevant wall
            mouse->index = incrementIndex(mouse->index, mouse->dir);
            mouse->dir = turn(2, mouse->dir);
            
            
            currentcell = &(mouse->maze.cellno[0][mouse->index]);
            
        }//FOR j
        
        
    }//FOR i

    mouse->dir = turn(1, mouse->dir);

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
        //if dead end, set bit and spin 180
        mouse->DeadEnd = 1;
        GoBack = 1;

    } else if ( currentcell->noOfWalls <= 1 ) {
        //if current cell is a Node, connect it to the parent Node
        ConnectNodes(mouse, nodelist);
    }
    
    if ( GoBack ) {
        mouse->dir = turn(2, mouse->dir);
        MouseTurn(180);
        GoBack = 0;
    }
}

void ConnectNodes(Mouse* mouse, Node* nodelist)
{    
    //shortcut to parent node
    Node* ParentNode = &nodelist[mouse->parentNode];
    
    //save connection in ParentNode
    ParentNode->connections[ParentNode->noOfConnections] = mouse->currentConnection;
    ParentNode->noOfConnections++;
    
    //if current cell not already a Node
    if ( !(mouse->maze.cellno[0][mouse->index].isNode) ) {
        //create a New Node at the current cell
        createNode(mouse, mouse->index, nodelist);
    }
    
    //add connection to the node at the current cell
    Node* CurrentNode = &nodelist[mouse->maze.cellno[0][mouse->index].nodeAddress];
    
    CurrentNode->connections[CurrentNode->noOfConnections] = mouse->currentConnection;
    
    //Set opposite direction as direction to Parent from current Node
    mouse->dir = turn(2, mouse->dir);
    CurrentNode->connections[CurrentNode->noOfConnections].direction = mouse->dir;
    mouse->dir = turn(2, mouse->dir);
    
    mouse->parentNode = mouse->maze.cellno[0][mouse->index].nodeAddress;
}


void ExploreNewCell(Mouse* mouse, Stack* openlist, Stack* history, Node* nodelist)
{
    //set target as most recently found unexplored cell
    unsigned int target = pop(openlist);
    unsigned int tempTarget;
    
    unsigned int direction = identifyDirection(mouse, target);
    
    //while first item in openlist is not adjacent
    while ( !direction )
    {
        tempTarget = pop(history);   
        
        //find the direction of that cell
        direction = identifyDirection(mouse, tempTarget);
        
        //move into the cell
        moveToAdjacentCell(mouse, direction);    
        
        cell* currentCell = &(mouse->maze.cellno[0][mouse->index]);
                       
        //if the dead end bit is set and the current cell is a Node 
        if ( mouse->DeadEnd && currentCell->isNode ) {
            //correct node
            
            //if there are no walls ( 3 possible paths )
            if ( !currentCell->noOfWalls ) {
                
                //place wall behind
                mouse->dir = turn(2, mouse->dir);
                currentCell->walls |= mouse->dir;
                mouse->dir = turn(2, mouse->dir);
                
            } else if ( currentCell->noOfWalls == 1 ) {
                //if only 1 wall (2 possible direction)
                //one has been determined to be a dead end,
                //so it can be considered a corridor.
                printf("%d", nodelist[currentCell->nodeAddress].noOfConnections);
                if ( !(nodelist[currentCell->nodeAddress].noOfConnections) ) {
                    //if there are no connections then destroy the Node
                    //the mouse will then see this as a corridor
                      
                    //set parent as pointer to the Node connected to the current one
                    //and update all working information about the parent cell
                    
                    mouse->currentConnection = nodelist[mouse->maze.cellno[0][mouse->index].nodeAddress].connections[0];
                    mouse->parentNode = mouse->maze.cellno[0][mouse->currentConnection.connection].nodeAddress;
                    
                    //destroy node at current location
                    mouse->maze.cellno[0][mouse->index].isNode = 0;
                    nodelist[mouse->maze.cellno[0][mouse->index].nodeAddress].distToCentre = 0;
                    //distToCentre = 0 used to find unused index in array
                    
                    int i;
                    for ( i=mouse->maze.cellno[0][mouse->index].nodeAddress; i<MAX_NODES; i++) {
                        //shift everything into the gap
                        nodelist[i] = nodelist[i+1];
                    }
                    
                    mouse->DeadEnd = 0;
                }//IF NO CONNECTIONS
                
            }//IF NO OF WALLS
            
        }//IF DEAD END BACKTRACK HAS REACHED NODE
        
        //check if target is reachable
        direction = identifyDirection(mouse, target);
    
    }//WHILE NOT ADJACENT TO TARGET
    
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
        
        mouse->dir = turn(1, mouse->dir);
        
        mouse->currentConnection.cost += TURN_COST;
        
        //set turn to RIGHT
        int turnDir = RIGHT;
        
        if ( !(direction & mouse->dir) ) {
            //if mouse is still not facing correct direction
            //look left
            
            mouse->dir = turn(2, mouse->dir);
            
            //set turn to LEFT
            turnDir = LEFT;
        }//IF TURN LEFT
        
        MouseTurn(turnDir);        
    }//IF TURN
    
    mouse->currentConnection.cost += STRAIGHT_COST;
    
    mouse->index = incrementIndex(mouse->index, mouse->dir);
    ForwardOneCell();
}

void virtualMouse(struct Maze* maze)
{
    int i;
    
    for (i = 0; i < WIDTH*HEIGHT; i++)
    {
        //for each cell in the maze
        //if it hasn't been explored, check if it's dead end
        if ( !(maze->cellno[0][i].explored) )
        VMcheck(maze, i);
    }
}


void VMcheck(struct Maze* maze, int index)
{
    cell* currentcell = &(maze->cellno[0][index]);
    
    //check if cell has 3 walls
    if ( currentcell->walls == 0x07 ||
         currentcell->walls == 0x0B ||
         currentcell->walls == 0x0D ||
         currentcell->walls == 0x0E ) 
    {
        //set cell as explored
        currentcell->explored = 1;

        //set dir to direction of gap
        unsigned int dir = ~(0xFFF0 | currentcell->walls);
        
        //set all walls to 1
        currentcell->walls |= 0x0F;
        
        //check cell in direction of new wall + append wall in that cell
        index = incrementIndex(index, dir);
        currentcell = &(maze->cellno[0][index]);
        dir = turn(2, dir);        
        currentcell->walls |= dir;
        
        //run same check on adjacent cell to the one just found
        //(the wall has just been amended, so may reveal a new dead-end)
        VMcheck(maze, index);
                    
    }
}
