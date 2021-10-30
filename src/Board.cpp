#include "../include/Board.h"
#include <iostream>
#include <queue>
#include <string>

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
			switchActivePlayer();
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
	initPlayersName();
	initPlayersScore();
}

void Board::initPlayersScore()
{
	int playersCount = playersName.size();
	playersScore = std::vector<int>(playersCount);
	for (int i = 0; i < playersCount; i++)
	{
		playersScore.push_back(0);
	}
}

void Board::initPlayersName()
{
	int playersCount = 0;
	std::cout << "How many players = ";
	std::cin >> playersCount;

	playersName = std::vector<std::string>(playersCount);

	for (int i = 0; i < playersCount; ++i)
	{
		std::cout << "Please enter name for player " << i << " = ";
		std::string name = "";
		std::cin >> std::ws;
		std::getline(std::cin, name);
		playersName[i] = name;
	}
}

void Board::performOperations(std::queue<Coordinate>& queue)
{
	while (!queue.empty())
	{
		Coordinate& coordinate = matrix[queue.front().getX()][queue.front().getY()];
		queue.pop();

		int ownerIndex = coordinate.getOwnerIndex();
		--playersScore[ownerIndex];
		coordinate.setOwnerIndex(activePlayerIndex);
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

void Board::switchActivePlayer()
{
	if (activePlayerIndex < (playersName.size() - 1))
		++activePlayerIndex;
	activePlayerIndex = 0;
}

void Board::insert(int x, int y)
{
	// Increasing the playerPlayedCount
	// To indicate this many player turns already played
	++playersPlayedCount;
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
	// Coordinate should be in range
	if (!(x < width && x > -1) && (y < height && height > -1))
		return false;
	Coordinate& coordinate = matrix[x][y];
	// Coordinate's owner and active player should be same
	return coordinate.getOwnerIndex() == activePlayerIndex || coordinate.isResetState();
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

bool Board::isInitialPlay() const
{
	return playersPlayedCount >= playersName.size();
}

bool Board::isGameFinished() const
{
	return playersName.size() == 1;
}

//Player Board::takePlayerDetailInput(int id)
//{
//	std::cout << "Please enter name for player " << id;
//	std::string name = "";
//	std::getline(std::cin, name);
//	/*Player player(id, name);
//	return player;*/
//	return Player(id, name);
//}

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