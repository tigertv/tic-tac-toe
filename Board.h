#ifndef BOARD_H_
#define BOARD_H_

enum BoardCell {
	EMPTY, ZERO, CROSS, NULL_CELL
};

class Board {
private:
	BoardCell cells[9] = {};
	int filledCells = 0;
public:
	Board();
	virtual ~Board();
	void show();
	int setCell(int row, int column, BoardCell c);
	BoardCell getCell(int row, int column);
	bool isFilled();
};

#endif
