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
	matrix = std::vector<std::vector<std::shared_ptr<Coordinate>>>(height);
	for (int i = 0; i < height; i++)
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
	initBoard();
	initCoordinates();
	initPlayers();
}

void Board::initPlayers()
{
	int playersCount = 0;
	std::cout << "How many players = ";
	std::cin >> playersCount;

	players = std::vector<std::shared_ptr<Player>>(playersCount, nullptr);
	for (int i = 0; i < playersCount; ++i)
	{
		players[i] = takePlayerDetailInput(i);
	}
}

void Board::performOperations(std::queue<std::shared_ptr<Coordinate>>& queue)
{
	while (!queue.empty())
	{
		std::shared_ptr<Coordinate> coordinate = queue.front();
		queue.pop();

		std::shared_ptr<Player> activePlayer = players[activePlayerIndex];
		std::shared_ptr<Player> coordinateOwner = coordinate->getOwner();

		// Setting false the played property
		// Because player already played
		activePlayer->played();

		if (coordinate->isResetState())
		{
			coordinate->setOwner(activePlayer);
			activePlayer->increment();
		}
		else if (activePlayer != coordinateOwner)
		{
			coordinateOwner->decrement();
			coordinate->setOwner(activePlayer);
			if (coordinateOwner->getScore() <= Board::NO_SCORE && coordinateOwner->hasPlayed())
			{
				// Player lost
				// Removing from players
				players.erase(std::remove(players.begin(), players.end(), coordinateOwner), players.end());
				if (isGameOver())
				{
					printGameFinishedMessage();
					exit(0);
				}
			}
			activePlayer->increment();
		}

		coordinate->increment();
		if (coordinate->isThreshold())
		{
			std::vector<std::shared_ptr<Coordinate>> adjacentCoordinates = getAdjacentCoordinates(coordinate);
			coordinate->reset();

			for (std::shared_ptr<Coordinate> adjacentCoordinate : adjacentCoordinates)
			{
				queue.push(adjacentCoordinate);
			}
		}
	}
}

void Board::switchActivePlayer()
{
	if (activePlayerIndex < (players.size() - 1))
		++activePlayerIndex;
	else 
		activePlayerIndex = 0;
}

void Board::printGameFinishedMessage()
{
	std::cout << "Game finished.\nPlayer " << players.at(0)->getName() << " won\n";
}

void Board::insert(int x, int y)
{
	std::shared_ptr<Coordinate> coordinate = matrix[x][y];
	std::queue<std::shared_ptr<Coordinate>> queue;

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
	// Clearing the screen
	std::cout << "\033[2J\033[1;1H";

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

	// Printing player scores
	for (auto player : players)
	{
		std::cout << *player << std::endl;
	}
}

bool Board::isCoordinatesValid(int x, int y)
{
	// Coordinate should be in range
	if (!(x < width && x > -1) && (y < height && height > -1))
		return false;
	std::shared_ptr<Coordinate> coordinate = matrix[x][y];
	// Coordinate's owner and active player should be same
	// active player can only tap on their coordinate
	// Or No one has yet tapped the coordinate
	return coordinate->getOwner() == players[activePlayerIndex] || coordinate->isResetState();
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

bool Board::isGameOver() const
{
	return players.size() == 1;
}

std::shared_ptr<Player> Board::takePlayerDetailInput(int id	)
{
	std::cout << "Please enter name for player " << id << " : ";
	std::string name = "";
	int color = 37;

	std::cin >> std::ws;
	std::getline(std::cin, name);
	
	std::cout << "Please enter color code for player " << id << " : ";
	std::cin >> std::ws;
	std::cin >> color;

	return std::make_shared<Player>(id, name, color);
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