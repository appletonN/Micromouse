
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


void mapmaze(struct Maze* mazeArg, Node* nodelist)
{
    Mouse mouse;
    mouse.maze = mazeArg;
    Stack openlist = {{0}};
    Stack history = {{0}};
    int i, j;
    
    //setup all mapping stuff
    SetupMapping(&mouse, &openlist, nodelist);
    
    //printStatus(mouse, &openlist);
    
    //while openlist is not empty
    while ( openlist.head )
    {
        printStatus(&mouse, &openlist, nodelist);
        
        /*  goto first item in openlist  */
        ExploreNewCell(&mouse, &openlist, &history, nodelist);
        
        /*  Map Current Cell   */
        checkcurrentcell(&mouse, &openlist, nodelist, &history); 
                                
        /* Check No Openlist Conflicts*/

        //check first item
        //if it is explored AND (not a node OR the end Node) 
        //remove from openlist
         while ( openlist.head && mouse.maze->cellno[0][openlist.data[openlist.head-1]].explored ) {
                pop(&openlist);
        }

        //for each item in the openlist
        for (i=0; i<openlist.head; i++)
        {
            if ( mouse.maze->cellno[0][openlist.data[i]].explored ) {

                //if next item in openlist is explored, remove
                for(j=i; j < openlist.head; j++) {
                    openlist.data[j] = openlist.data[j+1];
                }
                openlist.head--;
                i=-1; //start check again

            }           
        }//FOR

    
    
    }
    
    //Backtrack to Node
    while ( !mouse.maze->cellno[0][mouse.index].isNode )
        moveToAdjacentCell(&mouse, identifyDirection(&mouse, pop(&history)));
    
    //get back to star
 
    printStatus(&mouse, &openlist, nodelist); 
    
    //block off all dead end routes
    for ( i=1; i< WIDTH*HEIGHT; i++) 
        VMcheck(&mouse, i, nodelist);
            
    printStatus(&mouse, &openlist, nodelist);
    
}


void SetupMapping(Mouse* mouse, Stack* openlist, Node* nodelist)
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
        mouse->maze->cellno[0][i].walls = 0x02;
        
        //set North walls
        (mouse->maze->cellno[HEIGHT-1][i]).walls = 0x08;
    }
    
    //set east and west walls
    for ( i=0; i<HEIGHT; i++ )
    {
        //set east walls
        mouse->maze->cellno[i][WIDTH-1].walls |= 0x04;
        
        //set West Walls
        mouse->maze->cellno[i][0].walls |= 0x01;
    }
    
    //set LEDs
    mouse->LEDs = 0x00;
    
    //set start cell as node
    unsigned int StartNode = createNode(mouse, 0, nodelist);
    
    //set as parent Node
    mouse->parentNode = StartNode;
    mouse->currentConnection.cost = 0;
    mouse->currentConnection.direction = mouse->dir;
    
    //add starting walls, given by rules
    mouse->maze->cellno[0][0].walls |= 0x04;
    mouse->maze->cellno[0][0].noOfWalls = 3;
    mouse->maze->cellno[0][0].explored = 1;
    
    mouse->maze->cellno[0][1].walls |= 0x01;
    mouse->maze->cellno[0][1].noOfWalls = 2;
  
    //push frist cell to openlist
    push(openlist, WIDTH);
}

unsigned int createNode(Mouse* mouse, unsigned int index, Node* nodelist)
{
    unsigned int newNode = 0;
    
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
    cell* Nodecell = &(mouse->maze->cellno[0][index]);
    
    Nodecell->isNode = 1;
    Nodecell->nodeAddress = newNode;
    
    return newNode;
}

void checkcurrentcell(Mouse* mouse, Stack* openlist, Node* nodelist, Stack* history)
{
    int i, j;
    unsigned int GoBack = 0;
    unsigned int adjacentNode = 0;
    cell* currentcell;
    
    
    currentcell = &(mouse->maze->cellno[0][mouse->index]);
    
    currentcell->explored = 1;
    
    for ( i=0; i<3; i++)
    {
        //rotate in such a way that all directions are checked except backwards
        mouse->dir = turn(i, mouse->dir);
        
                
        int sensorval = readSensor(mouse->index, mouse->dir);
        
        //repeat twice
        for ( j=0; j<2; j++ )
        {
            if (mouse->index < WIDTH*HEIGHT) {
                //if there is a wall, add the wall by ORing the walls with the direction
                if (sensorval){
                    currentcell->walls |= mouse->dir;

                } else if ( !(currentcell->walls & mouse->dir) ) {
                    //if no wall, then if it's unexplored, add to the openlist
                    if ( !(currentcell->explored) ) {
                        push(openlist, mouse->index);

                    //else if it is a Node, connect with parent    
                    } else if ( j && currentcell->isNode ) {

                        adjacentNode |= turn(2, mouse->dir);   //mark direction as Node
                        GoBack = 1;             //turn around (corrected if current cell is Node)

                    }//IF UNEXPLORED / NODE

                }//IF
        }
            
            //move into cell ahead and turn around to append relevant wall
            mouse->index = incrementIndex(mouse->index, mouse->dir);
            mouse->dir = turn(2, mouse->dir);
            
            
            currentcell = &(mouse->maze->cellno[0][mouse->index]);
            
        }//FOR j
        
        
    }//FOR i

    mouse->dir = turn(1, mouse->dir);
    
    // j is used to check if turn cost should be added when connecting adjacent cells
    // it should not be if the current cell is a node (set to 1 if so)
    j=0;
    
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
        GoBack = 0;
        //if current cell is a Node, connect it to the parent Node
        virtualMouse(mouse, nodelist);
        //if it's still a node after VM check
        if ( currentcell->noOfWalls <= 1 ) {
            ConnectNodes(mouse, nodelist, mouse->dir);
            j=1;

            //set as parentNode
            mouse->parentNode = mouse->maze->cellno[0][mouse->index].nodeAddress;
            //set cost to move into adjacent cells as 1
            mouse->currentConnection.cost = 0;
        }
    }//FINISHED DEALING WITH NODE
    

    //add cost to move into adjacent cell
    mouse->currentConnection.cost += STRAIGHT_COST;
    unsigned int dir;

    //connect any adjacent Nodes
    for (i=0; i<4; i++) {
        //set dir as the correct direction relative to the mouse
        dir = turn(i, mouse->dir);

        //check if cell being looked at needs to be connected
        if ( adjacentNode & dir ) {

            //add turn cost if needed(only add once)
            if ( i && !j ) {
                mouse->currentConnection.cost += TURN_COST;
                j=1;
            }

            //set direction from node as correct if currently at a Node
            if (currentcell->noOfWalls <= 1)
                mouse->currentConnection.direction = dir;

            //move mouse onto node to be connected
            mouse->index = incrementIndex(mouse->index, dir);
            //connect Nodes
            ConnectNodes(mouse, nodelist, dir);

            //if it is the end, make it next cell to move to
            if ( nodelist[mouse->maze->cellno[0][mouse->index].nodeAddress].isEnd == 1 )
                history->head -= 2;

            //move mouse back
            mouse->index = incrementIndex(mouse->index, turn(2, dir));

            //move into the node if there is nowhere left to explore
            if( !openlist->head && !currentcell->isNode )
                moveToAdjacentCell(mouse, dir);

        }//CONNECT NODE
    }//ALL ADJACENT NODES CONNECTED

    //reset cost to correct value
    mouse->currentConnection.cost -= STRAIGHT_COST;
    //j = 1 if it is a node, where the cost will be reset when it leaves,
    //or if it turned while adding adjacent Nodes, so the cost is now too high
    if ( j )
        mouse->currentConnection.cost -= TURN_COST;
        
    
    //do a U-turn
    if ( GoBack ) {
        mouse->dir = turn(2, mouse->dir);
        MouseTurn(180);
        GoBack = 0;
    }
}

void ConnectNodes(Mouse* mouse, Node* nodelist, unsigned int dir)
{    
    //shortcut to parent node
    Node* ParentNode = &nodelist[mouse->parentNode];
    
    //save connection in ParentNode
    //save to index equal to number of connections already made, will store in a new index
    ParentNode->connections[ParentNode->noOfConnections] = mouse->currentConnection;
    //connect to current cell
    ParentNode->connections[ParentNode->noOfConnections].connectedCell = mouse->index;
    //increment number of connections
    ParentNode->noOfConnections++;
    
    int currentNodeIndex;
    //if current cell not already a Node
    if ( !(mouse->maze->cellno[0][mouse->index].isNode) ) {
        //create a New Node at the current cell
        currentNodeIndex = createNode(mouse, mouse->index, nodelist);
    } else {
        //otherwise, find where node is in the nodelist
        currentNodeIndex = mouse->maze->cellno[0][mouse->index].nodeAddress;
    }
    
    //create pointer to the Node within nodelist
    Node* CurrentNode = &nodelist[currentNodeIndex];
    
    //update connection information at correct index in Node
    CurrentNode->connections[CurrentNode->noOfConnections] = mouse->currentConnection;
    CurrentNode->connections[CurrentNode->noOfConnections].connectedCell = ParentNode->index;
    
    //set direction as opposite of the direction being faced now
    CurrentNode->connections[CurrentNode->noOfConnections].direction = turn(2, dir);

    //if it is connection a Node to itself, then this must be the Middle of the Maze, so the End
    if ( CurrentNode == ParentNode && CurrentNode->connections[CurrentNode->noOfConnections].cost == 13 ) 
        CurrentNode->isEnd = 1;
    
    CurrentNode->noOfConnections++;   
    
    //parent node is updated when a Node is left (in ExploreNewCell function)
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
        
        cell* currentCell = &(mouse->maze->cellno[0][mouse->index]);

        
        //Fix dead ends if dead end bit is set
        if ( mouse->DeadEnd && !currentCell->noOfWalls ) {
            //if no walls, there are 3 paths, so cannot destroy node (yet)
            //place wall behind
            currentCell->noOfWalls++;
            mouse->DeadEnd = 0;

        } else if ( mouse->DeadEnd && currentCell->noOfWalls == 1 ) {
            //if there is 1 wall, then the Node can be destroyed
            
            DestroyNode(mouse, nodelist, mouse->index);
            mouse->DeadEnd = 0;

        }//IF NO OF WALLS

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
        if ( ~(mouse->maze->cellno[0][mouse->index].walls) & 0x08 )
            return 0x08;

    } else if ( target == mouse->index + 1 ) {
        //target is left
        if ( ~(mouse->maze->cellno[0][mouse->index].walls) & 0x04 )
            return 0x04;

    } else if ( target == mouse->index - WIDTH ) {
        //target is below
        if ( ~(mouse->maze->cellno[0][mouse->index].walls) & 0x02 )
            return 0x02;

    } else if ( target == mouse->index - 1 ) {
        //target is right
        if ( ~(mouse->maze->cellno[0][mouse->index].walls) & 0x01 )
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
    
    //if at node now, make it parent and correct values before moving into new cell
    if ( mouse->maze->cellno[0][mouse->index].isNode ) {
        mouse->parentNode = mouse->maze->cellno[0][mouse->index].nodeAddress;
        mouse->currentConnection.cost = 0;
        mouse->currentConnection.direction = direction;
    }
    
    mouse->currentConnection.cost += STRAIGHT_COST;
    
    mouse->index = incrementIndex(mouse->index, mouse->dir);
    ForwardOneCell();
}

void virtualMouse(Mouse* mouse, Node* nodelist)
{
    int i;
    
    for (i = 1; i < WIDTH*HEIGHT; i++)
    {
        //for each cell in the maze
        //if it hasn't been explored, check if it's dead end
        if ( !(mouse->maze->cellno[0][i].explored) )
            VMcheck(mouse, i, nodelist);
    }
}

void VMcheck(Mouse* mouse, int index, Node* nodelist)
{
    cell* currentcell = &(mouse->maze->cellno[0][index]);
    
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
        currentcell->walls = 0x0F;
        
        //check cell in direction of new wall + append wall in that cell
        index = incrementIndex(index, dir);
        currentcell = &(mouse->maze->cellno[0][index]);
        dir = turn(2, dir);        
        currentcell->walls |= dir;
        
        if ( currentcell->explored )
            currentcell->noOfWalls++;
        
        //if it was a node but now is not, destroy it
        if ( currentcell->isNode && currentcell->noOfWalls > 1 )
            DestroyNode(mouse, nodelist, index);
        
        //run same check on adjacent cell to the one just found
        //(the wall has just been amended, so may reveal a new dead-end)
        VMcheck(mouse, index, nodelist);
                    
    }
}

void DestroyNode(Mouse* mouse, Node* nodelist, unsigned int index)
{
    cell* currentCell = &(mouse->maze->cellno[0][index]);
    
    Node* currentNode = &nodelist[mouse->maze->cellno[0][index].nodeAddress];
    Node* previousNode = &nodelist[mouse->maze->cellno[0][currentNode->connections[0].connectedCell].nodeAddress];

    //destroy node at current location
    mouse->maze->cellno[0][index].isNode = 0;
    nodelist[mouse->maze->cellno[0][index].nodeAddress].distToCentre = 0;
    //distToCentre = 0 used to find unused index in array
    
    mouse->DeadEnd = 0;
    
    if ( nodelist[currentCell->nodeAddress].noOfConnections == 1 ) {
        //revert parent to previous Node
        mouse->parentNode = mouse->maze->cellno[0][currentNode->connections[0].connectedCell].nodeAddress;
        
        previousNode->noOfConnections--;
        
        if ( mouse->index == index) {
            //if it was called from mouse
            //inherit cost and direction from connection between the Node that is destroyed and previous Node
            //decrement connection counter
            mouse->currentConnection = previousNode->connections[previousNode->noOfConnections];
            
            //if the mouse is in the Node to be destroyed, AND there is a wall in front of the mouse,
            //then the mouse will have to turn, so need to negate this by decrementing cost
            if ( currentCell->walls & mouse->dir )
                mouse->currentConnection.cost -= TURN_COST;
            
        } else {
            //if it was called from VM
            //add connection between previous Node and Node to be destroyed to the current connection
            mouse->currentConnection.cost += previousNode->connections[previousNode->noOfConnections].cost;
            //inherit the direction from previous Node
            mouse->currentConnection.direction = previousNode->connections[previousNode->noOfConnections].direction;
        
            //if a turn is required at the Node to be destroyed to get from previouNode to CurrentNode
            //add that to the cost. Determined by checking if the directions are opposite
            if ( currentNode->connections[0].direction != turn(2, mouse->currentConnection.direction) )
                mouse->currentConnection.cost += TURN_COST;
        
        }
            
    } else if ( nodelist[currentCell->nodeAddress].noOfConnections == 2 ) {
        
        Node* NextNode = &nodelist[mouse->maze->cellno[0][currentNode->connections[1].connectedCell].nodeAddress];
        int i, previousNodeConnectionNo, NextNodeConnectionNo;
        
        for ( i=0; i<4; i++){
            //determine which connection links to the node to be deleted
            
            if ( previousNode->connections[i].connectedCell == index )
                previousNodeConnectionNo = i;
            
            if ( NextNode->connections[i].connectedCell == index )
                NextNodeConnectionNo = i;
        }//FOR
        
        //edit data of both connecting nodes destroying the Node in the middle
        unsigned int previousNodecost = previousNode->connections[previousNodeConnectionNo].cost;
        
        previousNode->connections[previousNodeConnectionNo].connectedCell = NextNode->index;
        previousNode->connections[previousNodeConnectionNo].cost += NextNode->connections[NextNodeConnectionNo].cost;
        
        NextNode->connections[NextNodeConnectionNo].connectedCell = previousNode->index;
        NextNode->connections[NextNodeConnectionNo].cost += previousNodecost;
        
        //if a turn is required on theNode, increment cost
        //Check the direction the needs to go to get to previousNode is the opposite of the direction to
        //get to the NextNode - if it is, then the mouse goes in a straight line so cost is correct
        if ( currentNode->connections[0].direction != turn(2, currentNode->connections[1].direction) ) {
            previousNode->connections[previousNodeConnectionNo].cost += TURN_COST; 
            NextNode->connections[NextNodeConnectionNo].cost += TURN_COST;
        }
        
    }
}