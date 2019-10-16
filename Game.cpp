#include "HumanPlayer.h"
#include "AiPlayer.h"
#include "Game.h"
#include <iostream>

Game::Game(int boardSize, int line) {
    this->currentState = GameState::PLAYING;

    this->players.push(new HumanPlayer("X"));
    this->players.push(new AiPlayer("O"));

    this->board = new Board(boardSize, boardSize);
    this->line = line;
}

Game::Game(const Game &game) {
    this->currentState = GameState::PLAYING;
    this->line = game.line;
    this->players = game.players;
    this->board = new Board(*(game.board));
}

Game::~Game() {
    delete this->board;
    /*
    while(!this->players.empty()) {
        Player *player = this->players.front();
        delete player;
        this->players.pop();
    }
    //*/
}

void Game::clearScreen() {
    //if (system("clear") ) {}
}

Player* Game::getCurrentPlayer() {
    return this->players.front();
}

// TODO: change the ugly algorithm
bool Game::checkLine(BoardCell& cell, int row, int column, int rowLimit, int columnLimit,
        int rowPlus, int columnPlus) {
    int size = 0;
    for ( ; row <= rowLimit && column <= columnLimit; column += columnPlus, row += rowPlus) {
        if (row >= this->board->getWidth() || row < 0 || column >= this->board->getHeight()
                || column < 0) continue;

        BoardCoords c{row, column};
        if (&cell == &(this->board->getCell(c))) {
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
            std::cout << "'" << this->getCurrentPlayer()->getSeed().getValue()
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
    BoardCoords coords;

    while (wrongInput && !this->board->isFilled()) {
        Player* currentPlayer = this->getCurrentPlayer();
        std::cout << "'" << currentPlayer->getSeed().getValue()
                << "' is your turn. " << std::endl;

        coords = currentPlayer->askMove(*this).getCoords();
        if (!this->board->getCell(coords).isEmpty()) continue;

        try {
            this->board->setCell(coords, currentPlayer->getSeed());
            wrongInput = false;
        } catch (std::out_of_range& e) {
            std::cout << e.what() << std::endl;
            wrongInput = true;
        }
    }

    return coords;
}

// checks only around the cell
bool Game::hasWon(BoardCoords lastMove) {
    BoardCell& cell = this->getCurrentPlayer()->getSeed();

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

std::vector<GameMove> Game::getPossibleMoves() {
    std::vector<GameMove> ret;
    std::vector<BoardCoords> coords = this->board->getEmptyCells();
    for(BoardCoords& item : coords) {
        GameMove move(item);
        ret.push_back(move);
    }
    return ret;
}

Board* Game::getBoard() {
    return this->board;
}
