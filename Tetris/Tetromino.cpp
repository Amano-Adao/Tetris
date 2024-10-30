#include "Tetromino.h"
#include <iostream>
//enum class Tetcolor { RED, ORANGE, YELLOW, GREEN, BLUE_LIGHT, BLUE_DARK, PURPLE };
//enum class Tetshape { S, Z, L, J, O, I, T };

// - set the shape
// - set the blockLocs for the shape
// - set the color for the shape
void Tetromino::setShape(TetShape shape) {
	this->shape = shape;
	color = static_cast<TetColor>(shape);
	
	switch (shape) {
	case TetShape::O:
		blockLocs = { Point(0,0), Point(0,1),Point(1,1),Point(1,0) };
		break;
	case TetShape::I:
		blockLocs = { Point(0,0), Point(0,1),Point(0,2),Point(0,-1) };
		
		break;
	case TetShape::S:
		blockLocs = { Point(0,0), Point(-1,0),Point(0,1),Point(1,1) };
		
		break;
	
	case TetShape::Z:
		blockLocs = { Point(0,0), Point(-1,1),Point(0,1),Point(1,0) };
		
		break;
	case TetShape::L:
		blockLocs = { Point(0,0), Point(0,1),Point(0,-1),Point(1,-1) };
		
		break;
	case TetShape::J:
		blockLocs = { Point(0,0), Point(-1,-1),Point(0,1),Point(0,-1) };
		
		break;
	case TetShape::T:
		blockLocs = { Point(0,0), Point(-1,0),Point(1,0),Point(0,-1) };

		break;
	default:
		break;
	}


	
}

// print a grid to display the current shape
// to do this: print out a “grid” of text to represent a co-ordinate
// system. Start at top left [-3,3] go to bottom right [3,-3]
// (use nested for loops)
// for each [x,y] point, loop through the blockLocs and if the point exists
// in the list, print an 'x' instead of a '.'. You should end up with something
// like this: (results will vary depending on shape and rotation, eg: this
// one shows a T shape rotated clockwise once)
// .......
// .......
// ...x...
// ..xx...
// ...x...
// .......
//void Tetromino::printToConsole () const {
//	for (int i = 0; i <6; i++)
//	{
//		for (int j{ 0 }; j < 7; j++) {
//			bool pointExist = false;
//			for (const Point& p : blockLocs) {
//				if ((j - 3 == p.getX()) && (i - 2 == -p.getY())) {   // the print logic has a reversed y axis compared to point coordinate system
//					std::cout << "x";
//					pointExist = true;
//					break;
//				}
//			}
//			if (!pointExist) {
//				std::cout << ".";
//			}
//		}
//		std::cout << std::endl;
//	}
//}
void Tetromino::printToConsole () const {
	for (int y = 3; y > -3; y--){                           // start from left most to top bottom
		for (int x{ -3 }; x < 3; x++) {

			bool pointExist = false;
			for (const Point& p : blockLocs) {
				if ((x == p.getX()) && (y == p.getY())) {   // the print logic has a reversed y axis compared to point coordinate system
					std::cout << "x";
					pointExist = true;
					break;
				}
			}
			if (!pointExist) {
				std::cout << ".";
			}
		}
		std::cout << std::endl;
	}
}
// rotate the shape 90 degrees around [0,0] (clockwise)
// to do this:
// - iterate through blockLocs
// - rotate each Point 90 degrees clockwise around [0,0]
// hint: as you rotate the point [1,2] clockwise around [0,0], note
// how the x,y values change. Once you find the pattern you can use
// a couple existing methods in the Point class to accomplish this.
// make it so that the TetShape::O doesn’t rotate
void Tetromino::rotateClockwise() {
	if (this->getShape() == TetShape::O) {
		return;
	}
	for ( Point& p : blockLocs) {
		p.swapXY();
		p.multiplyY(-1);
	}
}
TetShape Tetromino::getRandomShape() {
	int tetShapeCount = static_cast<int>(TetShape::COUNT);
	int randShapeNum = rand() % tetShapeCount;
	TetShape randShape = static_cast<TetShape>(randShapeNum);
	return randShape;
}