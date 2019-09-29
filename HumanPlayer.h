#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H

#include <string>
#include "Player.h"

class HumanPlayer : public Player {
private:
    int getInput(std::string message, int maxInput);
public:
    HumanPlayer(std::string seed);
    virtual ~HumanPlayer();

    BoardCoords move(Board *board);
};

#endif
