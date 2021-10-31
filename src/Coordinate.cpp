#include "../include/Coordinate.h"



Coordinate::Coordinate()
{
	this->x = 0;
	this->y = 0;
	this->value = 0;
	this->threshold = 0;
	this->ownerIndex = Coordinate::BLANK_COORDINATE;
	this->player = nullptr;
}

Coordinate::Coordinate(const Coordinate& co)
{
	this->x = co.x;
	this->y = co.y;
	this->value = 0;
	this->threshold = co.threshold;
	this->ownerIndex = Coordinate::BLANK_COORDINATE;
	this->player = nullptr;
}

Coordinate::Coordinate(int x, int y, int threshold)
{
	this->x = x;
	this->y = y;
	this->value = 0;
	this->threshold = threshold;
	this->ownerIndex = Coordinate::BLANK_COORDINATE;
	this->player = nullptr;
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

int Coordinate::getOwnerIndex() const
{
	return this->ownerIndex;
}

bool Coordinate::isThreshold() const 
{
	return this->value >= this->threshold;
}

bool Coordinate::isResetState() const
{
	return value == 0 && ownerIndex == Coordinate::BLANK_COORDINATE;
}

void Coordinate::reset()
{
	this->value = 0;
	this->ownerIndex = -1;
}

void Coordinate::increment()
{
	++value;
}

void Coordinate::setOwnerIndex(int index)
{
	this->ownerIndex = index;
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

Coordinate Coordinate::operator=(Coordinate const& obj)
{
	return Coordinate(obj);
}