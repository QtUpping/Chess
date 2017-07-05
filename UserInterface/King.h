//
// Created by Wang wei on 2017/7/1.
//

#ifndef MYPART_KING_H
#define MYPART_KING_H

#include "Chessman.h"
class ChessController;

class King :public Chessman
{
public:
    King(int camp) : Chessman("˧", camp) {}
    bool setPoint(int* des, ChessController* controller);
    bool moveJudge(int* des, ChessController* controller);
};


#endif //MYPART_KING_H
