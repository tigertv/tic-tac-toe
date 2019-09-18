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
    Board board = Board(5, 5);
    GameState currentState;
    std::queue<Player> players;
    BoardCoords playerMove();
    bool hasWon(int lastRow, int lastColumn);
    void switchPlayer();
public:
    Game();
    virtual ~Game();
    void run();

};

#endif
