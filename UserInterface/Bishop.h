//
// Created by Wang wei on 2017/7/1.
//

#ifndef MYPART_BISHOP_H
#define MYPART_BISHOP_H

#include "Chessman.h"
class ChessController;

class Bishop : public Chessman
{
public:
    Bishop(int camp) :Chessman("��", camp) {}
    bool setPoint(int* des, ChessController* controller);
    bool moveJudge(int* des, ChessController* controller);
};


#endif //MYPART_BISHOP_H
