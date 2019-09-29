#ifndef GAME_H_
#define GAME_H_

#include "Board.h"
#include <queue>
#include <string>
#include "Player.h"

enum GameState {
    PLAYING, DRAW, WIN
};

class Game {
private:
    Board *board;
    GameState currentState;
    int line;
    std::queue<Player*> players;
    BoardCoords playerMove();
    bool hasWon(BoardCoords lastMove);
    void switchPlayer();
    void clearScreen();
    Player* getCurrentPlayer();
    bool checkLine(std::string& cell, int row, int column, int rowLimit, int columnLimit,
            int rowPlus, int columnPlus);

public:
    Game(int boardSize, int line);
    virtual ~Game();
    void run();
};

#endif
