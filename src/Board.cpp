#include "../include/Board.h"
#include <iostream>
#include <queue>


void Board::initMatrix()
{
	matrix = std::vector<std::vector<std::shared_ptr<Coordinate>>>(height);
	for (size_t i = 0; i < height; i++)
	{
		matrix[i] = std::vector<std::shared_ptr<Coordinate>>(width, nullptr);
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
				matrix[i][j] = std::make_shared<Coordinate>(i, j, 2);
			}
			// Edge coordinate
			else if (i == 0 || j == 0 || i == height - 1 || j == width - 1)
			{
				matrix[i][j] = std::make_shared<Coordinate>(i, j, 3);
			}
			// Middle coordinate
			else
			{
				matrix[i][j] = std::make_shared<Coordinate>(i, j, 4);
			}
		}
	}
}

void Board::init()
{
	initMatrix();
	initCoordinates();
}

std::vector<std::shared_ptr<Player>> Board::performOperations(std::queue<std::shared_ptr<Coordinate>>& queue, std::shared_ptr<Player> activePlayer)
{
	auto lostPlayers = std::vector<std::shared_ptr<Player>>(0, nullptr);
	while (!queue.empty())
	{
		std::shared_ptr<Coordinate> coordinate = queue.front();
		queue.pop();

		// Current coordinate owner
		std::shared_ptr<Player> coordinateOwner = coordinate->getOwner();

		// Player already played
		// This is helpful to find the lost player
		activePlayer->played();

		// If the player is in reset state
		// We need to change the owner to activePlayer
		// And increment the score of activePlayer
		if (coordinate->isResetState())
		{
			coordinate->setOwner(activePlayer);
			activePlayer->increment();
		}
		// We need to decrement the score of current coordinate owner
		// Because the coordinate lost the ownership, coordinate now belongs to activePlayer
		// If the coordinateOwner has played before and is now on NO_SCORE
		// We need to eliminate the player(coordinateOwner)
		else if (activePlayer != coordinateOwner)
		{
			coordinateOwner->decrement();
			coordinate->setOwner(activePlayer);
			if (coordinateOwner->isNoScore() && coordinateOwner->hasPlayed())
			{
				// Player lost
				// Adding to lostPlayers list
				lostPlayers.push_back(coordinateOwner);
			}
			activePlayer->increment();
		}

		// Incrementing the coordinate value
		coordinate->increment();

		// Checking if the coordinate has reached the threshold
		// If yes, need to explode the coordinate in available adjacent directions
		if (coordinate->isThreshold())
		{
			std::vector<std::shared_ptr<Coordinate>> adjacentCoordinates = getAdjacentCoordinates(coordinate);
			
			// Resetting the coordinate
			// Coordinate has exploded
			coordinate->reset();

			// Inserting the adjacent coordinates into queue
			// Need to treat the adjacent coordinates 
			// As the user insertions(user tap)
			for (std::shared_ptr<Coordinate> adjacentCoordinate : adjacentCoordinates)
			{
				queue.push(adjacentCoordinate);
			}
		}
	}

	return lostPlayers;
}


std::vector<std::shared_ptr<Player>> Board::insert(int x, int y, std::shared_ptr<Player> activePlayer)
{
	std::shared_ptr<Coordinate> coordinate = matrix[x][y];
	std::queue<std::shared_ptr<Coordinate>> queue;

	queue.push(coordinate);
	return performOperations(queue, activePlayer);
}

Board::Board(int width, int height)
{
	this->width = width;
	this->height = height;

	init();
}

void Board::print() const
{
	// Printing board
	for (int x = 0; x < height; x++)
	{
		for (int y = 0; y < width; y++)
		{
			std::shared_ptr<Coordinate> coordinate = matrix[x][y];
			std::cout << *coordinate << " ";
		}

		std::cout << "\n";
	}
}

bool Board::isCoordinatesValid(int x, int y, std::shared_ptr<Player> activePlayer)
{
	// Coordinate should be in range
	if (!(x < width && x > -1) && (y < height && height > -1))
		return false;
	std::shared_ptr<Coordinate> coordinate = matrix[x][y];
	// Coordinate's owner and active player should be same
	// active player can only tap on their coordinate
	// Or No one has yet tapped the coordinate
	return coordinate->getOwner() == activePlayer || coordinate->isResetState();
}

std::vector<std::shared_ptr<Coordinate>> Board::getAdjacentCoordinates(std::shared_ptr<Coordinate> coordinate) const
{
	std::vector<std::shared_ptr<Coordinate>> list;

	if (isDownwardSpaceAvailable(coordinate)) {
		list.push_back(getDownwardCoordinate(coordinate));
	}

	if (isUpwardSpaceAvailable(coordinate)) {
		list.push_back(getUpwardCoordinate(coordinate));
	}

	if (isLeftwardSpaceAvailable(coordinate)) {
		list.push_back(getLeftwardCoordinate(coordinate));
	}

	if (isRightwardSpaceAvailable(coordinate)) {
		list.push_back(getRightwardCoordinate(coordinate));
	}

	return list;
}

bool Board::isUpwardSpaceAvailable(std::shared_ptr<Coordinate> coordinate) const
{
	return coordinate->getY() > 0;
}

bool Board::isDownwardSpaceAvailable(std::shared_ptr<Coordinate> coordinate) const
{
	return coordinate->getY() < height - 1;
}

bool Board::isLeftwardSpaceAvailable(std::shared_ptr<Coordinate> coordinate) const
{
	return coordinate->getX() > 0;
}

bool Board::isRightwardSpaceAvailable(std::shared_ptr<Coordinate> coordinate) const
{
	return coordinate->getX() < width - 1;
}

std::shared_ptr<Coordinate> Board::getRightwardCoordinate(std::shared_ptr<Coordinate> coordinate) const
{
	return matrix[coordinate->getX() + 1][coordinate->getY()];
}

std::shared_ptr<Coordinate> Board::getLeftwardCoordinate(std::shared_ptr<Coordinate> coordinate) const
{
	return matrix[coordinate->getX() - 1][coordinate->getY()];
}

std::shared_ptr<Coordinate> Board::getUpwardCoordinate(std::shared_ptr<Coordinate> coordinate) const
{
	return matrix[coordinate->getX()][coordinate->getY() - 1];
}

std::shared_ptr<Coordinate> Board::getDownwardCoordinate(std::shared_ptr<Coordinate> coordinate) const
{
	return matrix[coordinate->getX()][coordinate->getY() + 1];
}