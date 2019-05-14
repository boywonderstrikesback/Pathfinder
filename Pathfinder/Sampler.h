#ifndef SAMPLER_H
#define SAMPLER_H
#include <stdlib.h> // for rand
#include <vector>
#include "pathfinder.h"


class Sampler {
public:
	Sampler(const int& numRows, const int& numColumns, uint8_t(*maze)[MAX_ROWS][MAX_COLS]);
	int sampleNoReplacement();
	int encode(Cell cell);
	Cell decode(int number);
	bool checkWallStatus(int item);
private:
	int numItems;
	int numRows;
	int numColumns;
	int items[10000];
	uint8_t (*maze)[MAX_ROWS][MAX_COLS];
};

#endif
