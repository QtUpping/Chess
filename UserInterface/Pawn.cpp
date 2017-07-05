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

    if(getCamp() ==0 )                //�췽��
    {
        if((point[0] == des[0] && des[1] < point[1]) || (point[1] == des[1] && point[1] < 5))
        {
            /* �������ƶ���ȷ���Ѳ���������ť���ƺ�����ִ�а�ť�������ݺ��ж��Ƿ������ӣ�����ȵ�
             * Ȼ��ť���ƺ����������ӿ��ƺ����ȵ�
             * �����ӿ��ƺ���buttonController(this->point, int* des);
             * buttonController()����������˼:void buttonController(int* oldPoint, int* destination)
             */
    //        buttonController(point, des);
            return true;
        }
        else
            return false;
    }
    else                        //�ڷ���       ������Щ����  ���Ի��ߵ�ʱ�� ��������û�и��µ��ǰ�ť�ƶ���
    {
        if((point[0] == des[0] && des[1] > point[1]) || (point[1] == des[1] && point[1] >= 5) )
            return true;
        else
            return false;
    }
}

