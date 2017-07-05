//
// Created by Wang wei on 2017/7/1.
//

#include "Rook.h"
#include "ChessController.h"

bool Rook::setPoint(int* des, ChessController* controller)
{
    if(moveJudge(des, controller)){
        for(int i = 0; i < 2; i++){
            oldPoint[i] = this->point[i];
            this->point[i] = des[i];
        }
        return true;
    } else {
        return false;
    }
}

bool Rook::moveJudge(int *des, ChessController *controller)
{
    return (point[0] == des[0] || point[1] == des[1])
       && controller->obstaclesOnLine(point, des) == 0;
}