#ifndef DISJOINTSET_H
#define DISJOINTSET_H
#include "pathfinder.h"

class DisjointSet
{
public:
	DisjointSet(const int& numRows, const int& numCols);
	void dsUnion(int a, int b);
	int find(int a);
	int encode(Cell cell);
	void decode(int n);
private:
	int numRows;
	int numCols;
	int row;
	int col;
	int elements[2500];
	int rank[2500];
};

#endif