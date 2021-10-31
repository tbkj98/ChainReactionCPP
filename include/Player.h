#pragma once

#include <string>

class Player
{
private:

	static int num;

	int id;
	std::string name;

	// Overloading the operator to directly print the object over console
	void print(std::ostream& out);
	friend std::ostream& operator<<(std::ostream& out, Player& player);
public:
	Player();
	Player(int id);
	Player(Player const& player);
	Player(int id, std::string name);
	bool operator == (Player const& obj);
};

