#ifndef AI_PLAYER_H
#define AI_PLAYER_H

#include "BoardCell.h"
#include "IPlayer.h"
#include <string>

class AiPlayer : public IPlayer {
private:

public:
    AiPlayer(BoardCell seed);
    AiPlayer(std::string seed);
    virtual ~AiPlayer();

    BoardCell getSeed();
    BoardCoords move(Board *board);
};

#endif
