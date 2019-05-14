#include "Sampler.h"

Sampler::Sampler(const int& numRows, const int& numColumns, uint8_t(*maze)[MAX_ROWS][MAX_COLS]){
	this->numRows = numRows;
	this->numColumns = numColumns;
	this->numItems = numRows * numColumns * 4; // each item is a wall at a cell. Each cell has 4 walls, so 4*numCells items exist
	this->maze = maze; // syntax for accessing elements is (*maze)[i][j]

	for (int i = 0; i < numItems; i++) {
		items[i] = i;
	}
}

// Returns int in Sampler encoded form
int Sampler::sampleNoReplacement(){
    int i = rand() % numItems;
    int e = items[i];
    numItems--;
    items[i] = items[numItems - 1];
    return e;
}

// Returns Sampler encoded form when given a Cell
int Sampler::encode(Cell cell){
	return (cell.row * numColumns + cell.column)*4 + cell.direction;
}

// Returns a Cell with data decoded from Sampler encoded form
Cell Sampler::decode(int number) {
	Cell result;
	result.direction = number % 4;
	result.column = (number / 4) % numColumns;
	result.row = number / (4 * numColumns);
	return result;
}


// Returns true if valid wall (existing and interior)
// Argument is in Sampler encoded form
bool Sampler::checkWallStatus(int item) {
	Cell cell = decode(item);

	// First checking if wall exterior
	if (cell.row == 0) {
		if (cell.direction == 0) {return false;}
	}
	if (cell.row == (numRows - 1)) {
		if (cell.direction == 2) {return false;}
	}
	if (cell.column == 0) {
		if (cell.direction == 3) {return false;}
	}
	if (cell.column == (numColumns - 1)) {
		if (cell.direction == 1) {return false;}
	}

	// At this point, wall not exterior
	// Then checking if walls don't exist
	switch (cell.direction) {
	case 0: if (((*maze)[cell.row][cell.column] & WALL_UP) == 0) {return false;}
	case 1: if (((*maze)[cell.row][cell.column] & WALL_RIGHT) == 0) {return false;}
	case 2: if (((*maze)[cell.row][cell.column] & WALL_DOWN) == 0) {return false;}
	case 3: if (((*maze)[cell.row][cell.column] & WALL_LEFT) == 0) {return false;}
	}

	// At this point, the walls are existing interior walls
	return true;
}
