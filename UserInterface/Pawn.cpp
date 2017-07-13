//
// Created by Wang wei on 2017/6/30.
//

#include "Pawn.h"
#include "ChessController.h"

bool Pawn::setPoint(int *des, ChessController* controller)
{

    if(moveJudge(des, controller))
    {
        for(int i = 0; i < 2; i++)
        {
            oldPoint[i] = this->point[i];
            this->point[i] = des[i];
        }
        return true;
    } else {
        return false;
    }
}

bool Pawn::moveJudge(int* des, ChessController* controller)
{
    if(abs(des[0] - point[0]) + abs(des[1] - point[1]) != 1)
    {
        return false;
    }
    if(getCamp() ==0 )                //红方兵
    {
        if((point[0] == des[0] && des[1] < point[1]) || (point[1] == des[1] && point[1] < 5))
        {
            return true;
        }
        else
            return false;
    }
    else
    {
        if((point[0] == des[0] && des[1] > point[1]) || (point[1] == des[1] && point[1] >= 5) )
            return true;
        else
            return false;
    }
}

