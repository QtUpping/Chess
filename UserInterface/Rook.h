//
// Created by Wang wei on 2017/7/1.
//

#ifndef MYPART_ROOK_H
#define MYPART_ROOK_H

#include "Chessman.h"
class ChessController;


class Rook : public Chessman
{
public:
    Rook(int camp) : Chessman("³µ", camp){}
    bool setPoint(int* des, ChessController* controller);
    bool moveJudge(int* des, ChessController* controller);
};


#endif //MYPART_ROOK_H
