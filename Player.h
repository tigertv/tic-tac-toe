#ifndef PLAYER_H_
#define PLAYER_H_

#include "Board.h"

class Player {
private:
    BoardCell seed;
public:
    Player(BoardCell seed);
    virtual ~Player();

    BoardCell getSeed();
};

#endif
