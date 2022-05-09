#pragma once
#include "Coordinate.h"
#include <vector>
#include <memory>
#include <queue>
#include "Player.h"

class Board
{
private:
	
	// Board width
	int width;
	// Board height
	int height;

	// Representation of 2D board
	std::vector<std::vector<std::shared_ptr<Coordinate>>> matrix;

	// Initialising functions
	void init();
	void initMatrix();
	void initCoordinates();

	// Finds the coordinates in which a coordinate can explode
	std::vector<std::shared_ptr<Coordinate>> getAdjacentCoordinates(std::shared_ptr<Coordinate> coordinate) const;

	// Function to check in which direction explosion can take place
	bool isUpwardSpaceAvailable(std::shared_ptr<Coordinate>coordinate) const;
	bool isDownwardSpaceAvailable(std::shared_ptr<Coordinate> coordinate) const;
	bool isLeftwardSpaceAvailable(std::shared_ptr<Coordinate> coordinate) const;
	bool isRightwardSpaceAvailable(std::shared_ptr<Coordinate> coordinate) const;

	// Function to find the coordinate in a perticular direction
	std::shared_ptr<Coordinate> getRightwardCoordinate(std::shared_ptr<Coordinate> coordinate) const;
	std::shared_ptr<Coordinate> getLeftwardCoordinate(std::shared_ptr<Coordinate> coordinate) const;
	std::shared_ptr<Coordinate> getUpwardCoordinate(std::shared_ptr<Coordinate> coordinate) const;
	std::shared_ptr<Coordinate> getDownwardCoordinate(std::shared_ptr<Coordinate> coordinate) const;

	std::vector<std::shared_ptr<Player>> performOperations(std::queue<std::shared_ptr<Coordinate>>& queue, std::shared_ptr<Player> activePlayer);

public:

	Board(int width, int height);

	// Prints the matrix
	void print() const;

	// To insert the user entered coordinates into board
	// Returns the list of lost players(if any)
	std::vector<std::shared_ptr<Player>> insert(int x, int y, std::shared_ptr<Player> activePlayer);
	
	// To check if the coordinate is valid
	bool isCoordinatesValid(int x, int y, std::shared_ptr<Player> activePlayer);
};

