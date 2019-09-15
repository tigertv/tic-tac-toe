#include "Game.h"
#include <iostream>
#include <limits>

Game::Game() {
	this->currentState = GameState::PLAYING;
	this->currentPlayer = Player::PLAYER_CROSS;
}

Game::~Game() {

}

void Game::run() {
	std::cout << "Game is running..." << std::endl;
	this->board.show();

	while (this->currentState == GameState::PLAYING) {
		this->playerStep();
		this->board.show();

		std::cout << std::endl;

		if (this->hasWon()) {
			switch (this->currentPlayer) {
			case Player::PLAYER_CROSS:
				this->currentState = GameState::CROSS_WON;
				break;

			case Player::PLAYER_ZERO:
				this->currentState = GameState::ZERO_WON;
				break;

			default:
				// there is no such player
				break;
			}
		} else if (this->board.isFilled()) {
			this->currentState = GameState::DRAW;
		} else {
			this->switchPlayer();
		}

	}

	switch(this->currentState) {
	case GameState::ZERO_WON:
		std::cout << "'O' wins!!!" << std::endl;
		break;

	case GameState::CROSS_WON:
		std::cout << "'X' wins!!!" << std::endl;
		break;

	case GameState::DRAW:
		std::cout << "Nobody wins!!!" << std::endl;
		break;

	default:

		break;
	}

	std::cout << "The game is over" << std::endl;

}

void Game::playerStep() {
	bool wrongInput = true;
	int row = 0;
	int column = 0;

	while (wrongInput && !this->board.isFilled()) {
		if (this->currentPlayer == Player::PLAYER_CROSS) {
			std::cout << "'X'";
		} else {
			std::cout << "'O'";
		}
		std::cout << " is your turn. " << std::endl;

		std::cout << "Input the row[1-3]: ";
		std::cin >> row;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
			continue;
		}
		row--;
		if (row > 2 || row < 0 ) continue;

		std::cout << "Input the column[1-3]: ";
		std::cin >> column;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
			continue;
		}
		column--;
		if (column > 2 || column < 0) continue;

		if (this->board.getCell(row, column) != BoardCell::EMPTY) continue;

		int ret;
		if (this->currentPlayer == Player::PLAYER_CROSS) {
			ret = this->board.setCell(row, column, BoardCell::CROSS);
		} else {
			ret = this->board.setCell(row, column, BoardCell::ZERO);
		}

		switch(ret) {
		case 1:
			wrongInput = true;
			break;

		case 2:
			this->currentState = GameState::DRAW;
			wrongInput = false;
			break;

		default:
			wrongInput = false;
			break;
		}

	}
}

bool Game::hasWon() {
	BoardCell cell;
	if (this->currentPlayer == Player::PLAYER_CROSS) {
		cell = BoardCell::CROSS;
	} else {
		cell = BoardCell::ZERO;
	}

	if ( (this->board.getCell(0, 0) == cell && this->board.getCell(1, 0) == cell && this->board.getCell(2, 0) == cell)
		|| (this->board.getCell(0, 1) == cell && this->board.getCell(1, 1) == cell && this->board.getCell(2, 1) == cell)
		|| (this->board.getCell(0, 2) == cell && this->board.getCell(1, 2) == cell && this->board.getCell(2, 2) == cell)
		|| (this->board.getCell(0, 0) == cell && this->board.getCell(0, 1) == cell && this->board.getCell(0, 2) == cell)
		|| (this->board.getCell(1, 0) == cell && this->board.getCell(1, 1) == cell && this->board.getCell(1, 2) == cell)
		|| (this->board.getCell(2, 0) == cell && this->board.getCell(2, 1) == cell && this->board.getCell(2, 2) == cell)
		|| (this->board.getCell(0, 0) == cell && this->board.getCell(1, 1) == cell && this->board.getCell(2, 2) == cell)
		|| (this->board.getCell(2, 0) == cell && this->board.getCell(1, 1) == cell && this->board.getCell(0, 2) == cell)
	) {
		return true;
	}
	return false;
}

void Game::switchPlayer() {
	if (this->currentPlayer == Player::PLAYER_CROSS) {
		this->currentPlayer = Player::PLAYER_ZERO;
	} else {
		this->currentPlayer = Player::PLAYER_CROSS;
	}
}
