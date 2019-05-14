/*
 * Pathfinder, by Devin Sigley 04/29/2018
 * Given a maze size between 1x1 and 50x50, generates
 * and solves a maze, then saves in "maze.ps".
 */

#include <iostream>
#include <stack>
#include "pathfinder.h"
#include "Sampler.h"
#include "DisjointSet.h"

using namespace std;

void generateMaze(const int& numRows, const int& numCols);
void getAdjacentCell(const Cell& currentCell, Cell& adjacentCell);
void removeWall(uint8_t(*maze)[MAX_ROWS][MAX_COLS], const Cell& currentCell, const Cell& adjacentCell);
void findPath(uint8_t(*maze)[MAX_ROWS][MAX_COLS], const int numRows, const int numCols);
bool wallExist(uint8_t(*maze)[MAX_ROWS][MAX_COLS], Cell cell, const int& numRows, const int& numColumns);

int main(){
	cout << "Welcome to Pathfinder. Please supply your maze dimensions:" << endl;
	int numRows = -1;
	int numCols = -1;
	do {
		cout << "Rows (whole number < 51): ";
		cin >> numRows;
		cout << "Columns (whole number < 51): ";
		cin >> numCols;
	} while (numRows < 1 || numRows > 50 || numCols < 1 || numCols > 50);

	generateMaze(numRows, numCols); // generates, solves, and prints maze

	cout << "Your maze has been generated and stored in \"maze.ps\"" << endl;
	return 0;
}

// Generates, solves, and prints maze in "maze.ps" file
void generateMaze(const int& numRows,  const int& numCols){
	
	uint8_t maze[MAX_ROWS][MAX_COLS];

	int count = 0;
	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCols; j++) {
			maze[i][j] = 15;
		}
	}

	DisjointSet ds(numRows, numCols);
	Sampler sampler(numRows, numCols, &maze);

	int i = 0, e = 0;
	Cell currentCell, adjacentCell;
	while (i < (numRows * numCols) - 1) {
		do {
			do {
				e = sampler.sampleNoReplacement();
			} while (!sampler.checkWallStatus(e));
			currentCell = sampler.decode(e);
			getAdjacentCell(currentCell, adjacentCell);
		} while (ds.find(ds.encode(currentCell)) == ds.find(ds.encode(adjacentCell)));
		ds.dsUnion(ds.encode(currentCell), ds.encode(adjacentCell));
		i++;
		removeWall(&maze, currentCell, adjacentCell);
	}

	findPath(&maze, numRows, numCols);
	printMaze(maze, numRows, numCols);

}

// Gets cell adjacent to current, stores in adjacent
void getAdjacentCell(const Cell& currentCell, Cell& adjacentCell) {
	switch (currentCell.direction) {
	case 0: 
		adjacentCell.row = currentCell.row - 1;
		adjacentCell.column = currentCell.column;
		break;
	case 1: 
		adjacentCell.row = currentCell.row;
		adjacentCell.column = currentCell.column + 1;
		break;
	case 2: 
		adjacentCell.row = currentCell.row + 1;
		adjacentCell.column = currentCell.column;
		break;
	case 3: 
		adjacentCell.row = currentCell.row;
		adjacentCell.column = currentCell.column - 1;
		break;
	}
	adjacentCell.direction = (currentCell.direction + 2) % 4;
}

// Toggle corresponding wall bit to off, for currentCell and its adjacentCell
void removeWall(uint8_t(*maze)[MAX_ROWS][MAX_COLS], const Cell& currentCell, const Cell& adjacentCell) {
	switch (currentCell.direction) {
	case 0: (*maze)[currentCell.row][currentCell.column] ^= WALL_UP; break;
	case 1: (*maze)[currentCell.row][currentCell.column] ^= WALL_RIGHT; break;
	case 2: (*maze)[currentCell.row][currentCell.column] ^= WALL_DOWN; break;
	case 3: (*maze)[currentCell.row][currentCell.column] ^= WALL_LEFT; break;
	}
	
	switch (adjacentCell.direction) {
	case 0: (*maze)[adjacentCell.row][adjacentCell.column] ^= WALL_UP; break;
	case 1: (*maze)[adjacentCell.row][adjacentCell.column] ^= WALL_RIGHT; break;
	case 2: (*maze)[adjacentCell.row][adjacentCell.column] ^= WALL_DOWN; break;
	case 3: (*maze)[adjacentCell.row][adjacentCell.column] ^= WALL_LEFT; break;
	}
}

// Solves the maze, marks DEAD_ENDs and VISITED cells (for use in printing maze)
void findPath(uint8_t(*maze)[MAX_ROWS][MAX_COLS], const int numRows, const int numCols) {
	stack<Cell> guesses;
	Cell current{ 0, 0, 0 };
	Cell adjacent;
	guesses.push(current);
	(*maze)[0][0] |= VISITED;

	while (true) {
		current = guesses.top();
		if (current.row == (numRows - 1) && current.column == (numCols - 1)) {
			break;
		}

		if (current.direction == 4) {
			(*maze)[current.row][current.column] |= DEAD_END; // mark as dead end
			guesses.pop(); // pop off stack
		}
		else {
			getAdjacentCell(current, adjacent);
			Cell nextDirection = current; 
			nextDirection.direction = nextDirection.direction + 1;
			guesses.pop();
			guesses.push(nextDirection);
			if (!wallExist(maze, current, numRows, numCols) && ((*maze)[adjacent.row][adjacent.column] & VISITED) == 0){
				adjacent.direction = 0;
				guesses.push(adjacent);
				(*maze)[adjacent.row][adjacent.column] |= VISITED; // setting space as visited
			}
		}
	}
}

// Returns whether or not a wall exists
bool wallExist(uint8_t(*maze)[MAX_ROWS][MAX_COLS], Cell cell, const int& numRows, const int& numColumns) {
	switch (cell.direction) {
	case 0: if (((*maze)[cell.row][cell.column] & WALL_UP) == 0) { return false; } break;
	case 1: if (((*maze)[cell.row][cell.column] & WALL_RIGHT) == 0) { return false; } break;
	case 2: if (((*maze)[cell.row][cell.column] & WALL_DOWN) == 0) { return false; } break;
	case 3: if (((*maze)[cell.row][cell.column] & WALL_LEFT) == 0) { return false; } break;
	}
	return true;
}
