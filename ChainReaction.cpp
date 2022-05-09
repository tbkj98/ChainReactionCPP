// ChainReaction.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <memory>
#include "include/Game.h"

int main()
{
	auto game = std::make_unique<Game>(5, 5);
	game->play();
	return 0;
}

