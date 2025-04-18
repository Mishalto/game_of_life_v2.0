# Conway's Game of Life
Conway's Game of Life is a cellular automaton devised by mathematician John Conway. It simulates the evolution of cells on a grid according to a few simple rules. Each cell can either be "alive" or "dead," and their state is determined by the states of neighboring cells.

## The game progresses in discrete time steps, and the state of the grid evolves based on the following rules:

- A live cell with fewer than two live neighbors dies (underpopulation).  

- A live cell with two or three live neighbors remains alive.  

- A live cell with more than three live neighbors dies (overpopulation).  

- A dead cell with exactly three live neighbors becomes alive (reproduction).  

It is a zero-player game, meaning its evolution is determined by its initial state, requiring no further input after the start.  

## Design
To set the initial positions of the cells, the set_start_position function is used. You need to specify the coordinates of all living cells in a vector, along with their count.  

## Build
1. Clone the repository  
2. Open the project in CMake.  
3. CMake will automatically pull all necessary dependencies, and the project will be ready to use.  
