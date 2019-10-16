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
    BoardCell emptyCell;
    BoardCell **cells;
    int filledCells = 0;
    const int height;
    const int width;
    const int cellCount;
public:
    Board(int height, int width);
    Board(const Board& board);
    virtual ~Board();
    void show();
    void setCell(BoardCoords coords, BoardCell& c);
    BoardCell& getCell(BoardCoords coords);
    bool isFilled();
    int getWidth();
    int getHeight();
    std::vector<BoardCoords> getEmptyCells();
};

#endif
