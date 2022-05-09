#pragma once

#include <vector>
#include <memory>

#include "Board.h"
#include "Player.h"
#include "Coordinate.h"

class Game
{
private:

	// Default board width and height
	static const size_t BOARD_WIDTH = 5;
	static const size_t BOARD_HEIGHT = 5;

	// Default player count
	static const size_t MINIMUM_PLAYERS_COUNT = 2;
	static const size_t MAXIMUM_PLAYERS_COUNT = 4;
	
	// Play board
	std::shared_ptr<Board> board;

	// List of players
	std::vector<std::shared_ptr<Player>> players;
	// List index of active player
	size_t activePlayerIndex;

	// Board init
	void initBoard(size_t width, size_t height);
	// Players init
	void initPlayers();

	// Player count input function
	size_t takePlayerCountInput();

	// To check the game over status
	bool isGameOver() const;

	// Players turn switch
	void switchActivePlayer();
	// Print game finish message
	void printGameFinishedMessage();

	// Remove lost players from players
	void removeLostPlayers(std::vector<std::shared_ptr<Player>> lostPlayers);

	// Function to fill the player details
	std::shared_ptr<Player> takePlayerDetailInput(int id);
	Color takePlayerColorInput(int id);

	// Prints the matrix
	void print() const;

public:
	static const int NO_SCORE = 0;

	Game();
	Game(size_t width, size_t height);

	// Begin play
	void play();
};

