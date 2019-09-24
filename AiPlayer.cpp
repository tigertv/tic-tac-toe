#include "AiPlayer.h"
#include <random>
#include <chrono>

AiPlayer::~AiPlayer() {

}

AiPlayer::AiPlayer(BoardCell seed) {
    this->seed = seed;
}

BoardCell AiPlayer::getSeed() {
    return this->seed;
}

AiPlayer::AiPlayer(std::string seed) {
    this->seed = BoardCell(seed);
}

BoardCoords AiPlayer::move(Board *board) {
    BoardCoords coords;

    int height = board->getHeight();
    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, height);

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::minstd_rand0 generator(seed);

    coords.row = generator() % height;
    coords.column = generator() % height;
    return coords;
}
