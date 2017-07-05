//
// Created by Wang wei on 2017/7/1.
//

#include "Bishop.h"
#include "ChessController.h"

bool Bishop::setPoint(int* des, ChessController* controller)
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

bool Bishop::moveJudge(int* des, ChessController* controller)
{
    if(abs(point[0] - des[0]) == 2 && abs(point[1] - des[1]) == 2)
    {
        Chessman* tmpChess = NULL;
        int tmpArray[2] = {(point[0]+des[0])/2, (point[1]+des[1])/2};
        tmpChess = controller->whetherExist(tmpArray);

        //debug�޸�
        if(tmpChess == NULL )
        {
            if( des[1]>4){
                return true;
            }
            else
                return false;
        }
        else return false;          //���һ��else ��if�жϲ�Ϊ�� ��˵�����ϰ����޷��ƶ� ���ؼ�
        //���Ը���һ��false�ϲ� �Ƚϼ��

//        return tmpChess == NULL && des[1] > 4;
    }
    else
    {
        return false;
    }
}
