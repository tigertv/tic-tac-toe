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

class Game {
private:
    Board *board;
    GameState currentState;
    int line;
    std::queue<Player*> players;
    BoardCoords playerMove();
    bool hasWon(BoardCoords lastMove);
    void clearScreen();
    Player* getCurrentPlayer();
    bool checkLine(BoardCell& cell, int row, int column, int rowLimit, int columnLimit,
            int rowPlus, int columnPlus);

public:
    Game(int boardSize, int line);
    Game(const Game& game);
    virtual ~Game();
    void run();
    void switchPlayer();
    std::vector<GameMove> getPossibleMoves();
    Board* getBoard();
};

#endif
