//
// Created by Wang wei on 2017/6/30.
//


//士的类


#ifndef MYPART_MANDARIN_H
#define MYPART_MANDARIN_H

#include "Chessman.h"
//#include "ChessController.h"
class ChessController;

class Mandarin : public Chessman
{
public:
    Mandarin(int camp) : Chessman("士", camp){}
    bool setPoint(int* des, ChessController* controller);
    bool moveJudge(int* des, ChessController* controller);
};


#endif //MYPART_MANDARIN_H
