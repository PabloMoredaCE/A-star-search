# A* Robot Pathfinding
A C++ implementation of the A* search algorithm for finding a minimum-cost path through a weighted two-dimensional grid.

The environment contains traversable cells, obstacles, a starting position, and a destination. Each traversable cell has an associated cost, and the goal is to find the path with the lowest total traversal cost.

## Features
* Grid-based environment loaded from a text file.
* Weighted traversal costs.
* Obstacles.
* Four-directional movement.
* Initial and destination position detection.
* A* pathfinding.
* Open and closed node tracking.
* Path reconstruction.
* Console and file output.

## Environment
The environment is represented as a rectangular grid of integers.

Special values:
0   -> Initial position
10  -> Destination
-1  -> Obstacle

Any other value represents the cost of entering that cell.

Example:

2 2 2 2 2 2 10
2 2 2 2 -1 2 2
2 2 2 8 -1 8 8
2 2 0 2 -1 8 8
2 2 2 2 2 5 2
2 2 -1 -1 -1 -1 -1
2 2 2 2 2 2 2


## Movement

The robot can move in four directions:
Up
Down
Left
Right

A movement is valid when the destination cell:
* Is inside the environment boundaries.
* Is not an obstacle.

The cost of a movement is determined by the cell being entered.


## A* Search

Each state is represented by a position: (row, column)

A* evaluates nodes using: 
f(n) = g(n) + h(n)

where:
g(n) -> accumulated cost from the starting position
h(n) -> estimated cost to the destination

The heuristic used is a weighted Manhattan distance:
h(n) = 2 * (|destination_row - row| + |destination_col - column|)


## Project Structure

A-star-search/
├── README.md
├── Makefile
│
├── src/
│   ├── main.cpp
│   │
│   ├── environment.h
│   ├── environment.cpp
│   │
│   ├── robot.h
│   ├── robot.cpp
│   │
│   ├── node.h
│   │
│   ├── astar.h
│   └── astar.cpp
│
├── tests/
│   ├── test.txt
│   └── ...
│
└── output/
    └── ...


## Main Components

### Environment
Stores the grid
It provides access to:
* Grid dimensions.
* Individual cells.
* Environment output

### Robot
Stores the robot's current position and provides movement in the four available directions while validating boundaries and obstacles.

### Node
Represents a state considered by the search.

### AStar
Handles the search process and determines a minimum-cost path from the initial position to the destination.


## Input
The program reads the environment from a text file.
Each line represents one row of the grid.


## Output
The program can display and save:
* The generated search states.
* Open and closed node lists.
* The final path.
* The total path cost.
* The environment with the resulting path marked.