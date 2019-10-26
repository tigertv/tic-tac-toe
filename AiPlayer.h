#ifndef AI_PLAYER_H
#define AI_PLAYER_H

#include <string>
#include "Player.h"
#include "Game.h"

class AiPlayer : public Player {
private:
    int negamax(Game& game, int depth, int alpha, int beta);
    int evaluate(Game& game);
public:
    AiPlayer(std::string seed);
    virtual ~AiPlayer();

    GameMove askMove(const Game& game);

};

#endif
