#include "..\include\Player.h"
#include "..\include\Board.h"

int Player::num = 0;

Player::Player()
{
	this->id = ++Player::num;
	this->name = "Player " + id;
	this->score = Board::NO_SCORE;
	this->colorCode = 37;
}

Player::Player(int id)
{
	this->id = id;
	this->name = "Player " + id;
	this->score = Board::NO_SCORE;
	this->colorCode = 37;
}

Player::Player(int id, std::string name, int color)
{
	this->id = id;
	this->name = name;
	this->score = Board::NO_SCORE;
	this->colorCode = color;
}

bool Player::operator==(Player const& obj)
{
	return this->id == obj.id && this->name == obj.name;
}

int Player::getScore() const
{
	return score;
}

std::string Player::getName() const
{
	return name;
}

bool Player::hasPlayed() const
{
	return dirty;
}

int Player::getColorCode() const
{
	return colorCode;
}

void Player::setScore(int score)
{
	this->score = score;
}

void Player::played()
{
	this->dirty = true;
}

void Player::increment()
{
	++score;
}

void Player::decrement()
{
	--score;
}

Player::Player(Player const& player)
{
	this->id = player.id;
	this->name = player.name;
}

void Player::print(std::ostream& out)
{
	std::string stmt = "ID = " + std::to_string(id) + ", Name = " + name + ", Score = " + std::to_string(score);
	out << "\x1B[" << colorCode << "m" << stmt << "\033[0m\t\t";
}

std::ostream& operator<<(std::ostream& out, Player& player)
{
	player.print(out);
	return out;
}