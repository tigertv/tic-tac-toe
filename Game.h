#ifndef GAME_H_
#define GAME_H_

#include "Board.h"
#include <queue>
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

public:
    Game(int boardSize, int line);
    virtual ~Game();
    void run();
};

#endif
