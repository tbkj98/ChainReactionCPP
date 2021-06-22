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
	Player(Player& player);
	Player(int id, std::string name);
};

