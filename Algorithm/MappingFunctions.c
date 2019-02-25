
#include "MappingFunctions.h"


void turn(int N, Mouse* mouse)
{
	int i;

	for (i=0; i<N; i++)
	{ 
		mouse->dir = mouse->dir >> 1;

		if (mouse->dir == 0x00) 	//if mouse has shifted too far right
			mouse->dir = 0x08; 		//bring it back around to 1000 (facing North)
	}
}


void incrementIndex(Mouse* mouse)
{
    switch (mouse->dir) {
        case 0x01:                      //< facing N
            mouse->index += WIDTH;
            break;
            
        case 0x02:                      //< facing E
            mouse->index += HEIGHT;
            break;
            
        case 0x04:                      //< facing S
            mouse->index -= WIDTH;
            break;
            
        case 0x08:                      //< facing W
            mouse->index -= HEIGHT;
            break;
            
    }//SWITCH
}
