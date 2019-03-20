/**
*		@file main.c
*		@brief this is the main file that controls the
*		robot.
*
*		Contains the mission planner and runs all
*		initialisation of maze. offloads most functionality
*		to external functions.
*
*
*		@author		Nick Appleton @ UWE Robotics
*
*		@date	21/2/19
*/

#include "Algorithm/MappingFunctions.h"
#include "Algorithm/MapMaze.h"
#include "Algorithm/Dijekstra.h"
#include "Integration/LED.h"
#include <stdlib.h>
#include <stdio.h>

_FWDT(WDT_OFF); 
//watch dog is disabled


int main(void)
{
//    setupLEDs();
//    timer1Setup();    
    
    //create maze
    struct Maze Cellmaze;
    
    //create array of Nodes
    Node nodelist[MAX_NODES] = {{0}};
    
    //Map the entire maze
    mapmaze(&Cellmaze, nodelist);
    
    //find end Node
    unsigned char EndNode = 0;
    while ( !nodelist[EndNode].isEnd )
        EndNode++;
    
    unsigned char i;
    //reset distance values
    for ( i=0; i<MAX_NODES; i++ ) {
        if ( nodelist[i].distToStart ) 
            nodelist[i].distToStart = -1;
    }   
    
    Stack fast;
    fast = dijekstra(&Cellmaze, nodelist, &nodelist[0], &nodelist[EndNode], 0x02);
      
    
    printf("done, bye bye\n\n\n");
	
	return 0;
}