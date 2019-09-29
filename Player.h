#ifndef PLAYER_H_
#define PLAYER_H_

#include "Board.h"
#include <string>

class Player {
protected:
    BoardCell seed;
public:
    virtual ~Player() {};
    BoardCell& getSeed() {
        return this->seed;
    }
    virtual BoardCoords move(Board *board) = 0;
};

#endif
