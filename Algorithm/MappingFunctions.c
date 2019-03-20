
#include "MappingFunctions.h"


unsigned char turn(char N, unsigned char dir)
{
	unsigned char i;
    
    
	for (i=0; i<N; i++)
	{ 
		dir = dir >> 1;

		if (dir == 0x00) 	//if mouse has shifted too far right
			dir = 0x08; 		//bring it back around to 1000 (facing North)
	}
    return dir;
}


unsigned char incrementIndex(unsigned char index, unsigned char dir)
{
    switch (dir) {
        case 0x08:                      //< facing N
            index += WIDTH;
            break;
            
        case 0x04:                      //< facing E
            index += 1;
            break;
            
        case 0x02:                      //< facing S
            index -= WIDTH;
            break;
            
        case 0x01:                      //< facing W
            index -= 1;
            break;
            
    }//SWITCH
    return index;
}
