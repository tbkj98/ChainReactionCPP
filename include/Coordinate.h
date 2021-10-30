#pragma once
#include <ostream>
class Coordinate
{
private:
	// Coordinates for axes
	int x, y;

	// Value
	int value;

	// Threshold value on which the coordinate has to explode
	int threshold;

	// Overloading the operator to directly print the object over console
	void print(std::ostream& out);

	// Owner player index
	int ownerIndex;

	friend std::ostream& operator<<(std::ostream& out, Coordinate& coordinate);
public:
	Coordinate();
	Coordinate(int x, int y, int threshold);
	
	int getX() const;
	int getY() const;
	int getValue() const;
	int getOwnerIndex() const;

	void reset();
	void increment();
	void setOwnerIndex(int index);

	bool isThreshold() const;
	bool isResetState() const;
};

