#include "DisjointSet.h"

DisjointSet::DisjointSet(const int& numRows, const int& numCols){
	this->numRows = numRows;
	this->numCols = numCols;
	for (int i = 0; i < (numRows * numCols); i++) {
		elements[i] = i;
		rank[i] = 0;
	}
}

// Combines a and b into one set
void DisjointSet::dsUnion(int a, int b){
	a = find(a);
	b = find(b);

	if (a != b) {
		if (rank[a] < rank[b]) {
			elements[a] = b;
		}
		else if (rank[a] > rank[b]) {
			elements[b] = a;
		}
		else {
			rank[a] = rank[a] + 1;
			elements[b] = a;
		}
	}
}

// Returns representative of a
int DisjointSet::find(int a){
	if (elements[a] == a) {
		return a;
	}
	else {
		elements[a] = find(elements[a]);
		return elements[a];
	}
}

int DisjointSet::encode(Cell cell){
	return ((cell.row * numCols) + cell.column);
}

void DisjointSet::decode(int n){
	row = n / numCols;
	col = n % numCols;
}
