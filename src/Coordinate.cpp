#include "../include/Coordinate.h"



Coordinate::Coordinate()
{
	this->x = 0;
	this->y = 0;
	this->value = 0;
	this->threshold = 0;
	this->owner = nullptr;
}

Coordinate::Coordinate(const Coordinate& co)
{
	this->x = co.x;
	this->y = co.y;
	this->value = co.value;
	this->threshold = co.threshold;
	this->owner = co.owner;
}

Coordinate::Coordinate(int x, int y, int threshold)
{
	this->x = x;
	this->y = y;
	this->value = 0;
	this->threshold = threshold;
	this->owner = nullptr;
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

std::shared_ptr<Player> Coordinate::getOwner() const
{
	return owner;
}

bool Coordinate::isThreshold() const 
{
	return this->value >= this->threshold;
}

bool Coordinate::isResetState() const
{
	return value == 0 && owner == nullptr;
}

void Coordinate::reset()
{
	this->value = 0;
	this->owner->decrement();
	this->owner = nullptr;
}

void Coordinate::increment()
{
	++value;
}

void Coordinate::setOwner(std::shared_ptr<Player> owner)
{
	this->owner = owner;
}

std::ostream& operator<<(std::ostream& out, Coordinate& coordinate)
{
	coordinate.print(out);
	return out;
}

void Coordinate::print(std::ostream& out)
{
	int colorCode = isResetState() ? 37 : owner->getColorCode();
	out << "\x1B[" << colorCode << "m" << this->value << "\033[0m\t\t";
}

Coordinate Coordinate::operator=(Coordinate const& obj)
{
	return Coordinate(obj);
}