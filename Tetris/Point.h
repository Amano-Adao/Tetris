#pragma once
#include <string>

class Point
{
	// FRIENDS
	friend class TestSuite;// (allows TestSuite access to private members for testing)
private:
	int x{ 0 };
	int y{ 0 };
public:
	Point() {};
	Point(int x, int y) : x{ x }, y{ y } {}
	int getX() const { return x; }
	int getY() const { return y; }
	void setX(int x) ;
	void setY(int y) ;
	void setXY(int x, int y) ;
	void swapXY() ;
	void multiplyX(int factor) ;
	void multiplyY(int factor);
	std::string toString() const ;
};




