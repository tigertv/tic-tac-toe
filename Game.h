#ifndef GAME_H_
#define GAME_H_

#include "Board.h"

enum GameState {
    PLAYING, DRAW, CROSS_WON, ZERO_WON
};

enum Player {
    PLAYER_CROSS, PLAYER_ZERO
};

class Game {
private:
    Board board = Board(5, 5);
    GameState currentState;
    Player currentPlayer;
    BoardCoords playerMove();
    bool hasWon(int lastRow, int lastColumn);
    void switchPlayer();
public:
    Game();
    virtual ~Game();
    void run();

};

#endif
