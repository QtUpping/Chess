//
// Created by Wang wei on 2017/6/30.
//

#include "Pawn.h"
#include "ChessController.h"
//debug
#include <QDebug>

bool Pawn::setPoint(int *des, ChessController* controller)
{

    if(moveJudge(des, controller))
    {
        for(int i = 0; i < 2; i++)
        {
            //debug:
            qDebug("des (%d,%d)     and coordinate is updated",des[0],des[1]);
            //

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
    int curCamp=getCamp();

    //debug:
    qDebug("curCamp = %d",curCamp);

    if(getCamp() ==0 )                //红方兵
    {
        if((point[0] == des[0] && des[1] < point[1]) || (point[1] == des[1] && point[1] < 5))
        {
            /* 若本身移动正确，把参数传给按钮控制函数，执行按钮参数传递和判断是否有棋子，吃棋等等
             * 然后按钮控制函数调用棋子控制函数等等
             * 设棋子控制函数buttonController(this->point, int* des);
             * buttonController()函数声明构思:void buttonController(int* oldPoint, int* destination)
             */
    //        buttonController(point, des);
            return true;
        }
        else
            return false;
    }
    else                        //黑方卒       走棋有些问题  尝试回走的时候 棋子坐标没有更新但是按钮移动了
    {
        if((point[0] == des[0] && des[1] > point[1]) || (point[1] == des[1] && point[1] >= 5) )
            return true;
        else
            return false;
    }
}

