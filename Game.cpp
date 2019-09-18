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
        BoardCoords c = this->playerMove();
        this->board.show();

        std::cout << std::endl;

        if (this->hasWon(c.row, c.column)) {
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

BoardCoords Game::playerMove() {
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

        std::cout << "Input the row[1-" << this->board.getHeight() << "]: ";
        std::cin >> row;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            continue;
        }
        row--;
        if (row >= this->board.getHeight() || row < 0 ) continue;

        std::cout << "Input the column[1-"<< this->board.getWidth() << "]: ";
        std::cin >> column;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            continue;
        }
        column--;
        if (column >= this->board.getWidth() || column < 0) continue;

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

    BoardCoords ret {row, column};
    return ret;
}

// checks only around the cell
bool Game::hasWon(int lastRow, int lastColumn) {
    BoardCell cell;
    if (this->currentPlayer == Player::PLAYER_CROSS) {
        cell = BoardCell::CROSS;
    } else {
        cell = BoardCell::ZERO;
    }

    const int line = 3;
    int left = lastColumn - line + 1;
    int right = lastColumn + line - 1;
    int up = lastRow - line + 1;
    int down = lastRow + line - 1;

    int size = 0;

    // directions:
    // left down to right top
    for (int column = left, row = down; column <= right; column++, row--) {
        if (cell == this->board.getCell(row, column)) {
            size++;
            if (size == line) return true;
        } else {
            size = 0;
        }
    }

    size = 0;

    // left to right
    for (int column = left; column <= right; column++) {
        if (cell == this->board.getCell(lastRow, column)) {
            size++;
            if (size == line) return true;
        } else {
            size = 0;
        }
    }

    size = 0;

    // left top to right down
    for (int column = left, row = up; column <= right; column++, row++) {
        if (cell == this->board.getCell(row, column)) {
            size++;
            if (size == line) return true;
        } else {
            size = 0;
        }
    }

    size = 0;

    // up to down
    for (int row = up; row <= down; row++) {
        if (cell == this->board.getCell(row, lastColumn)) {
            size++;
            if (size == line) return true;
        } else {
            size = 0;
        }
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
