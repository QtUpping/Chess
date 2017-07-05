//
// Created by Wang wei on 2017/7/1.
//

#ifndef MYPART_KNIGHT_H
#define MYPART_KNIGHT_H

#include "Chessman.h"
class ChessController;


class Knight : public Chessman{
public:
    Knight(int camp) : Chessman("Âí", camp){}
    bool setPoint(int* des, ChessController* controller);
    bool moveJudge(int* des, ChessController* controller);
};


#endif //MYPART_KNIGHT_H
