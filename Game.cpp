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
    while(!this->players.empty()) {
        Player *player = this->players.front();
        delete player;
        this->players.pop();
    }
}

void Game::clearScreen() {
    if (system("clear") ) {}
}

Player* Game::getCurrentPlayer() {
    return this->players.front();
}

// TODO: change the ugly algorithm
bool Game::checkLine(std::string& cell, int row, int column, int rowLimit, int columnLimit,
        int rowPlus, int columnPlus) {
    int size = 0;
    for ( ; row <= rowLimit && column <= columnLimit; column += columnPlus, row += rowPlus) {
        if (row >= this->board->getWidth() || row < 0 || column >= this->board->getHeight()
                || column < 0) continue;
        BoardCoords c{row, column};
        if (cell == this->board->getCell(c).getValue()) {
            size++;
            if (size == line) return true;
        } else {
            size = 0;
        }
    }
    return false;
}

void Game::run() {
    this->clearScreen();
    std::cout << "Game is running..." << std::endl;
    this->board->show();

    while (this->currentState == GameState::PLAYING) {
        BoardCoords move = this->playerMove();

        this->clearScreen();
        this->board->show();
        std::cout << std::endl;

        if (this->hasWon(move)) {
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
        if (!this->board->getCell(ret).isEmpty()) continue;

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
bool Game::hasWon(BoardCoords lastMove) {
    std::string cell = this->getCurrentPlayer()->getSeed();

    int lastRow = lastMove.row;
    int lastColumn = lastMove.column;
    const int line = this->line;
    int left = lastColumn - line + 1;
    int right = lastColumn + line - 1;
    int up = lastRow - line + 1;
    int down = lastRow + line - 1;

    // directions:
    // left down to right top
    if (this->checkLine(cell, down, left, down, right, -1, 1)) return true;
    // left to right
    if (this->checkLine(cell, lastRow, left, lastRow, right, 0, 1)) return true;
    // left top to right down
    if (this->checkLine(cell, up, left, down, right, 1, 1)) return true;
    // up to down
    if (this->checkLine(cell, up, lastColumn, down, lastColumn, 1, 0)) return true;

    return false;
}

void Game::switchPlayer() {
    Player* p = this->getCurrentPlayer();
    this->players.pop();
    this->players.push(p);
}
