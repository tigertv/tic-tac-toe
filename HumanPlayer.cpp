#include "HumanPlayer.h"
#include <iostream>
#include <limits>

HumanPlayer::~HumanPlayer() {

}

HumanPlayer::HumanPlayer(std::string seed) {
    this->seed = seed;
}

BoardCoords HumanPlayer::move(Board *board) {
    BoardCoords coords;
    coords.row = this->getInput("Input the row[1-" + std::to_string(board->getHeight())
        + "]: ", board->getHeight());
    coords.column = this->getInput("Input the column[1-" + std::to_string(board->getWidth())
        + "]: ", board->getWidth());
    return coords;
}

int HumanPlayer::getInput(std::string message, int maxInput) {
    int ret = 0;

    do {
        std::cout << message;
        std::cin >> ret;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            continue;
        }
    } while (ret > maxInput || ret <= 0 );
    ret--;
    return ret;
}
