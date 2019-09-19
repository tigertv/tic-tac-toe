#include "Player.h"

Player::~Player() {

}

Player::Player(BoardCell seed) {
    this->seed = seed;
}

BoardCell Player::getSeed() {
    return this->seed;
}

Player::Player(std::string seed) {
    this->seed = BoardCell(seed);
}
