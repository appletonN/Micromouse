
#include "Dijekstra.h"
#include "MappingFunctions.h"

#define LEFTT   2
#define RIGHTT  1
#define UTURN   3

Stack dijekstra(struct Maze* maze, Node nodemap[MAX_NODES], Node* start, Node* end, char startdir)
{
    unsigned char i, j, extracost;
   
    //set openlists
    Node* openlist[MAX_NODES] = {0};
    unsigned char openlisthead = 0;
  
    //check start Node to begin with
    Node* currentNode = start;
    Node* connectedNode;
    currentNode->distToStart = 0;
    
    while ( currentNode != end )
    {
        
        //check each connection connected to the current cell
        for ( i=0; i<currentNode->noOfConnections; i++) {
            extracost = 0;  
            
            //Node being looked at
            connectedNode = &nodemap[maze->cellno[0][currentNode->connections[i].connectedCell].nodeAddress];            

            //add turn if necessary
            if ( currentNode != start && currentNode->connections[i].direction != turn(2, currentNode->connections[j].direction) )
                extracost += TURN_COST; 
         
            //if it is a new shortest path to this Node, then update the cost
            if ( currentNode->distToStart + currentNode->connections[i].cost + extracost < connectedNode->distToStart 
                    || connectedNode->distToStart == -1 ) {
                
                //if it is a new candidate, add it to the openlist
                if ( connectedNode->distToStart == -1 ) {

                    openlist[openlisthead] = connectedNode;
                    openlisthead++;
                
                }
                
                connectedNode->distToStart = currentNode->distToStart + currentNode->connections[i].cost + extracost;
                connectedNode->via = currentNode->index;               
               
            }

        }//FOR
                    
        //reorder priority queue
        cocktail(openlist);
        
        //look at next item in queue
        currentNode = openlist[openlisthead-1];
        openlisthead--;
        
        //find which connection connects back to the previous Node in the route
        for ( j=0; j<4; j++ ) {
            if ( currentNode->connections[j].connectedCell == currentNode->via ) {
                break;
            }
        }     
            
    }//WHILE
    
    //nodemap now contains shortest path
    
    Stack route = {{0}};
    route.head = 0;
    unsigned char index, move, dir;
    
    move = 0;    
    
    //get ready to move down path
    index = currentNode->index;
    dir = currentNode->connections[0].direction;
    
    //loop back through route and push each to the openlist
    while ( currentNode != start )
    {        
        //calculate direction of via Node
        for ( j=0; j<4; j++ ) {
            //find which connection is the via Node
            if ( currentNode->connections[j].connectedCell == currentNode->via ) {
                //set direction to correct value
                //check if it's facing the right way to start with
                for ( i=0; i<=3; ++i ) {
                    //checks right, then left, then back
                    dir = turn(i, dir);

                    //when it's facing the right way, break
                    if ( currentNode->connections[j].direction == dir )
                        break;
                }
                //if turn is needed, push straight and turn and reset counter
                if ( i ) {
                    push(&route, move);
                    push(&route, i);
                    move = 0;
                } else {
                    move++;
                }
                
                break;
            }
        }       
        
        index = incrementIndex(index, dir);
        
        //move to via Node
        while ( !maze->cellno[0][index].isNode || index == currentNode->index ) {
            
            //if there is a wall in front
            if ( dir & maze->cellno[0][index].walls ) {
                push(&route, move);
                dir = turn(1, dir);
                
                //turn left is required
                move = RIGHTT;
                if ( dir & maze->cellno[0][index].walls ) {
                    //turn right
                    move = LEFTT;
                    dir = turn(2, dir);
                }
                //push to openlist and reset move counter
                push(&route, move);
                move = 0;
                
            } else {
                move++;
            }
            
            
            
            index = incrementIndex(index, dir);
            
        }//WHILE
        
        currentNode = &nodemap[maze->cellno[0][index].nodeAddress];
    }//WHILE
            
    //push the straight
    push(&route, move);

    //check if it's facing the right way to start with
    for ( i=0; i<=3; ++i ) {
        //checks right, then left, then back
        dir = turn(i, dir);

        //when it's facing the right way, break
        if ( dir == turn(2,startdir) )
            break;
    }
    //push initial turn
    push(&route, i);
    
    //reeset for next run
    for ( i=0; i<MAX_NODES; i++ ) {
        if ( nodemap[i].distToStart )
            nodemap[i].distToStart = -1;
    }
    start->distToStart = -1;
    
      route;
}


void cocktail(Node* arr[MAX_NODES])
{
    unsigned char flag, i, j;
    Node* temp;
    
    unsigned char sizes[2] = {0, MAX_NODES -2};
    while(1)
    {
            
         for ( i=0; i<2; i++ ) {   //0 counts up, 1 counts down
            flag = 1;
            
            //start checking
            for ( j=sizes[i]; j!=sizes[!i]; ) {
                
                if ( arr[j+1]->distToStart > arr[j]->distToStart ) {      //swap elements if they are in the wrong order
                    temp = arr[j];
                    arr[j] = arr[j+1];
                    arr[j+1] = temp;
                    flag = 0;
                }
                
                if ( i )
                    j--;
                else
                    j++;
            }
            
            //if no elements were swapped, break out if both directions have been checked
            if ( flag && i )
                return;
        }
    }
}
