#pragma once
#include <ostream>
#include "Player.h"
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

	std::shared_ptr<Player> owner;

	friend std::ostream& operator<<(std::ostream& out, Coordinate& coordinate);
public:
	Coordinate();
	Coordinate(const Coordinate& co);
	Coordinate(int x, int y, int threshold);
	Coordinate operator=(Coordinate const& obj);

	int getX() const;
	int getY() const;
	int getValue() const;
	std::shared_ptr<Player> getOwner() const;

	void reset();
	void increment();
	void setOwner(std::shared_ptr<Player> owner);

	bool isThreshold() const;
	bool isResetState() const;
};

