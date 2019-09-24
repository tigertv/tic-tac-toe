#ifndef IPLAYER_H_
#define IPLAYER_H_

#include "BoardCell.h"
#include "Board.h"
#include <string>

class IPlayer {
protected:
    BoardCell seed;
public:
    virtual ~IPlayer() {};
    virtual BoardCell getSeed() = 0;
    virtual BoardCoords move(Board *board) = 0;
};

#endif
