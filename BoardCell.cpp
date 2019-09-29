#include "BoardCell.h"

BoardCell::BoardCell() {
    this->value = " ";
}

BoardCell::BoardCell(const std::string& value) {
    this->value = value;
}

BoardCell::~BoardCell() {

}

std::string BoardCell::getValue() {
    return this->value;
}

bool BoardCell::isEmpty() {
    return (this->value == " ");
}
