#ifndef HUMAN_PLAYER_H_
#define HUMAN_PLAYER_H_

#include <string>
#include "Player.h"
#include "Game.h"
//class Game;

class HumanPlayer : public Player {
private:
    int getInput(std::string message, int maxInput);
public:
    HumanPlayer(std::string seed);
    virtual ~HumanPlayer();

    GameMove askMove(const Game& game);
};

#endif
