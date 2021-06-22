#include "..\include\Player.h"
#include "..\include\Player.h"


Player::num = 0;

Player::Player()
{
	this->id = Player::num++;
	this->name = std::string(1, (65 + num));
}

Player::Player(int id, std::string name)
{
	this->id = id;
	this->name = name;
}

Player::Player(Player& player)
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
