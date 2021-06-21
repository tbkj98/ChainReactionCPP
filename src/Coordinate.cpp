#include "../include/Coordinate.h"

Coordinate::Coordinate()
{
	Coordinate(0, 0, 0);
}

Coordinate::Coordinate(int x, int y, int threshold)
{
	this->x = x;
	this->y = y;
	this->value = 0;
	this->threshold = threshold;
}

int Coordinate::getX() const
{
	return this->x;
}

int Coordinate::getY() const
{
	return this->y;
}

int Coordinate::getValue() const
{
	return this->value;
}

bool Coordinate::isThreshold() const 
{
	return this->value >= this->threshold;
}

void Coordinate::reset()
{
	this->value = 0;
}

void Coordinate::increment()
{
	++value;
}

std::ostream& operator<<(std::ostream& out, Coordinate& coordinate)
{
	coordinate.print(out);
	return out;
}

void Coordinate::print(std::ostream& out)
{
	out << this->value;
}
