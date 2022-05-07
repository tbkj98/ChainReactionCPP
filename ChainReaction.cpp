// ChainReaction.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <memory>
#include "include/Board.h"

int main()
{
	std::unique_ptr<Board> board = std::make_unique<Board>(5, 5);
	board->play();

	return 0;
}

