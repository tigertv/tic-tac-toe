#ifndef BOARD_H_
#define BOARD_H_

#include <vector>
#include "BoardCell.h"

struct BoardCoords {
    int row;
    int column;
};

class Board {
private:
    BoardCell *cells;
    int filledCells = 0;
    int height;
    int width;
public:
    Board(int height, int width);
    virtual ~Board();
    void show();
    int setCell(int row, int column, BoardCell c);
    int setCell(BoardCoords coords, BoardCell c);
    BoardCell getCell(int row, int column);
    BoardCell getCell(BoardCoords coords);
    bool isFilled();
    int getWidth();
    int getHeight();
};

#endif
