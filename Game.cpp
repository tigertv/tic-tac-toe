#include "Game.h"
#include "HumanPlayer.h"
#include "AiPlayer.h"
#include <iostream>

Game::Game(int boardSize, int line) {
    this->currentState = GameState::PLAYING;

    Player *player;

    player = new HumanPlayer("X");
    this->players.push(player);
    player = new AiPlayer("O");
    this->players.push(player);

    this->board = new Board(boardSize, boardSize);
    this->line = line;
}

Game::~Game() {
    delete this->board;
}

void Game::clearScreen() {
    if (system("clear") ) {}
}

Player* Game::getCurrentPlayer() {
    return this->players.front();
}

void Game::run() {
    this->clearScreen();
    std::cout << "Game is running..." << std::endl;
    this->board->show();

    while (this->currentState == GameState::PLAYING) {
        BoardCoords c = this->playerMove();

        this->clearScreen();
        this->board->show();
        std::cout << std::endl;

        if (this->hasWon(c.row, c.column)) {
            this->currentState = GameState::WIN;
            std::cout << "'" << this->getCurrentPlayer()->getSeed()
                    << "' wins!!!" << std::endl;
        } else if (this->board->isFilled()) {
            this->currentState = GameState::DRAW;
            std::cout << "Nobody wins!!!" << std::endl;
        } else {
            this->switchPlayer();
        }

    }

    std::cout << "The game is over" << std::endl;
}

BoardCoords Game::playerMove() {
    bool wrongInput = true;
    BoardCoords ret;

    while (wrongInput && !this->board->isFilled()) {
        Player* currentPlayer = this->getCurrentPlayer();
        std::cout << "'" << currentPlayer->getSeed()
                << "' is your turn. " << std::endl;

        ret = currentPlayer->move(this->board);
        if (!this->board->isEmptyCell(ret)) continue;

        try {
            this->board->setCell(ret, currentPlayer->getSeed());
            wrongInput = false;
        } catch (std::out_of_range& e) {
            std::cout << e.what() << std::endl;
            wrongInput = true;
        }
    }

    return ret;
}

// checks only around the cell
bool Game::hasWon(int lastRow, int lastColumn) {
    BoardCell cell = this->getCurrentPlayer()->getSeed();

    const int line = this->line;
    int left = lastColumn - line + 1;
    int right = lastColumn + line - 1;
    int up = lastRow - line + 1;
    int down = lastRow + line - 1;

    int size = 0;

    // directions:
    // left down to right top
    for (int column = left, row = down; column <= right; column++, row--) {
        if (cell.getValue() == this->board->getCell(row, column).getValue()) {
            size++;
            if (size == line) return true;
        } else {
            size = 0;
        }
    }

    size = 0;

    // left to right
    for (int column = left; column <= right; column++) {
        if (cell.getValue() == this->board->getCell(lastRow, column).getValue()) {
            size++;
            if (size == line) return true;
        } else {
            size = 0;
        }
    }

    size = 0;

    // left top to right down
    for (int column = left, row = up; column <= right; column++, row++) {
        if (cell.getValue() == this->board->getCell(row, column).getValue()) {
            size++;
            if (size == line) return true;
        } else {
            size = 0;
        }
    }

    size = 0;

    // up to down
    for (int row = up; row <= down; row++) {
        if (cell.getValue() == this->board->getCell(row, lastColumn).getValue()) {
            size++;
            if (size == line) return true;
        } else {
            size = 0;
        }
    }

    return false;
}

void Game::switchPlayer() {
    Player* p = this->getCurrentPlayer();
    this->players.pop();
    this->players.push(p);
}
