#ifndef PLAYER_H_
#define PLAYER_H_

#include "Board.h"
#include <string>

class Player {
protected:
    std::string seed;
public:
    virtual ~Player() {};
    std::string getSeed() {
        return this->seed;
    }
    virtual BoardCoords move(Board *board) = 0;
};

#endif
