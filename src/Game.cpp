#include <iostream>

#include "..\include\Game.h"
#include "..\include\Board.h"

void Game::play()
{
	print();

	int x, y;
	char inputToBeTaken = 'y';

	do
	{
		std::cout << "Enter coordinates\n";
		std::cin >> x >> y;

		auto activePlayer = players[activePlayerIndex];
		
		if (board->isCoordinatesValid(x, y, activePlayer))
		{
			auto lostPlayers = board->insert(x, y, activePlayer);
			if (!lostPlayers.empty())
			{
				removeLostPlayers(lostPlayers);
			}
			print();
			if (isGameOver())
			{
				printGameFinishedMessage();
				return;
			}
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

void Game::initBoard(size_t width, size_t height)
{
	board = std::make_shared<Board>(width, height);
}

void Game::initPlayers()
{
	size_t playersCount = takePlayerCountInput();
	
	players = std::vector<std::shared_ptr<Player>>(playersCount, nullptr);
	for (size_t i = 0; i < playersCount; ++i)
	{
		players[i] = takePlayerDetailInput(i);
	}
}

size_t Game::takePlayerCountInput()
{
	size_t playersCount = 0;
	while (true)
	{
		std::cout << "How many players = ";
		std::cin >> playersCount;

		if ((playersCount >= Game::MINIMUM_PLAYERS_COUNT && playersCount <= Game::MAXIMUM_PLAYERS_COUNT))
			break;

		std::cout << "Invalid Players count" << std::endl;
		std::cout << "Players count must be in range ("
				  << Game::MINIMUM_PLAYERS_COUNT 
				  << ", " 
				  << Game::MAXIMUM_PLAYERS_COUNT << ")" 
				  << std::endl;
	}

	return playersCount;
}


void Game::switchActivePlayer()
{
	if (activePlayerIndex < (players.size() - 1))
		++activePlayerIndex;
	else
		activePlayerIndex = 0;
}

void Game::printGameFinishedMessage()
{
	std::cout << "Game finished.\nPlayer " << players.at(0)->getName() << " won\n";
}

Game::Game()
{
	initBoard(Game::BOARD_WIDTH, Game::BOARD_HEIGHT);
	initPlayers();
}

Game::Game(size_t width, size_t height)
{
	initBoard(width, height);
	initPlayers();
}

void Game::print() const
{
	// Clearing the screen
	std::cout << "\033[2J\033[1;1H";

	board->print();

	// Printing player scores
	for (auto player : players)
	{
		std::cout << *player << std::endl;
	}
}

bool Game::isGameOver() const
{
	// If there is only one player in players vector
	// Other players have lost
	return players.size() == 1;
}

std::shared_ptr<Player> Game::takePlayerDetailInput(int id)
{
	std::string name = "";
	std::cout << "Please enter name for player " << id << " : ";
	std::cin >> std::ws;
	std::getline(std::cin, name);

	Color color = takePlayerColorInput(id);
	return std::make_shared<Player>(id, name, color);
}

Color Game::takePlayerColorInput(int id)
{
	size_t i = 0;
	while (true)
	{
		for (i = 0; i < colors.size(); i++)
		{
			Color color = colors[i];
			std::cout << i << ". " << color << std::endl;
		}
		std::cout << "Please select the color" << std::endl;
		std::cin >> std::ws;
		std::cin >> i;

		if (i >= 0 && i < colors.size())
			break;

	}
	return colors[i];
}

void Game::removeLostPlayers(std::vector<std::shared_ptr<Player>> lostPlayers)
{
	auto pred = [&](const std::shared_ptr<Player> key)->bool
	{
		return std::find(lostPlayers.begin(), lostPlayers.end(), key) != lostPlayers.end();
	};

	// Removing lost players from players vector
	players.erase(std::remove_if(players.begin(), players.end(), pred), players.end());
}