#include "GameMove.h"

GameMove::GameMove(BoardCoords coords) {
    this->coords = coords;
}

GameMove::~GameMove() {

}

BoardCoords GameMove::getCoords() {
    return this->coords;
}
