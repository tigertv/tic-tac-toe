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

int Board::setCell(int row, int column, BoardCell c) {
    if (row < 0 || row >= this->height || column < 0 || column >= this->width) {
        throw std::out_of_range ("the row or the column is out of range");
    }

    int i = row * this->width + column;

    if (c.getValue() != " " && this->cells[i].getValue() == " ") {
        this->filledCells++;
    }
    this->cells[i] = c;
    return 0;
}

int Board::setCell(BoardCoords coords, BoardCell c) {
    return this->setCell(coords.row, coords.column, c);
}

BoardCell Board::getCell(int row, int column) {
    if (row < 0 || row >= this->height) return BoardCell("");
    if (column < 0 || column >= this->width) return BoardCell("");

    int i = row * this->width + column;
    return this->cells[i];
}

BoardCell Board::getCell(BoardCoords coords) {
    return this->getCell(coords.row, coords.column);
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
