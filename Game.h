#ifndef GAME_H_
#define GAME_H_

#include "Board.h"
#include "IPlayer.h"
#include <queue>

enum GameState {
    PLAYING, DRAW, WIN
};

class Game {
private:
    Board *board;
    GameState currentState;
    int line;
    std::queue<IPlayer*> players;
    BoardCoords playerMove();
    bool hasWon(int lastRow, int lastColumn);
    void switchPlayer();
    void clearScreen();

public:
    Game(int boardSize, int line);
    virtual ~Game();
    void run();
};

#endif
