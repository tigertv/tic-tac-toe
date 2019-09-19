#ifndef BOARDCELL_H_
#define BOARDCELL_H_

#include <string>

class BoardCell {
private:
    std::string value;
public:
    BoardCell(std::string value);
    BoardCell();
    virtual ~BoardCell();
    std::string getValue();
};

#endif