//
// Created by Wang wei on 2017/7/1.
//

//炮的类

#ifndef MYPART_CANNON_H
#define MYPART_CANNON_H

#include "Chessman.h"
class ChessController;

class Cannon : public Chessman
{
public:
    Cannon(int camp) : Chessman("炮", camp){}
    bool setPoint(int* des, ChessController* controller);
    bool moveJudge(int* des, ChessController* controller);
};


#endif //MYPART_CANNON_H
