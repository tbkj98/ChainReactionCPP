#include "..\include\Player.h"
#include "..\include\Player.h"

Player::Player()
{
	this->id = Player::num++;
	this->name = std::string(1, (65 + num));
}

Player::Player(int id)
{
	this->id = id;
	this->name = "Player " + id;
}

Player::Player(int id, std::string name)
{
	this->id = id;
	this->name = name;
}

bool Player::operator==(Player const& obj)
{
	return obj == nullptr ? false : this->id == obj.id && this->name == obj.name;
}

Player::Player(Player const& player)
{
	this->id = player.id;
	this->name = player.name;
}

void Player::print(std::ostream& out)
{
	out << "ID = " << id << " Name = " << name << "\n";
}

std::ostream& operator<<(std::ostream& out, Player& player)
{
	player.print(out);
	return out;
}