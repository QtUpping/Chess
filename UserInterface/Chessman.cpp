//
// Created by Wang wei on 2017/6/30.
//

#include "Chessman.h"
#include "ChessController.h"

Chessman::Chessman(string name, int camp)
: name(name), camp(camp) {
    oldPoint[0] = oldPoint[1] = point[0] = point[1] = 0;
}

Chessman::~Chessman() {
    oldPoint[0] = oldPoint[1] = point[0] = point[1] = 0;
}

int* Chessman::getPoint(){
    return this->point;
}

int Chessman::getCamp(){
    return this->camp;
}

string Chessman::getName(){
    return this->name;
}

void Chessman::setOri(int des[])
{
    point[0] = des[0];
    point[1] = des[1];
}

void Chessman::setCamp(int side)
{
    camp = side;
}
//bool Chessman::setPoint(int* des){
//    if(moveJudge(des)){
//        for(int i = 0; i < 2; i++){
//            oldPoint[i] = this->point[i];
//            this->point[i] = des[i];
//        }
//        return true;
//    } else {
//        return false;
//    }
//}
