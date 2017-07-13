//
// Created by Wang wei on 2017/7/1.
//


//兵的类


#ifndef MYPART_PAWN_H
#define MYPART_PAWN_H

#include "Chessman.h"
class ChessController;

class Pawn : public Chessman
{
public:
    Pawn(int camp) : Chessman("兵", camp){}
    bool setPoint(int* des, ChessController* controller);
    bool moveJudge(int* des, ChessController* controller);
};


#endif //MYPART_PAWN_H
