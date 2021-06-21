#pragma once
#include <ostream>
class Coordinate
{
private:
	int x;
	int y;
	int value;
	int threshold;

	void print(std::ostream& out);

	friend std::ostream& operator<<(std::ostream& out, Coordinate& coordinate);
public:
	Coordinate();
	Coordinate(int x, int y, int threshold);
	
	int getX() const;
	int getY() const;
	int getValue() const;

	void reset();
	void increment();

	bool isThreshold() const;
};

