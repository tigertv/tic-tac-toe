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
            cout << " | ";
            switch (this->cells[i * this->width + j]) {
            case BoardCell::EMPTY:
                cout << ' ';
                break;

            case BoardCell::ZERO:
                cout << 'O';
                break;

            case BoardCell::CROSS:
                cout << 'X';
                break;

            default:
                cout << "ERROR";
                break;
            }
        }
        cout << " |" << endl;
    }
    cout << line << endl;
}

int Board::setCell(int row, int column, BoardCell c) {
    if (row < 0 || row >= this->height) return 1;
    if (column < 0 || column >= this->width) return 1;
    if (this->isFilled()) return 2;

    int i = row * this->width + column;

    this->cells[i] = c;
    if (c != BoardCell::EMPTY) {
        this->filledCells++;
    }
    return 0;
}

BoardCell Board::getCell(int row, int column) {
    if (row < 0 || row >= this->height) return NULL_CELL;
    if (column < 0 || column >= this->width) return NULL_CELL;

    int i = row * this->width + column;
    return this->cells[i];
}

int Board::setCell(BoardCoords coords, BoardCell c) {
    return this->setCell(coords.row, coords.column, c);
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
