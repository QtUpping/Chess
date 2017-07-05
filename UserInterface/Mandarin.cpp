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
    //�޸�: �������귶Χ
    //1.ʿ���ƶ���ΧΪ�м�������Σ���3~5 ��0~2 || 7~9�����ж���������Ƿ����
    if(des[0] >= 3 && des[0] <= 5 && (des[1] >= 0 && des[1] <= 2)||( des[1] >=7 && des[1]<=9 )  )
    {
        return abs(des[0] - point[0]) == 1 && abs(des[1] - point[1]) == 1;
    }
    else
    {
        return false;
    }
}
