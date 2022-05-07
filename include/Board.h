#pragma once
#include "Coordinate.h"
#include <vector>
#include <memory>
#include <queue>
#include "Player.h"

class Board
{
private:
	
	// Dimension of matrix
	int width;
	int height;

	std::vector<std::vector<std::shared_ptr<Coordinate>>> matrix;

	std::vector<std::shared_ptr<Player>> players;
	size_t activePlayerIndex;

	// Initialising functions
	void init();
	void initBoard();
	void initCoordinates();
	void initPlayers();

	// Finds the coordinates in which a coordinate can explode
	std::vector<std::shared_ptr<Coordinate>> getAdjacentCoordinates(std::shared_ptr<Coordinate> coordinate) const;

	// Function to check in which direction explosion can take place
	bool isUpwardSpaceAvailable(std::shared_ptr<Coordinate>coordinate) const;
	bool isDownwardSpaceAvailable(std::shared_ptr<Coordinate> coordinate) const;
	bool isLeftwardSpaceAvailable(std::shared_ptr<Coordinate> coordinate) const;
	bool isRightwardSpaceAvailable(std::shared_ptr<Coordinate> coordinate) const;

	bool isGameOver() const;

	// Function to find the coordinate in a perticular direction
	std::shared_ptr<Coordinate> getRightwardCoordinate(std::shared_ptr<Coordinate> coordinate) const;
	std::shared_ptr<Coordinate> getLeftwardCoordinate(std::shared_ptr<Coordinate> coordinate) const;
	std::shared_ptr<Coordinate> getUpwardCoordinate(std::shared_ptr<Coordinate> coordinate) const;
	std::shared_ptr<Coordinate> getDownwardCoordinate(std::shared_ptr<Coordinate> coordinate) const;

	void performOperations(std::queue<std::shared_ptr<Coordinate>>& queue);
	void switchActivePlayer();
	void printGameFinishedMessage();

	// Function to fill the player details
	std::shared_ptr<Player> takePlayerDetailInput(int id);

public:
	static const int NO_SCORE = 0;

	Board();
	Board(int width, int height);

	// Prints the matrix
	void print() const;
	// To take input from user
	void insert(int x, int y);
	// To check if the coordinate is valid
	bool isCoordinatesValid(int x, int y);

	// Begin play
	void play();
};

