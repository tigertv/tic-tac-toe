#include "Player.h"

Player::Player(BoardCell seed) {
    this->seed = seed;
}

Player::~Player() {

}

BoardCell Player::getSeed() {
    return this->seed;
}
