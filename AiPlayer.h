#ifndef AI_PLAYER_H
#define AI_PLAYER_H

#include <string>
#include "Player.h"

class AiPlayer : public Player {
private:

public:
    AiPlayer(std::string seed);
    virtual ~AiPlayer();

    BoardCoords move(Board *board);
};

#endif
