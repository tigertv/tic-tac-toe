#include "Board.h"
#include <iostream>
#include <string>

Board::Board() {

}

Board::~Board() {

}

void Board::show() {
	using namespace std;
	string line = " -------------";
	for (int i = 0; i < 3; ++i) {
		cout << line << endl;
		for (int j = 0; j < 3; ++j) {
			cout << " | ";
			switch (this->cells[i * 3 + j]) {
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
	int i = row * 3 + column;
	if (i < 0 || i > 8) return 1;
	if (this->isFilled()) return 2;
	this->cells[i] = c;
	this->filledCells++;
	return 0;
}

BoardCell Board::getCell(int row, int column) {
	int i = row * 3 + column;
	if (i < 0 || i > 8) return NULL_CELL;
	return this->cells[i];
}

bool Board::isFilled() {
	return (this->filledCells == 9);
}
