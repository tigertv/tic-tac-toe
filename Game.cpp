#include "Game.h"
#include <iostream>
#include <limits>

Game::Game(int boardSize) {
    this->currentState = GameState::PLAYING;
    Player player1(BoardCell::CROSS);
    Player player2(BoardCell::ZERO);
    this->players.push(player1);
    this->players.push(player2);
    this->board = new Board(boardSize, boardSize);
}

Game::~Game() {
    delete this->board;
}

void Game::run() {
    std::cout << "Game is running..." << std::endl;
    this->board->show();

    while (this->currentState == GameState::PLAYING) {
        BoardCoords c = this->playerMove();
        this->board->show();

        std::cout << std::endl;

        if (this->hasWon(c.row, c.column)) {
            this->currentState = GameState::WIN;
        } else if (this->board->isFilled()) {
            this->currentState = GameState::DRAW;
        } else {
            this->switchPlayer();
        }

    }

    switch(this->currentState) {
    case GameState::WIN:
        if(this->players.front().getSeed() == BoardCell::CROSS) {
            std::cout << "'X'";
        } else {
            std::cout << "'O'";
        }
        std::cout << " wins!!!" << std::endl;
        break;

    case GameState::DRAW:
        std::cout << "Nobody wins!!!" << std::endl;
        break;

    default:
        break;
    }

    std::cout << "The game is over" << std::endl;
}

BoardCoords Game::playerMove() {
    bool wrongInput = true;
    int row = 0;
    int column = 0;

    while (wrongInput && !this->board->isFilled()) {
        if(this->players.front().getSeed() == BoardCell::CROSS) {
            std::cout << "'X'";
        } else {
            std::cout << "'O'";
        }
        std::cout << " is your turn. " << std::endl;

        do {
            std::cout << "Input the row[1-" << this->board->getHeight() << "]: ";
            std::cin >> row;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                continue;
            }
            row--;
        } while (row >= this->board->getHeight() || row < 0 );

        do {
            std::cout << "Input the column[1-"<< this->board->getWidth() << "]: ";
            std::cin >> column;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                continue;
            }
            column--;
        } while (column >= this->board->getWidth() || column < 0);

        if (this->board->getCell(row, column) != BoardCell::EMPTY) continue;

        int ret = this->board->setCell(row, column, this->players.front().getSeed());

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

    BoardCoords ret {row, column};
    return ret;
}

// checks only around the cell
bool Game::hasWon(int lastRow, int lastColumn) {
    BoardCell cell = this->players.front().getSeed();

    const int line = 3;
    int left = lastColumn - line + 1;
    int right = lastColumn + line - 1;
    int up = lastRow - line + 1;
    int down = lastRow + line - 1;

    int size = 0;

    // directions:
    // left down to right top
    for (int column = left, row = down; column <= right; column++, row--) {
        if (cell == this->board->getCell(row, column)) {
            size++;
            if (size == line) return true;
        } else {
            size = 0;
        }
    }

    size = 0;

    // left to right
    for (int column = left; column <= right; column++) {
        if (cell == this->board->getCell(lastRow, column)) {
            size++;
            if (size == line) return true;
        } else {
            size = 0;
        }
    }

    size = 0;

    // left top to right down
    for (int column = left, row = up; column <= right; column++, row++) {
        if (cell == this->board->getCell(row, column)) {
            size++;
            if (size == line) return true;
        } else {
            size = 0;
        }
    }

    size = 0;

    // up to down
    for (int row = up; row <= down; row++) {
        if (cell == this->board->getCell(row, lastColumn)) {
            size++;
            if (size == line) return true;
        } else {
            size = 0;
        }
    }

    return false;
}

void Game::switchPlayer() {
    Player p = this->players.front();
    this->players.pop();
    this->players.push(p);
}
