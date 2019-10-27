#include "HumanPlayer.h"
#include "AiPlayer.h"
#include "Game.h"
#include <iostream>

Game::Game(int boardSize, int line) {
    this->currentState = GameState::PLAYING;

    PlayerNode* node = new PlayerNode(new HumanPlayer("X"));
    PlayerNode* node2 = new PlayerNode(new AiPlayer("O"));

    node->next = node2;
    node2->next = node;
    this->players = node;

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
}

void Game::clearScreen() {
    //if (system("clear") ) {}
}

Player* Game::getCurrentPlayer() {
    return this->players->player;
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
    int row = coords.row;
    int column = coords.column;

    for (int i = 1; i < this->line; i++) {
        row += dRow;
        column += dColumn;
        BoardCoords c{row, column};
        try {
            if (&cell == &(this->board->getCell(c))) {
                size++;
            } else {
                break;
            }
        } catch(...) {
            break;
        }

    }

    row = coords.row;
    column = coords.column;

    for (int i = 1; i < this->line; i++) {
        row -= dRow;
        column -= dColumn;
        BoardCoords c{row, column};
        try {
            if (&cell == &(this->board->getCell(c))) {
                size++;
            } else {
                break;
            }
        } catch(...) {
            break;
        }
    }

    return (size >= this->line);
}

// checks only around the cell
bool Game::hasWon(GameMove& lastMove) {
    // directions:
    return (
        // left down to right top
        this->checkLine(lastMove, -1, 1) ||
        // left to right
        this->checkLine(lastMove, 0, 1) ||
        // left top to right down
        this->checkLine(lastMove, 1, 1) ||
        // up to down
        this->checkLine(lastMove, 1, 0)
    );
}

void Game::switchPlayer() {
    this->players = this->players->next;
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
