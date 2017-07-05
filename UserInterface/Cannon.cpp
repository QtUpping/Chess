//
// Created by Wang wei on 2017/7/1.
//

#include "Cannon.h"
#include "ChessController.h"

bool Cannon::setPoint(int *des, ChessController* controller)
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

bool Cannon::moveJudge(int* des, ChessController* controller)
{
    int numOfObstacles = controller->obstaclesOnLine(point, des);
    Chessman* enemy = controller->whetherExist(des);
    return (point[0] == des[0] && (numOfObstacles == 0 && enemy == NULL)) || (numOfObstacles == 1 && enemy != NULL)
    || (point[1] == des[1] && (numOfObstacles == 0 && enemy == NULL));
}
