#include "AiPlayer.h"
#include <random>
#include <chrono>

AiPlayer::~AiPlayer() {

}

AiPlayer::AiPlayer(std::string seed) {
    this->seed = seed;
}

GameMove AiPlayer::askMove(const Game& game) {
    Game aigame = game;
    std::vector<GameMove> moves = aigame.getPossibleMoves();
    int size = moves.size();

    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, size);

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::minstd_rand0 generator(seed);
    int i = generator() % size;

    return moves[i];
}
