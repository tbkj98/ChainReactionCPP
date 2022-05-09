#pragma once

#include <string>
#include <ostream>

#include "Color.h"

class Player
{
private:
	std::string name;
	int id;
	int score;
	Color color;

	// Indicating, that player playing for second time in single game
	bool dirty;

	// Overloading the operator to directly print the object over console
	void print(std::ostream& out);
	friend std::ostream& operator<<(std::ostream& out, Player& player);
public:
	Player(int id);
	Player(Player const& player);
	Player(int id, std::string name, Color color);

	bool operator == (Player const& obj);
	
	std::string getName() const;
	bool isNoScore() const;
	bool hasPlayed() const;
	Color getColor() const;

	void played();
	void increment();
	void decrement();
};

