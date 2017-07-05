//
// Created by Wang wei on 2017/7/1.
//


//ChessController类，用于对所有的棋子对象进行管理


#ifndef MYPART_CHESSCONTROLLER_H
#define MYPART_CHESSCONTROLLER_H

#include "AllChess.h"

class ChessController {
    //改动: 将所有私有成员改为公有
public:
    King* king[2];
    Bishop* bishop[4];
    Knight* knight[4];
    Mandarin* mandarin[4];
    Cannon* cannon[4];
    Rook* rook[4];
    Pawn* pawn[10];
    Chessman* piece[32];//储存所有棋子对象的指针

    ChessController();
    void showPieces();
    int obstaclesOnLine(int* point, int* des);
    Chessman* whetherExist(int* des);   //参数为终点坐标，判断终点是否有棋子
    bool move(int* point, int* des);    //接收移动参数，调用对象setPoint实现棋子的移动
    void show();



    //现有棋子判断函数根据下方红方坐标写的, 若要黑子能使用应转化坐标
    //添加坐标转换函数
    void CampCoordinateConversion(int *des);
};


#endif //MYPART_CHESSCONTROLLER_H
