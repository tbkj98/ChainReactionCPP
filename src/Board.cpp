#include "../include/Board.h"
#include <iostream>
#include <queue>

void Board::play()
{
	print();

	int x, y;
	char inputToBeTaken = 'y';

	do
	{
		std::cout << "Enter coordinates\n";
		std::cin >> x >> y;
		if (isCoordinatesValid(x, y))
		{
			insert(x, y);
			print();
		}
		else
		{
			std::cout << "Enter valid coordinates\n";
		}

		std::cout << "Continue playing(y/n) ? = ";
		std::cin >> inputToBeTaken;

	} while (inputToBeTaken == 'y' || inputToBeTaken == 'Y');
}

void Board::initBoard()
{
	matrix = std::vector<std::vector<Coordinate>>(height);
	for (int i = 0; i < height; i++)
	{
		matrix[i] = std::vector<Coordinate>(width);
	}
}

void Board::initCoordinates()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			// Corner coordinate
			if ((i == 0 && (j == 0 || j == width - 1)) || (i == height - 1 && (j == 0 || j == width - 1)))
			{
				matrix[i][j] = Coordinate(i, j, 2);
			}
			// Sides coordinate
			else if (i == 0 || j == 0 || i == height - 1 || j == width - 1)
			{
				matrix[i][j] = Coordinate(i, j, 3);
			}
			// Middle coordinate
			else
			{
				matrix[i][j] = Coordinate(i, j, 4);
			}			
		}
	}
}

void Board::init()
{
	initBoard();
	initCoordinates();
}

void Board::performOperations(std::queue<Coordinate>& queue)
{
	while (!queue.empty())
	{
		Coordinate& coordinate = matrix[queue.front().getX()][queue.front().getY()];
		queue.pop();

		coordinate.increment();
		if (coordinate.isThreshold())
		{
			std::vector<Coordinate> adjacentCoordinates = getAdjacentCoordinates(coordinate);
			coordinate.reset();


			for (Coordinate& adjacentCoordinate : adjacentCoordinates)
			{
				queue.push(adjacentCoordinate);
			}
		}
	}
}

void Board::insert(int x, int y)
{
	Coordinate& coordinate = matrix[x][y];
	std::queue<Coordinate> queue;

	queue.push(coordinate);
	performOperations(queue);
}

Board::Board()
{
	this->width = 5;
	this->height = 5;

	init();
}

Board::Board(int width, int height)
{
	this->width = width;
	this->height = height;

	init();
}

void Board::print() const
{
	for (int x = 0; x < height; x++)
	{
		for (int y = 0; y < width; y++)
		{
			Coordinate coordinate = matrix[x][y];
			std::cout << coordinate << " ";
		}

		std::cout << "\n";
	}
}

bool Board::isCoordinatesValid(int x, int y)
{
	return (x < width && x > -1) && (y < height && height > -1);
}

std::vector<Coordinate> Board::getAdjacentCoordinates(Coordinate& coordinate) const
{
	std::vector<Coordinate> list;


	if (isDownwardSpaceAvailable(coordinate)) {
		auto t = getDownwardCoordinate(coordinate);
		list.push_back(matrix[t.getX()][t.getY()]);
	}

	if (isUpwardSpaceAvailable(coordinate)) {
		auto t = getUpwardCoordinate(coordinate);
		list.push_back(matrix[t.getX()][t.getY()]);
	}

	if (isLeftwardSpaceAvailable(coordinate)) {
		auto t = getLeftwardCoordinate(coordinate);
		list.push_back(matrix[t.getX()][t.getY()]);
	}

	if (isRightwardSpaceAvailable(coordinate)) {
		auto t = getRightwardCoordinate(coordinate);
		list.push_back(matrix[t.getX()][t.getY()]);
	}

	return list;
}

bool Board::isUpwardSpaceAvailable(Coordinate& coordinate) const
{
	return coordinate.getY() > 0;
}

bool Board::isDownwardSpaceAvailable(Coordinate& coordinate) const
{
	return coordinate.getY() < height - 1;
}

bool Board::isLeftwardSpaceAvailable(Coordinate& coordinate) const
{
	return coordinate.getX() > 0;
}

bool Board::isRightwardSpaceAvailable(Coordinate& coordinate) const
{
	return coordinate.getX() < width - 1;
}

Coordinate Board::getRightwardCoordinate(Coordinate& coordinate) const
{
	return matrix[coordinate.getX() + 1][coordinate.getY()];
}

Coordinate Board::getLeftwardCoordinate(Coordinate& coordinate) const
{
	return matrix[coordinate.getX() - 1][coordinate.getY()];
}

Coordinate Board::getUpwardCoordinate(Coordinate& coordinate) const
{
	return matrix[coordinate.getX()][coordinate.getY() - 1];
}

Coordinate Board::getDownwardCoordinate(Coordinate& coordinate) const
{
	return matrix[coordinate.getX()][coordinate.getY() + 1];
}