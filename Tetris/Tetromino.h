#pragma once
#include <vector>
#include "Point.h"

enum class TetColor { RED, ORANGE, YELLOW, GREEN, BLUE_LIGHT, BLUE_DARK, PURPLE, COUNT };
enum class TetShape { S, Z, L, J, O, I, T,COUNT };
class Tetromino
{
	// FRIENDS
	friend class GridTetromino;
	friend class TestSuite;// (allows TestSuite access to private members for testing)
	
private:
	TetColor color;
	TetShape shape;
	std::vector<Point> blockLocs;
public:
	Tetromino(){ setShape(TetShape::I); }
	TetColor getColor() const { return color; }
	TetShape getShape() const { return shape; }
	void setShape(TetShape shape);
	void rotateClockwise() ;
	void printToConsole() const;
	static TetShape getRandomShape();
};

