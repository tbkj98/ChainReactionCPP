#pragma once
#include "Coordinate.h"
#include <vector>
#include <memory>

class Board
{
private: 
	int width;
	int height;

	std::vector<std::vector<Coordinate>> matrix;
	
	void initBoard();
	void initCoordinates();
	void init();
	void explodeCoordinate(Coordinate& coordinate);
	
	bool isUpwardSpaceAvailable(Coordinate& coordinate) const;
	bool isDownwardSpaceAvailable(Coordinate& coordinate) const;
	bool isLeftwardSpaceAvailable(Coordinate& coordinate) const;
	bool isRightwardSpaceAvailable(Coordinate& coordinate) const;

	Coordinate getRightwardCoordinate(Coordinate& coordinate) const;
	Coordinate getLeftwardCoordinate(Coordinate& coordinate) const;
	Coordinate getUpwardCoordinate(Coordinate& coordinate) const;
	Coordinate getDownwardCoordinate(Coordinate& coordinate) const;
	
	std::vector<Coordinate> getAdjacentCoordinates(Coordinate& coordinate) const;
public:
	Board();
	Board(int width, int height);

	void print() const;
	void insert(int x, int y);
	bool isCoordinatesValid(int x, int y);
	
	void play();
};

