#ifndef GAME_H_
#define GAME_H_

#include "GameMove.h"
#include "Player.h"
#include "Board.h"
#include <queue>
#include <string>

enum GameState {
    PLAYING, DRAW, WIN
};

class Player;

struct PlayerNode {
    PlayerNode* next;
    Player* player;

    PlayerNode(Player* player) {
        this->player = player;
        this->next = nullptr;
    }
};

class Game {
private:
    Board *board;
    GameState currentState;
    int line;
    PlayerNode* players;
    GameMove playerMove();
    void clearScreen();
    bool checkLine(BoardCell& cell, int row, int column, int rowLimit, int columnLimit,
            int rowPlus, int columnPlus);
    bool checkLine(GameMove& move, int dRow, int dColumn);

public:
    Game(int boardSize, int line);
    Game(const Game& game);
    virtual ~Game();

    void run();
    void switchPlayer();
    std::vector<GameMove> getPossibleMoves();
    Board* getBoard();
    Player* getCurrentPlayer();
    bool makeMove(GameMove& move);
    bool unmakeMove(GameMove& move);
    bool hasWon(GameMove& lastMove);

};

#endif
