//
// Created by Wang wei on 2017/7/1.
//


//ChessController�࣬���ڶ����е����Ӷ�����й���


#ifndef MYPART_CHESSCONTROLLER_H
#define MYPART_CHESSCONTROLLER_H

#include "AllChess.h"

class ChessController {
    //�Ķ�: ������˽�г�Ա��Ϊ����
public:
    King* king[2];
    Bishop* bishop[4];
    Knight* knight[4];
    Mandarin* mandarin[4];
    Cannon* cannon[4];
    Rook* rook[4];
    Pawn* pawn[10];
    Chessman* piece[32];//�����������Ӷ����ָ��

    ChessController();
    void showPieces();
    int obstaclesOnLine(int* point, int* des);
    Chessman* whetherExist(int* des);   //����Ϊ�յ����꣬�ж��յ��Ƿ�������
    bool move(int* point, int* des);    //�����ƶ����������ö���setPointʵ�����ӵ��ƶ�
    void show();
    int posInArr(int* des);



    //���������жϺ��������·��췽����д��, ��Ҫ������ʹ��Ӧת������
    //�������ת������
    void CampCoordinateConversion(int *des);
};


#endif //MYPART_CHESSCONTROLLER_H
