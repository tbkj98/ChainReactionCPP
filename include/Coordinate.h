#pragma once
#include <ostream>
#include "Player.h"
class Coordinate
{
private:

	// Constant value to represent coordinate is blank
	static const int BLANK_COORDINATE = -1;

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

	std::unique_ptr<Player> player;

	friend std::ostream& operator<<(std::ostream& out, Coordinate& coordinate);
public:
	Coordinate();
	Coordinate(const Coordinate& co);
	Coordinate(int x, int y, int threshold);
	Coordinate operator=(Coordinate const& obj);

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

