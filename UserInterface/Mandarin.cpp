//
// Created by Wang wei on 2017/6/30.
//

#include "Mandarin.h"
#include "ChessController.h"

bool Mandarin::setPoint(int *des, ChessController* controller) {
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

bool Mandarin::moveJudge(int *des, ChessController* controller) {
    //修改: 横纵坐标范围
    //1.士的移动范围为中间的正方形，横3~5 纵0~2 || 7~9。先判断这个条件是否符合
    if(des[0] >= 3 && des[0] <= 5 && (des[1] >= 0 && des[1] <= 2)||( des[1] >=7 && des[1]<=9 )  )
    {
        return abs(des[0] - point[0]) == 1 && abs(des[1] - point[1]) == 1;
    }
    else
    {
        return false;
    }
}
