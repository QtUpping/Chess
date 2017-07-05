//
// Created by Wang wei on 2017/7/1.
//
//这是所有棋子的父类，用于设计棋子的基本功能
/*
 * getPoint，getCamp，getName用于获取棋子的基本信息
 * moveJudge需要每个棋子子类实现，根据棋子类型判断落子是否合理
 * 若moveJudge*/

#ifndef MYPART_CHESSMAN_H
#define MYPART_CHESSMAN_H

#include <string>
#include <iostream>
using namespace std;
class ChessController;

class Chessman {
protected:
    string name;
    int point[2];       //point[0]代表横坐标，point[1]代表纵坐标
    int oldPoint[2];
    int camp;           //0代表红，1代表黑
public:
    Chessman(string name, int camp);
    ~Chessman();

    /* 因为在走棋的时候需要根据棋子种类判断走法时候有效，所以设置位置函数
     * 为纯虚函数
     */
    virtual bool moveJudge(int* des, ChessController* controller) = 0;

    /*因为获取棋子信息不需要对棋子属性进行修改，所以统一在父类中进行定义*/
    int* getPoint();
    int getCamp();
    string getName();
    void setOri(int des[]);
    void setCamp(int side);
    virtual bool setPoint(int* point, ChessController* controller) = 0;
};


#endif //MYPART_CHESSMAN_H