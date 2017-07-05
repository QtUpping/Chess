//
// Created by Wang wei on 2017/7/1.
//


//±øµÄÀà


#ifndef MYPART_PAWN_H
#define MYPART_PAWN_H

#include "Chessman.h"
class ChessController;

class Pawn : public Chessman
{
public:
    Pawn(int camp) : Chessman("±ø", camp){}
    bool setPoint(int* des, ChessController* controller);
    bool moveJudge(int* des, ChessController* controller);
};


#endif //MYPART_PAWN_H
