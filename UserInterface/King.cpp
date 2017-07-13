//
// Created by Wang wei on 2017/7/1.
//

#include "King.h"
#include "ChessController.h"

bool King::setPoint(int* des, ChessController* controller)
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
bool King::moveJudge(int* des, ChessController* controller)
{
    return abs(point[0] - des[0]) + abs(point[1] - des[1]) == 1
           && des[0] > 2 && des[0] < 6
           &&( (des[1] > 6 && des[1] < 10)  || (des[1] >=0 && des[1] < 3) ) ;
}
