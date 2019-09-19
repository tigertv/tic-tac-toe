#ifndef PLAYER_H_
#define PLAYER_H_

#include "Board.h"
#include <string>

class Player {
private:
    BoardCell seed;
public:
    Player(BoardCell seed);
    Player(std::string seed);
    virtual ~Player();

    BoardCell getSeed();
};

#endif
