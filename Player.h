#ifndef PLAYER_H_
#define PLAYER_H_

#include "Board.h"
#include "GameMove.h"
#include "Game.h"
#include <string>

class Game;

class Player {
protected:
    BoardCell seed;
public:
    virtual ~Player() {};
    BoardCell& getSeed();
    virtual GameMove askMove(const Game& game) = 0;
};

#endif
