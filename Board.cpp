#include "Board.h"
#include <iostream>
#include <string>

Board::Board(int height, int width) {
    this->height = height;
    this->width = width;
    this->cells = new BoardCell[width * height];
}

Board::~Board() {
    delete[] this->cells;
}

void Board::show() {
    using namespace std;
    string line(this->width * 4 + 1, '-');
    line = " " + line;
    for (int i = 0; i < this->height; ++i) {
        cout << line << endl;
        for (int j = 0; j < this->width; ++j) {
            cout << " | " << this->cells[i * this->width + j].getValue();
        }
        cout << " |" << endl;
    }
    cout << line << endl;
}

void Board::setCell(BoardCoords coords, BoardCell c) {
    if (coords.row < 0 || coords.row >= this->height || coords.column < 0
            || coords.column >= this->width) {
            throw std::out_of_range ("the row or the column is out of range");
    }

    int i = coords.row * this->width + coords.column;

    if (!c.isEmpty() && this->cells[i].isEmpty()) {
        this->filledCells++;
    }
    this->cells[i] = c;
}

BoardCell Board::getCell(BoardCoords coords) {
    if (coords.row < 0 || coords.row >= this->height || coords.column < 0
            || coords.column >= this->width) {
        return BoardCell("");
    }

    int i = coords.row * this->width + coords.column;
    return this->cells[i];
}

bool Board::isFilled() {
    return (this->filledCells == this->height * this->width );
}

int Board::getWidth() {
    return this->width;
}

int Board::getHeight() {
    return this->height;
}

bool Board::isEmptyCell(BoardCoords coords) {
    return (this->getCell(coords).getValue() == " ");
}
