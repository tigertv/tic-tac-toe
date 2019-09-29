#ifndef BOARDCELL_H_
#define BOARDCELL_H_

#include <string>

class BoardCell {
private:
    std::string value;
public:
    BoardCell(const std::string& value);
    BoardCell();
    virtual ~BoardCell();
    std::string getValue();
    bool isEmpty();
};

#endif
