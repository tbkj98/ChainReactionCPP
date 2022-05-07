#pragma once

#include <string>
#include <ostream>

class Player
{
private:

	static int num;

	std::string name;
	int id;
	int score;
	int colorCode;

	// Indicating, that player playing for second time in single game
	bool dirty;

	// Overloading the operator to directly print the object over console
	void print(std::ostream& out);
	friend std::ostream& operator<<(std::ostream& out, Player& player);
public:
	Player();
	Player(int id);
	Player(Player const& player);
	Player(int id, std::string name, int color);

	bool operator == (Player const& obj);
	
	std::string getName() const;
	int getScore() const;
	bool hasPlayed() const;
	int getColorCode() const;

	void setScore(int score);
	void played();
	void increment();
	void decrement();
};

