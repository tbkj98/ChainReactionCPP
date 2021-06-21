#pragma once
#include "Coordinate.h"
#include <vector>
#include <memory>

class Board
{
private: 
	// Dimension of matrix
	int width;
	int height;

	std::vector<std::vector<Coordinate>> matrix;
	
	// Initialising functions
	void initBoard();
	void initCoordinates();
	void init();

	// Function to explode the coordinate upon reaching the threshold
	void explodeCoordinate(Coordinate& coordinate);

	// Finds the coordinates in which a coordinate can explode
	std::vector<Coordinate> getAdjacentCoordinates(Coordinate& coordinate) const;
	
	// Function to check in which direction can explosion take place
	bool isUpwardSpaceAvailable(Coordinate& coordinate) const;
	bool isDownwardSpaceAvailable(Coordinate& coordinate) const;
	bool isLeftwardSpaceAvailable(Coordinate& coordinate) const;
	bool isRightwardSpaceAvailable(Coordinate& coordinate) const;

	// Function to find the coordinate in a perticular direction
	Coordinate getRightwardCoordinate(Coordinate& coordinate) const;
	Coordinate getLeftwardCoordinate(Coordinate& coordinate) const;
	Coordinate getUpwardCoordinate(Coordinate& coordinate) const;
	Coordinate getDownwardCoordinate(Coordinate& coordinate) const;
	
public:
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

