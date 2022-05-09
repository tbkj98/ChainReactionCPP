#include "..\include\Player.h"
#include "..\include\Board.h"
#include "../include/Game.h"


Player::Player(int id)
{
	this->id = id;
	this->name = "Player " + id;
	this->score = Game::NO_SCORE;
	this->color = colors[colors.size() - 1];
}

Player::Player(int id, std::string name, Color color)
{
	this->id = id;
	this->name = name;
	this->score = Game::NO_SCORE;
	this->color = color;
}

bool Player::operator==(Player const& obj)
{
	return this->id == obj.id && this->name == obj.name;
}

std::string Player::getName() const
{
	return name;
}

bool Player::isNoScore() const
{
	return score == Game::NO_SCORE;
}

bool Player::hasPlayed() const
{
	return dirty;
}

Color Player::getColor() const
{
	return color;
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
	this->color = player.color;
	this->score = player.score;
	this->dirty = player.dirty;
}

void Player::print(std::ostream& out)
{
	std::string stmt = "ID = " + std::to_string(id) + ", Name = " + name + ", Score = " + std::to_string(score);
	out << "\x1B[" << color.getCode() << "m" << stmt << "\033[0m\t\t";
}

std::ostream& operator<<(std::ostream& out, Player& player)
{
	player.print(out);
	return out;
}