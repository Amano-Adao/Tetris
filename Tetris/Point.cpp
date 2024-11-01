#include "Point.h"
#include <string>


void Point::setX(int x) { this->x = x; }
void Point::setY(int y) { this->y = y; }
void Point::setXY(int x, int y) { this->x = x; this->y = y; }
void Point::swapXY() { int temp = x; x = y; y = temp; }
void Point::multiplyX(int factor) { x *= factor; }
void Point::multiplyY(int factor) { y *= factor; }
std::string Point::toString() const { return "[" + std::to_string(x) + "," + std::to_string(y) + "]"; }
