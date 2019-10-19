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
        GameMove move = this->playerMove();

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

GameMove Game::playerMove() {
    bool wrongInput = true;
    BoardCoords coords;
    GameMove move(coords);
    while (wrongInput && !this->board->isFilled()) {
        Player* currentPlayer = this->getCurrentPlayer();
        std::cout << "'" << currentPlayer->getSeed().getValue()
                << "' is your turn. " << std::endl;

        move = currentPlayer->askMove(*this);
        if (this->makeMove(move)) {
            wrongInput = false;
        } else {
            wrongInput = true;
        }
    }
    return move;
}

bool Game::checkLine(GameMove &move, int dRow, int dColumn) {
    int size = 1;
    BoardCell& cell = this->getCurrentPlayer()->getSeed();
    BoardCoords coords = move.getCoords();
    int row = coords.row + dRow;
    int column = coords.column + dColumn;
    int columnLimit = coords.column + this->line * dColumn;
    int rowLimit = coords.row + this->line * dRow;

    for (; row < rowLimit && column < columnLimit; column += dColumn, row += dRow) {
        BoardCoords c{row, column};
        if (&cell == &(this->board->getCell(c))) {
            size++;
        } else {
            break;
        }
    }

    rowLimit = coords.row - this->line * dRow;
    columnLimit = coords.column - this->line * dColumn;
    row = coords.row - dRow;
    column = coords.column - dColumn;
    for (; row > rowLimit && column > columnLimit; column -= dColumn, row -= dRow) {
        BoardCoords c{row, column};
        if (&cell == &(this->board->getCell(c))) {
            size++;
        } else {
            break;
        }
    }

    if (size >= this->line) return true;
    return false;

    /*
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
    //*/
    return false;
}

// checks only around the cell
bool Game::hasWon(GameMove& lastMove) {
    BoardCell& cell = this->getCurrentPlayer()->getSeed();
    BoardCoords coords = lastMove.getCoords();
    int lastRow = coords.row;
    int lastColumn = coords.column;
    const int line = this->line;
    int left = lastColumn - line + 1;
    int right = lastColumn + line - 1;
    int up = lastRow - line + 1;
    int down = lastRow + line - 1;

    // directions:
    // left down to right top
    return (this->checkLine(cell, down, left, down, right, -1, 1)) ||
    //        return (this->checkLine(lastMove, -1, 1)) ||
                    // left to right
        (this->checkLine(cell, lastRow, left, lastRow, right, 0, 1)) ||
        // left top to right down
        (this->checkLine(cell, up, left, down, right, 1, 1)) ||
        // up to down
        (this->checkLine(cell, up, lastColumn, down, lastColumn, 1, 0));
}

void Game::switchPlayer() {
    Player* p = this->getCurrentPlayer();
    this->players.pop();
    this->players.push(p);
}

std::vector<GameMove> Game::getPossibleMoves() {
    std::vector<GameMove> moves;
    std::vector<BoardCoords> coords = this->board->getEmptyCells();
    for(BoardCoords& item : coords) {
        GameMove move(item);
        moves.push_back(move);
    }
    return moves;
}

Board* Game::getBoard() {
    return this->board;
}

bool Game::makeMove(GameMove &move) {
    BoardCoords coords = move.getCoords();
    if (!this->board->getCell(coords).isEmpty()) return false;

    try {
        this->board->setCell(coords, this->getCurrentPlayer()->getSeed());
        return true;
    } catch (std::out_of_range& e) {
        std::cout << e.what() << std::endl;
        return false;
    }
}

bool Game::unmakeMove(GameMove &move) {
    BoardCoords coords = move.getCoords();
    try {
        this->board->clearCell(coords);
        return true;
    } catch (std::out_of_range& e) {
        std::cout << e.what() << std::endl;
        return false;
    }
    return true;
}
