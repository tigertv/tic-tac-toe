#ifndef AI_PLAYER_H
#define AI_PLAYER_H

#include <string>
#include "Player.h"
#include "Game.h"

class AiPlayer : public Player {
private:
    int minimax(Game& game);
public:
    AiPlayer(std::string seed);
    virtual ~AiPlayer();

    GameMove askMove(const Game& game);

};

#endif
