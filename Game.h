#ifndef GAME_H_
#define GAME_H_

#include "Board.h"
#include "Player.h"
#include <queue>

enum GameState {
    PLAYING, DRAW, WIN
};

class Game {
private:
    Board *board;
    GameState currentState;
    std::queue<Player> players;
    BoardCoords playerMove();
    bool hasWon(int lastRow, int lastColumn);
    void switchPlayer();
public:
    Game(int boardSize);
    virtual ~Game();
    void run();

};

#endif
