#ifndef GAMEMOVE_H_
#define GAMEMOVE_H_

#include "Board.h"

class GameMove {
private:
    BoardCoords coords;
public:
    GameMove(BoardCoords coords);
    virtual ~GameMove();
    BoardCoords getCoords();
};

#endif
