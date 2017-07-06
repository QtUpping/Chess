//
// Created by Wang wei on 2017/7/1.
//

#include "ChessController.h"

//debug
#include <QDebug>

ChessController::ChessController()
{
    int point[32][2] = {0};
    int i = 0, j = 0, y = 0;

    for(i = 0; i < 9; i++){
        point[i][0] = i;
        point[i][1] = 9;
        point[31-i][0] = 8-i;
        point[31-i][1] = 0;
    }
    point[9][0] = 1; point[9][1] = 7;
    point[10][0] = 7;point[10][1] = 7;
    point[21][0] = 1; point[21][1] = 2;
    point[22][0] = 7;point[22][1] = 2;

    //�޸�: i<20��Ϊi<21
    for (i = 11; i < 21; i++, j+=2)
    {
        y = i<16?6:3;
        j = i==16?0:j;
        point[i][0] = j;
        point[i][1] = y;
    }

    for(i = 0; i < 4; i++)
    {
        //�޸�:  i<3��Ϊi<2
        j = i<2?0:1;
        rook[i] = new Rook(j);
        knight[i] = new Knight(j);
        bishop[i] = new Bishop(j);
        mandarin[i] = new Mandarin(j);
        cannon[i] = new Cannon(j);
    }
    for(i = 0; i < 10; i++)
    {
        j = i<5?0:1;
        pawn[i] = new Pawn(j);
    }
    king[0] = new King(0);
    king[1] = new King(1);

    piece[0] = rook[0];piece[8] = rook[1];
    piece[1] = knight[0];piece[7] = knight[1];
    piece[2] = bishop[0];piece[6] = bishop[1];
    piece[3] = mandarin[0];piece[5] = mandarin[1];
    piece[4] = king[0];
    piece[23] = rook[2];piece[31] = rook[3];
    piece[24] = knight[2];piece[30] = knight[3];
    piece[25] = bishop[2];piece[29] = bishop[3];
    piece[26] = mandarin[2];piece[28] = mandarin[3];
    piece[27] = king[1];
    piece[9] = cannon[0]; piece[10] = cannon[1];
    piece[21] = cannon[2];piece[22] = cannon[3];
    for(i = 11; i <21; i++)
    {
        piece[i] = pawn[i-11];
    }

    for(i = 0; i < 32; i++)
    {
        piece[i]->setOri(point[i]);
    }
}

//�����������ӣ��ж�des���Ƿ������ӣ��еĻ���������ָ�룬���򷵻�NULL

Chessman* ChessController::whetherExist(int* des)
{
    //debugʹ��
    qDebug("whetherExist receive(%d,%d)",des[0], des[1]);

    for(int i=0; i<32; ++i)
    {
        if(des[0] == piece[i]->getPoint()[0] && des[1] == piece[i]->getPoint()[1])
            return piece[i];
    }

    return NULL;
}

//������ͬһֱ�ߵĲ���������յ����ڵ�����֮�����������
//����ʱֻ����������ͬһֱ�ߵ�����
int ChessController::obstaclesOnLine(int* point, int* des)
{
    int num = 0;
    int tmpArray[2] = {0};
    Chessman* tmpChess = NULL;
    if((abs(point[0] - des[0]) + abs(point[1] - des[1])) == 1)          //ֱ���ƶ�һ��
        return 0;
    if(point[0] == des[0])
    {
        int i = point[1] < des[1]?point[1] + 1 : des[1] + 1;
        int max = point[1] > des[1]?point[1] - 1 : des[1] - 1;
        for(; i <= max; i++)
        {
            tmpArray[0] = point[0];
            tmpArray[1] = i;
            tmpChess = whetherExist(tmpArray);
            if(tmpChess != NULL)
                num++;
        }
    }
    else if(point[1] == des[1])                             //�����ƶ�������  ����������� ���������жϷ���
    {                                                                         //�������������   û���ж���ȷλ�ú������ĵ�
        int i = point[0] < des[0]?point[0] + 1:des[0] + 1;
        int max = point[0]>des[0]?point[0]-1: des[0] -1;
        for(; i <= max; i++)
        {
            tmpArray[0] = i;
            tmpArray[1] = point[1];                         //�޸�: ԭ�� tmpArrya[0] = point[1]; tmpArray[1] =i; ��Ϊ
            tmpChess = whetherExist(tmpArray);
            if(tmpChess != NULL)
                num++;
        }
    }
    return num;
}

bool ChessController::move(int *point, int *des)
{
    Chessman* start = whetherExist(point);
    Chessman* end = whetherExist(des);
    if(end == NULL)
    {
//        start->setPoint(des, this);
//        return true;
        //�޸�:  ע�Ͳ����� �����ƶ��Ƿ�,���������޷��ı�, ���Ƿ���ֵΪ��, ���°�ťλ�÷����ı�
        if( start->setPoint(des, this) )
        {
            return true;
        }
        else
            return false;
    }
    else  //�ƶ�λ�������� ��Ϊ�ط������ δ�Ա�����������������
    {
        //debug �޸�
        if(start->getCamp() != end->getCamp() )  //��ͬ��Ӫ �ɳ���
        {
            if( start->setPoint(des, this))                  //���ӷ����߷�
            {
                //�޸�: ��ӶԱ�����������Ĵ���, ��Ϊ-1,-1
                //��chessman����Ӻ���, ֱ�ӽ�point��Ϊ-1,-1  ԭ��ʹ��setPoint�ڲ������ƶ�����ʱ�޷��޸ĳ�-1,-1
                end->capturePiece();

                qDebug("Capture in movement!");

                return true;
            }
            else
                return  false;
        }

//        return start->getCamp() != end->getCamp()
//        && start->setPoint(des, this);
    }    
}

void ChessController::show()
{
    for (int i = 0; i < 32; i++) {
        cout<<piece[i]->getName()<<"  "
        <<piece[i]->getPoint()[0]<<"  "
        <<piece[i]->getPoint()[1]<<endl;
    }
}


int ChessController::posInArr(int *des)
{
    for(int i=0; i<32; ++i)
    {
        if(des[0] == piece[i]->getPoint()[0] && des[1] == piece[i]->getPoint()[1])
            return i;
    }
}
