//
// Created by Wang wei on 2017/7/1.
//

#include "Knight.h"
#include "ChessController.h"


bool Knight::setPoint(int* des, ChessController* controller)
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

bool Knight::moveJudge(int* des, ChessController* controller)
{
//    cout<<"("
    Chessman* tmpChess = NULL;
    int tmpArray[2] = {0};

    //竖走日
    if(abs(point[1] - des[1]) == 2
       && abs(point[0] - des[0]) == 1)
    {
        tmpArray[0] = point[0];
        tmpArray[1] = (point[1] + des[1]) / 2;
        tmpChess = controller->whetherExist(tmpArray);
        return tmpChess == NULL;
    }
        //横走日
    else if(abs(point[0] - des[0]) == 2
            && abs(point[1] - des[1]) == 1)
    {
        tmpArray[1] = point[1];
        tmpArray[0] = (point[0] + des[0]) / 2;
        tmpChess = controller->whetherExist(tmpArray);
        if( tmpChess == NULL)
          return true;
        else
            return false;
    }
    else
    {
        return false;
    }
}
