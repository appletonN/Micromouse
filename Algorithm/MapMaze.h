/**
*		@file MapMaze.c
*		@brief Fully maps the maze.
*
*		Maps the full maze including placing nodes
*       and finding the connections between those
*       Nodes.
*
*
*		@author		Nick Appleton @ UWE Robotics
*
*		@date	24/2/19
*/

#ifndef MAPMAZE_H
#define	MAPMAZE_H

#include "../Stacks.h"

/**
 * @brief Representation of the Mouse in virtual space
 *
 * represents the mouse that inhabits the virtual maze. including physical
 * attributes and debugging info.
 */
typedef struct Mouse
{
	unsigned int dir : 4;				/**< Direction the mouse is facing */
	unsigned char index;					/**< Position of the mouse within the maze */
    unsigned int DeadEnd : 1;           /**< Marks whether backtracking from a dead end */
	struct Maze* maze;                  /**< contains the mouse's model of the maze */
    unsigned char parentNode;            /**< index of Node last viseted in nodelist, next node found will be connected to this */
    struct connection currentConnection;/**< Info about current exploration from parent Node */
} Mouse;


/**
 * @brief main maze-mapping function.
 * 
 * calls all the other functions to map out the whole
 * reachable maze.
 * 
 * @startuml
 *      [-> PIC : inMaze
 *      activate PIC
 * 
 *      create Mouse
 *      PIC -> Mouse : SetupMapping()
 *      create openlist
 *      PIC -> openlist : SetupMapping()
 *      create VirtualMouse
 *      PIC -> VirtualMouse : SetupMapping()
 * 
 *      loop While Openlist is Not Empty
 *         PIC -> Mouse ++ : ExploreNewCell()
 *            PIC <-- Mouse
 * 
 *            PIC -> Mouse : checkcurrentcell()
 *            PIC <-- Mouse --
 * 
 *         PIC -> openlist ** : Verify
 *            openlist -> openlist : DeleteDuplicates
 * 
 *            openlist -> openlist : pop()
 *      
 *         PIC <-- openlist -- :nextIndex
 *      end
 * 
 *      PIC -> Mouse ++ : BacktrackToNode
 *      return atNode
 * 
 *      PIC -> PIC : Dijekstra()
 *      
 *      PIC -> Mouse ++ : GotoStart
 *      return atStart
 *      
 *      PIC -> VirtualMouse ++: runVM()
 *      return
 * 
 *      [<- PIC : atStart
 *      deactivate PIC
 * @enduml 
 * 
 * @param nodelist  list of all the Nodes in the maze. can be considered the Nodemap.
 * @return          the index of the Node the mouse is currently at in the nodelist
 */
void mapmaze(struct Maze* mazeArg, Node* nodelist);

/**
 * @brief sets up the mouse ready to map out the maze.
 * 
 * Initialises the mouse's maze model as all 0s with a 
 * border of 1s. Sets the mouse's index to 0 and direction
 * to 0b1000 (North). Creates the start Node and seets it 
 * as the parent node.
 * 
 * @param openlist lise
 */
void SetupMapping(Stack* openlist, Node* nodelist);

/**
 * @brief creates a new node.
 * 
 * Initialises all the Node variables, sets the cell at
 * the correct index to a node and adds a pointer to the
 * new node.
 * 
 * @memberof Node
 * 
 * @param mouse     representation of the mouse in the maze.
 * @param index     index at which the new Node is to be created.
 * @return          a pointer to the newly created node.
 */
unsigned char createNode(unsigned char index, Node* nodelist);

/**
 * @brief updates info on the cell currently occupied.
 * 
 * This includes correcting all the walls in the current
 * cell and all adjacent cells, adding unexplored adjacent
 * cells to the openlist and changing the cells properties
 * to reflect it's status (it's now been explored).
 * 
 * @memberof Mouse
 * 
 * @startuml
 *      [-> Mouse ++ : checkcurnetcell()
 *  
 *      loop for each direction
 *          Mouse -> PIC ++ : readSensor()
 *          PIC -> Sensor ++ : getValue()
 *          return value
 *          PIC -> PIC : DecodeValue
 *          Mouse <-- PIC -- : WallOrNot
 *          
 *          alt Wall
 *              Mouse -> Maze ++: appendWall
 *              return
 *          else
 *              alt Not Explored
 *                  Mouse -> openlist : push()
 *                  return
 *              else Node is Adjacent
 *                  Mouse -> Nodelist ++ : addNode()
 *                  return
 *              end
 *          end
 *      end
 * 
 *      Mouse -> Maze ++ : countWalls
 *      Mouse <-- Maze : noOfWalls
 *      
 *      deactivate Mouse
 *      
 *      alt noOfWalls = 3
 *          Maze -> Maze : setDeadEnd
 *      else noOfwalls > 2
 *          Maze -> Nodelist ++ : setAsNode
 *          Nodelist -> Nodelist : connectNodes()
 *          return
 *      end
 *      [<-- Mouse --
 * @enduml
 * 
 * @param mouse     representation of the mouse in the maze.
 * @param openlist  The stack of cells to be explored.
 * @param Nodelist  list of all the Nodes in the maze.
 * @param history   stack of the cells which were visited by the mouse.
 */
void checkcurrentcell(Stack* openlist, Node* nodelist, Stack* history);

/**
 * @brief Connects the parent node to the current cell.
 * 
 * Adds a connection to the parent Node to the current cell, also
 * adds the connection back from current cell to parent Node. If the
 * current cell is not a Node, it creates a new node to use.
 * 
 * @memberof Node
 *  
 * @param mouse         representation of the mouse in the maze.
 * @param nodelist      List of all the Nodes in the maze.
 * @param dir           direction in which the mouse entered the cell to be connected to the parent.
 */
void ConnectNodes(Node* nodelist, unsigned char dir);

/**
 * @breif Used to get to new areas.
 * 
 * Pops the first item from the openlist and explores the cell
 * at that index. If the cell is not accessible from the current
 * cell, then it backtracks until it finds it.
 * 
 * @memberof Mouse
 * 
 * @startuml
 *      [-> Mouse ++ : ExploreNewCell
 * 
 *      Mouse -> openlist ++ : requestTarget
 *      openlist -> openlist : pop()
 *      Mouse <-- openlist -- : data
 *  
 *      Mouse -> Maze ++ : identifyDirection()
 *      return direction
 *  
 *      loop While not facing correct direction
 *          Mouse -> openlist ++ : backtrackSpace
 *          openlist -> openlist : pop()
 *          Mouse <-- openlist -- : history
 * 
 *          alt if dead end finished 
 *              Mouse -> Maze ++ : fixDeadEnd
 *              return
 *          end
 * 
 *          Mouse -> PIC ++ moveToAdjacentCell()
 *          return
 *      end
 *      
 *      Mouse -> Maze ++ : identifyDirection()
 *      return direction
 * 
 *      mouse -> PIC ++ : moveToAdjacentCell()
 *      return
 *      
 *      [<-- Mouse -- : atNewCell
 * 
 * @enduml
 *  
 * @param mouse         representation of the mouse in the maze.
 * @param openlist      The stack of cells to be explored.
 */
void ExploreNewCell(Stack* openlist, Stack* history, Node* nodelist);

/**
 * @brief identify in which direction a cell is.
 * 
 * Identifies which direction an adjacent cell is in, if the
 * target cell is not adjacent, then 0 is returned.
 * 
 * @param mouse     representation of the mouse in the maze.
 * @param target    the cell that the mouse is trying to get to.
 * @return          the direction of the adjacent cell.
 */
unsigned char identifyDirection(unsigned char target);

/**
 * @brief move mouse into an adjacent cell in the direction given.
 * 
 * Moves the physical mouse into a cell geven in the direction param.
 * 
 * @memberof mouse
 * 
 * @param mouse         representation of the mouse in the maze.
 * @param direction     the direction in which the adjacent cell is.
 */
void moveToAdjacentCell(unsigned char direction);

/**
 * @class VirtualMouse
 * 
 * @brief traverses maze and blocks any dead-ends.
 */

/**
 * @brief corrects any known but unexplored dead-ends.
 * 
 * Checks every cell in the maze, if the cell is unexplored and has 3
 * walls, then it will mark the cell as explored. This will get the 
 * cell removed from the openlist during the mapmaze function.
 * 
 * @memberof VirtualMouse
 * 
 * @param maze      the maze that needs to be checked.
 */
void virtualMouse(Node* nodelist);

/**
 * @brief checks one cell for dead end and corrects it.
 * 
 * @memberof VirtualMouse
 * 
 * checks if cell is dead end by looking at wall pattern. If it is, it
 * sets all the walls to 1, moves into the cell that connects to it and
 * runs the check on that cell too. This means the "virtual mouse" will 
 * move back through the dead-end corridor, correcting it cell by cell,
 * until it gets to either a non-fully-mapped cell or the end of that
 * corridor.
 * 
 * @param maze      The maze in which the cell being checked is held.
 * @param index     The index of the cell within the maze.
 */
void VMcheck(unsigned char index, Node* nodelist);

/**
 * @brief destroy a given Node.
 * 
 * Removes Node from nodelist by setting the distanceToStart as 0.
 * 
 * @memberof Node
 * 
 * @param mouse         representation of the mouse in the maze.
 * @param nodelist      List of all Nodes in the maze.
 * @param index         index where the Node to be destroyed is.
 */
void DestroyNode(Node* nodelist, unsigned char index);


#endif	/* MAPMAZE_H */
