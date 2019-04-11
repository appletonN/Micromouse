# Micromouse

This software was deveoped by Nicholas Appleton and Christian Woof of UWE Robotics. It is for use with a micromouse with a dsPIC30F4011 microcontroller. It is desined with compliance to the micromouse international competition. The maze that it was created to solve is an 8x6 maze, however, the size of the maze can be set accordingly and the actual size of the maze does not need to be known, as long as the size is set to greater than the actual size. A simulator is also included in the code so that the functionality can be tested without a physical mouse. To use the simulator, the integration folder should be excluded from the project, and the SIMULATOR macro set to 1. A series of test mazes can be found later in this document, these should be pasted into the simulator.c file.

The Maze contains a high level algorithm that maps the maze by pushing any cell it finds to an openlist of unexplored cells, from which the most recently found is explored. A nodemap is created where Nodes are created and destroyed as necissary to the final solving. A Dijkstra's algorithm has been used to find the fastest route through the maze, after each node has been checked, a cocktail search is used to order the priority queue so that the next node to be checked is the correct one.


# Test Mazes

Test mazes for use in the simulated environment. Each maze focusses on tripping up the algorithm in a different way.

1)
	{0,1,1,1, 0,1,1,1, 0,1,1,1, 0,1,1,1, 0,1,1,1, 0,1,1,1},
	{0,0,0,1, 0,1,0,0, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1},
	{0,1,0,1, 0,0,0,1, 1,0,0,0, 0,0,0,0, 1,0,0,0, 0,1,0,0},
	{0,1,0,1, 1,1,0,1, 0,0,1,1, 0,1,0,0, 0,1,1,1, 0,1,0,1},
	{0,1,0,1, 0,1,1,1, 1,0,0,1, 1,1,0,0, 0,0,0,1, 0,1,0,0},
	{0,1,0,1, 1,0,0,1, 1,0,1,0, 1,0,1,0, 1,1,0,0, 0,1,0,1},
	{0,0,0,1, 1,0,1,0, 1,0,1,0, 0,0,1,0, 1,0,1,0, 0,1,0,0},
	{1,0,0,1, 1,0,1,0, 1,1,1,0, 1,1,0,1, 1,0,1,1, 1,1,0,0}

2)
	{0,1,1,1, 0,0,1,1, 0,0,1,0, 0,0,1,0, 0,1,1,0, 0,1,1,1},
	{0,0,0,1, 0,1,0,0, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1},
	{0,1,0,1, 0,0,0,1, 1,0,0,1, 1,0,0,0, 0,1,0,0, 0,1,0,1},
	{0,0,0,1, 0,1,0,0, 0,0,1,1, 0,1,1,0, 0,1,0,1, 0,1,0,1},
	{0,1,0,1, 0,1,0,1, 1,0,0,1, 1,0,0,0, 0,1,0,0, 0,1,0,1},
	{0,0,0,1, 0,0,0,0, 1,0,1,0, 0,0,1,0, 1,0,0,0, 0,1,0,0},
	{0,1,0,1, 1,0,0,1, 0,1,1,0, 0,0,0,1, 0,0,1,0, 0,1,0,0},
	{1,0,1,1, 1,0,1,0, 1,0,0,0, 1,1,0,0, 1,1,0,1, 1,1,0,1}

3)
	{0,1,1,1, 0,0,1,1, 0,1,1,0, 0,0,1,1, 1,0,1,0, 0,1,1,0},
	{0,1,0,1, 0,1,0,1, 0,1,0,1, 0,1,0,1, 0,0,1,1, 1,1,0,0},
	{0,1,0,1, 0,1,0,1, 1,0,0,1, 1,1,0,0, 1,0,0,1, 0,1,1,0},
	{0,1,0,1, 0,1,0,1, 0,0,1,1, 0,0,1,0, 0,1,1,0, 0,1,0,1},
	{0,1,0,1, 0,1,0,1, 1,0,0,1, 1,1,0,0, 0,1,0,1, 0,1,0,1},
	{0,1,0,1, 0,1,0,1, 0,0,1,1, 0,1,1,0, 0,1,0,1, 0,1,0,1},
	{0,1,0,1, 1,0,0,1, 1,1,0,0, 1,0,0,1, 1,1,0,0, 0,1,0,1},
	{1,0,0,1, 1,0,1,0, 1,0,1,0, 1,0,1,0, 1,0,1,0, 1,1,0,0}

4)
	{0,1,1,1, 0,0,1,1, 0,0,1,0, 1,0,1,0, 0,1,1,0, 0,1,1,1},
	{1,0,0,1, 0,1,0,0, 0,1,0,1, 0,0,1,1, 1,1,0,0, 0,1,0,1},
	{0,0,1,1, 1,0,1,0, 1,0,0,0, 1,0,0,0, 0,0,1,0, 1,1,0,0},
	{0,1,0,1, 0,0,1,1, 0,0,1,0, 0,1,1,0, 0,1,0,1, 0,1,1,1},
	{0,0,0,1, 1,1,0,0, 1,0,0,1, 1,1,0,0, 0,1,0,1, 0,1,0,1},
	{1,0,0,1, 0,1,1,0, 0,0,1,1, 0,0,1,0, 0,0,0,0, 0,1,0,0},
	{0,1,1,1, 1,0,0,1, 1,1,0,0, 0,1,0,1, 0,1,0,1, 0,1,0,1},
	{1,0,0,1, 1,0,1,0, 1,0,1,0, 1,1,0,0, 1,1,0,1, 1,1,0,1}

5)
	{0,1,1,1, 0,1,1,1, 0,1,1,1, 0,0,1,1, 1,0,1,0, 0,1,1,0},
	{0,0,0,1, 0,0,0,0, 0,0,0,0, 0,0,0,0, 1,0,1,0, 0,1,0,0},
	{0,1,0,1, 0,1,0,1, 1,1,0,1, 1,0,0,1, 0,1,1,0, 0,1,0,1},
	{0,1,0,1, 0,1,0,1, 0,0,1,1, 0,1,1,0, 0,1,0,1, 0,1,0,1},
	{0,1,0,1, 0,1,0,1, 0,0,0,1, 1,1,0,0, 0,1,0,1, 0,1,0,1},
	{0,1,0,1, 1,0,0,1, 0,1,0,0, 0,0,1,1, 1,0,0,0, 0,1,0,0},
	{0,0,0,1, 1,1,1,0, 1,0,0,1, 0,0,0,0, 1,0,1,0, 0,1,0,0},
	{1,1,0,1, 1,0,1,1, 1,0,1,0, 1,0,0,0, 1,0,1,0, 1,1,0,0}

6)
	{0,1,1,1, 0,0,1,1, 1,1,1,0, 0,0,1,1, 1,1,1,0, 0,1,1,1},
	{0,0,0,1, 0,0,0,0, 1,0,1,0, 0,1,0,0, 0,1,1,1, 0,1,0,1},
	{0,1,0,1, 0,0,0,1, 1,1,1,0, 1,0,0,1, 0,0,0,0, 0,1,0,0},
	{1,1,0,1, 0,1,0,1, 0,0,1,1, 0,1,1,0, 0,1,0,1, 0,1,0,1},
	{0,0,1,1, 1,1,0,0, 0,0,0,1, 1,1,0,0, 1,1,0,1, 0,1,0,1},
	{0,1,0,1, 0,1,1,1, 0,1,0,1, 0,0,1,1, 1,0,1,0, 0,1,0,0},
	{1,0,0,1, 0,0,0,0, 0,0,0,0, 1,0,0,0, 1,0,1,0, 0,1,0,0},
	{1,0,1,1, 1,1,0,1, 1,0,0,1, 1,0,1,0, 1,0,1,0, 1,1,0,0}

