#ifndef _PATHFINDER_H
#define _PATHFINDER_H
#include <stdint.h>

const int
  MAX_ROWS = 50,
  MAX_COLS = 50;

struct Cell {
	int row, column, direction;
};

//
// these are constants to use in the maze cells
//

enum CellValues {
  WALL_UP    = 0x01, // 0b0000'0001
  WALL_RIGHT = 0x02,
  WALL_DOWN  = 0x04,
  WALL_LEFT  = 0x08,
  VISITED    = 0x10, // used in searching
  DEAD_END   = 0x20  // used in searching
};

//=============================================================================
// void printMaze(uint8_t maze[][MAX_COLS],int nR,int nC);
//  print the given maze
//
// Parameters
//  maze - MAX_ROWS x MAX_COLS character array containing maze information
//  nR   - number of rows in the maze
//  nC   - number of columns in the maze
//

void printMaze(uint8_t maze[][MAX_COLS],int nR,int nC);

//=============================================================================
// bool wallExists(uint8_t maze[][MAX_COLS],int r,int c,int d)
//  tell if a wall exists at the given edge of the given cell
//
// Parameters
//  maze - the maze
//  r    - row to check
//  c    - column to check
//  d    - direction to check
//
// Returns
//  true if a wall exists at the given location and direction, false otherwise
//

bool wallExists(uint8_t maze[][MAX_COLS],int r,int c,int d);

//=============================================================================
// bool cellVisited(uint8_t maze[][MAX_COLS],int r,int c)
//  tell if a cell has been visited during the solution process
//
// Parameters
//  maze - the maze
//  r    - row to check
//  c    - column to check
//
// Returns
//  true if the cell was visited during solution, false if not
//

bool cellVisited(uint8_t maze[][MAX_COLS],int r,int c);

#endif
