#include "Game.h"
#include <iostream>
#include <limits>

Game::Game(int boardSize, int line) {
    this->currentState = GameState::PLAYING;
    Player player1("X");
    Player player2("O");
    this->players.push(player1);
    this->players.push(player2);
    this->board = new Board(boardSize, boardSize);
    this->line = line;
}

Game::~Game() {
    delete this->board;
}

int Game::getInput(std::string message, int maxInput) {
    int ret = 0;

    do {
        std::cout << message;
        std::cin >> ret;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            continue;
        }
        ret--;
    } while (ret >= maxInput || ret <= 0 );

    return ret;
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
        std::cout << "'" << this->players.front().getSeed().getValue()
                    << "' wins!!!" << std::endl;
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
        std::cout << "'" << this->players.front().getSeed().getValue()
                << "' is your turn. " << std::endl;

        row = this->getInput("Input the row[1-" + std::to_string(this->board->getHeight())
            + "]: ", this->board->getHeight());
        column = this->getInput("Input the column[1-" + std::to_string(this->board->getWidth())
            + "]: ", this->board->getWidth());

        if (this->board->getCell(row, column).getValue() != " ") continue;

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
    Player p = this->players.front();
    this->players.pop();
    this->players.push(p);
}
