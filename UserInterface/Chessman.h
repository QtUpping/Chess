//
// Created by Wang wei on 2017/7/1.
//
//�����������ӵĸ��࣬����������ӵĻ�������
/*
 * getPoint��getCamp��getName���ڻ�ȡ���ӵĻ�����Ϣ
 * moveJudge��Ҫÿ����������ʵ�֣��������������ж������Ƿ����
 * ��moveJudge*/

#ifndef MYPART_CHESSMAN_H
#define MYPART_CHESSMAN_H

#include <string>
#include <iostream>
using namespace std;
class ChessController;

class Chessman {
protected:
    string name;
    int point[2];       //point[0]��������꣬point[1]����������
    int oldPoint[2];
    int camp;           //0����죬1�����
public:
    Chessman(string name, int camp);
    ~Chessman();

    /* ��Ϊ�������ʱ����Ҫ�������������ж��߷�ʱ����Ч����������λ�ú���
     * Ϊ���麯��
     */
    virtual bool moveJudge(int* des, ChessController* controller) = 0;

    /*��Ϊ��ȡ������Ϣ����Ҫ���������Խ����޸ģ�����ͳһ�ڸ����н��ж���*/
    int* getPoint();
    int getCamp();
    string getName();
    void setOri(int des[]);
    void setCamp(int side);
    virtual bool setPoint(int* point, ChessController* controller) = 0;
};


#endif //MYPART_CHESSMAN_H