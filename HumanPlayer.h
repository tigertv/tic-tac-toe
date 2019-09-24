#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H

#include "BoardCell.h"
#include "IPlayer.h"
#include <string>

class HumanPlayer : public IPlayer {
private:
    int getInput(std::string message, int maxInput);
public:
    HumanPlayer(BoardCell seed);
    HumanPlayer(std::string seed);
    virtual ~HumanPlayer();

    BoardCell getSeed();
    BoardCoords move(Board *board);
};

#endif
