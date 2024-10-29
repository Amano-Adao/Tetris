#include "Point.h"
#include <iomanip>
#include <iostream>
#include <vector>
#include <cassert>
#include "Gameboard.h"

//static const int MAX_X = 10;		// gameboard x dimension
//static const int MAX_Y = 19;		// gameboard y dimension
//static const int EMPTY_BLOCK = -1;	// contents of an empty block

// MEMBER VARIABLES -------------------------------------------------

// the gameboard - a grid of X and Y offsets.  
//  ([0][0] is top left, [MAX_Y-1][MAX_X-1] is bottom right) 
//int grid[MAX_Y][MAX_X];
// the gameboard offset to spawn a new tetromino at.
//const Point spawnLoc{ MAX_X / 2, 0 };


// METHODS -------------------------------------------------
// 
// constructor - empty() the grid
Gameboard::Gameboard() {
		
	empty();
};

// fill the board with EMPTY_BLOCK 
//   (iterate through each rowIndex and fillRow() with EMPTY_BLOCK))
// - params: none
// - return: nothing
void Gameboard::empty() {
	for (int i{ 0 }; i < MAX_Y; i++) {
		for (int j{ 0 }; j < MAX_X; j++) {
			grid[i][j] = EMPTY_BLOCK;
		}
	}
	//getCompletedRowIndices().clear();
}

// print the grid contents to the console (for debugging purposes)
//   use std::setw(2) to space the contents out 
//   (google it, you'll need to #include <iomanip>).
//   If the content == EMPTY_BLOCK, print a '.', otherwise print the content.
// - params: none
// - return: nothing
void Gameboard::printToConsole() const {
		
	for (int row{ 0 }; row < MAX_Y; row++) {
		for (int col{ 0 }; col < MAX_X; col++) {
			if (grid[row][col] == EMPTY_BLOCK) {
				std::cout << std::left << std::setw(2) << '.';
			}
			else {
				std::cout << std::left << std::setw(2) << getContent(col, row); // grid[row,col]
			}
				
		}
		std::cout << std::endl;
	}
}

// Determine if a given Point is a valid grid location
// - param 1: a Point object
// - return: true if the point is a valid grid location, false otherwise
bool Gameboard::isValidPoint(const Point& p) const {
	if ((p.getX() >= 0) && (p.getX() < MAX_X) && (p.getY() >= 0) && (p.getY() < MAX_Y)) {
		return true;
	}
	return false;
}

// Determine if a given XY is a valid grid location
// - param 1: an int representing x
// - param 2: an int representing y
// - return: true if the x,y is a valid grid location, false otherwise
bool Gameboard::isValidPoint(int x, int y) const {
	if ((x >= 0) && (x < MAX_X) && (y >= 0) && (y < MAX_Y)) {
		return true;
	}
	return false;
}

Point Gameboard::getSpawnLoc() const{
	return spawnLoc;
}

// get the content at a given point 
// assert the point is valid (use isValidPoint())
// - param 1: a Point (the XY of the content weant to retrieve)
// - return: an int, the content from the grid at the specified point 
int Gameboard::getContent(const Point& p) const {
	//assert(isValidPoint(p));
	//if (isValidPoint(p)) {
		return grid[p.getY()][p.getX()];
	//}
}

// get the content at a given XY location
// assert the point is valid (use isValidPoint())
// - param 1: an int for X (column)
// - param 2: an int for Y (row)
// - return: an int, the content from the grid at the specified XY
int Gameboard::getContent(int x, int y) const {
	assert(isValidPoint(x,y));
	//if (isValidPoint(x, y)) {
		return grid[y][x];
	//}
}

// set the content at a given point (ignore invalid points)
// - param 1: a Point
// - param 2: an int representing the content we want to set at this location.
void Gameboard::setContent(const Point& p, int content) {
    if (isValidPoint(p)) {
        grid[p.getY()][p.getX()] = content;
    }
}

// set the content at an x,y position (ignore invalid points)
// - param 1: an int for X (column)
// - param 2: an int for Y (row)
// - param 3: an int representing the content we want to set at this location	
void Gameboard::setContent(int x, int y, int content) {
	if (isValidPoint(x, y)) {
		grid[y][x] = content;
	}       
	// .    . (0,2)
	// (1,0). (1,2)
}

// set the content for a set of points (ignore invalid points)
// - param 1: a vector of Points representing locations
// - param 2: an int representing the content we want to set.
void Gameboard::setContent(std::vector<Point>& v, int content) {
	for (Point& p : v) {
		setContent(p, content);
	}
}

// Determine if (valid) all points passed in are empty
// *** IMPORTANT: Assume invalid x,y values can be passed to this method.
// Invalid meaning outside the bounds of the grid.
// * ONLY TEST VALID POINTS (use isValidPoint()). Ignore invalid Points.
// Using invalid points to index into the grid would cause undefined behaviour. 
// - param 1: a vector of Points representing locations to test
// - return: true if the content at ALL VALID points is EMPTY_BLOCK, false otherwise
bool Gameboard::areAllLocsEmpty(const std::vector<Point>& v) const {
	for (const Point& p : v) {
		if ((!isValidPoint(p))&& (getContent(p) == EMPTY_BLOCK)) {
			return false;
		}
	}
	return true;
}

// Remove all completed rows from the board
//   use getCompletedRowIndices() and removeRows() 
// - params: none
// - return: the count of completed rows removed
int Gameboard::removeCompletedRows() {
	std::vector<int> v =(getCompletedRowIndices());
	int count = v.size();
	removeRows(v);
	//std::cout << "size:"<<v.size();
	return count;
}

// A getter for the spawn location
// - params: none
// - returns: a Point, representing our private spawnLoc
Point Gameboard::getSpawnLoc() {
	return spawnLoc;
}

//private:  // This is commented out to allow us to test. 

// return a bool indicating if a given row is full (no EMPTY_BLOCK in the row)
// assert the row index is valid
// - param 1: an int representing the row index we want to test
// - return: bool representing if the row is completed
bool Gameboard::isRowCompleted(int rowIndex) const {
	assert(rowIndex < MAX_Y);
	for (int x{ 0 }; x < MAX_X; x++) {
		if (getContent(x, rowIndex) == EMPTY_BLOCK) {    // grid[rowIndex][x]
			return false;
		}
	}
	return true;
}

// fill a given grid row with specified content
// - param 1: an int representing a row index
// - param 2: an int representing content
// - return: nothing
void Gameboard::fillRow(int rowIndex, int content) {
	for (int col{ 0 }; col < MAX_X; col++) {
		grid[rowIndex][col] = content;
		//setContent(rowIndex,col ,content);
	}
}

// scan the board for completed rows.
// Iterate through grid rows and use isRowCompleted(rowIndex)
// - params: none
// - return: a vector of completed row indices (integers).
std::vector<int> Gameboard::getCompletedRowIndices() const {
	std::vector<int> completedRows;
	for (int y{ 0 }; y < MAX_Y; y++) {
		if (isRowCompleted(y)) {
			completedRows.push_back(y);
		}
	}
	return completedRows;
}

// copy a source row's contents into a target row.
// - param 1: an int representing the source row index
// - param 2: an int representing the target row index
// - return: nothing
void Gameboard::copyRowIntoRow(int sourceRowIndex, int targetRowIndex) {
	for (int col{ 0 }; col < MAX_X; col++) {
			//grid[sourceRowIndex][col];   getContent(col, sourceRowIndex);
		setContent(col, targetRowIndex, getContent(col, sourceRowIndex)); //grid[targetRowIndex][col]  set(col,target)
	}
}

// In gameplay, when a full row is completed (filled with content)
// it gets "removed".  To be exact, the row itself is not removed
// but the content from the row above it is copied into it.
// This continues all the way up the grid until the first row is copied
// into the second row.  Finally, the first row is filled with EMPTY_BLOCK
// Given a row index:
//   1) Assert the row index is valid
//   2) Starting at rowIndex, copy each row above the removed
//     row "one-row-downwards" in the grid.
//     (loop from y=rowIndex-1 down to 0, and copyRowIntoRow(y, y+1)).
//   3) call fillRow() on the first row (and place EMPTY_BLOCKs in it).
// - param 1: an int representing a row index
// - return: nothing
void Gameboard::removeRow(int rowIndex) {
	assert(rowIndex < MAX_Y);
	for (int y{ rowIndex - 1 };y >= 0; y--) {
		copyRowIntoRow(y, y + 1);
	}
	fillRow(0, EMPTY_BLOCK);
}

// given a vector of row indices, remove them. 
//   Iterate through the vector, call removeRow() on each row index. 
// - param 1: a vector of integers representing row indices we want to remove
// - return: nothing
void Gameboard::removeRows(std::vector<int>& v) {
	for (int row : v) {
		removeRow(row);
			
	}
	//v.clear();
}