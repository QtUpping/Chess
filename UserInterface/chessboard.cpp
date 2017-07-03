#include "chessboard.h"
#include "ui_chessboard.h"
#include <QPushButton>
#include <QMouseEvent>
#include <QDebug>

static MoveRecord *click = new MoveRecord;      //创建一个MoveRecord的类,  通过指针调用choose_or_move函数

ChessBoard::ChessBoard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChessBoard)
{
    coordinate[0]=oldPoint[0]=coordinate[1]=oldPoint[1]=0;
    ui->setupUi(this);
}

ChessBoard::~ChessBoard()
{
    delete ui;
}

void ChessBoard::mousePressEvent(QMouseEvent *e)
{
    int originalXY[2] = {e->x(), e->y()};
    int XY[2]={e->x(), e->y()};
    coordinateConversion(XY);
    click->updateClickCoordinate(originalXY);

//     qDebug("Movestaty=%d    DBStaty=%d",click->getStatu(),click->getDBStatu() );
    if( click->getStatu() == false && click->getDBStatu() == false)
    {
        qDebug()<<"mouse at "<<originalXY[0]<<","<<originalXY[1];
        switch(click->getCounter())
        {
        case 1:
            ui->RCannon->move(originalXY[0]-20, originalXY[1]-20);                  //偏移20个像素使按钮处于点击处正中  按钮大小40*40
            break;
        case 2:
            ui->RCannon2->move(originalXY[0]-20, originalXY[1]-20);
            break;
        case 3:
            ui->RRook->move(originalXY[0]-20, originalXY[1]-20);
            break;
        case 4:
            ui->RRook2->move(originalXY[0]-20, originalXY[1]-20);
            break;
        }
    }
    click->resetStatuT();

    /********创建坐标按钮**********/
    QPushButton  *btn = new QPushButton(this);
    btn->setText( tr( "(%1,%2)").arg(e->x()).arg(e->y() ) );
    btn->show();
    QPushButton *b2 = new QPushButton(this);
    b2->setText( tr("(%1,%2)").arg(coordinate[0]).arg(coordinate[1] ) );
    b2->move(0,50);
    b2->show();
}

bool ChessBoard::Capture(int *XY,int count)
{
    if(  click->getStatu() == true  )
    {
         click->setCounter(count);
         qDebug()<<click->getCounter();
         return false;
    }
    else
    {
        switch(click->getCounter() )               //根据上一次调用获取的变量值 移动不同棋子
        {
        case 1:
            qDebug()<<"Capture() Move to "<<XY[0]<<","<<XY[1];
            ui->RCannon->move(XY[0], XY[1] );
            break;
        case 2:
             ui->RCannon2->move(XY[0], XY[1] );
            break;
        case 3:
             ui->RRook->move(XY[0], XY[1] );
            break;
        case 4:
             ui->RRook2->move(XY[0], XY[1] );
            break;
        }
        return true;
    }
}
/**********************************按钮槽函数(实现移动, 失效)*****************************************/
/**********************************即走棋, 吃子*******************************************************/
void ChessBoard::on_RCannon_clicked()
{
    int originalXY[2]={ ui->RCannon->x(), ui->RCannon->y() };
    int XY[2]={ ui->RCannon->x(), ui->RCannon->y() };
    coordinateConversion(XY);

     /**这两行顺序很重要, 两个函数通过class Movestatu中的MoveStatu的值进行判断并进行修改**/
    if( Capture(originalXY,1) )
    {
        ui->RCannon->setEnabled(false);
        ui->RCannon->hide();
    }
    click->Choose_or_Move_Judge(1);
    /**千万不能颠倒, 若颠倒棋子移动功能无法完全实现**/
    /********************创建坐标按钮**********************/
//    QPushButton *b2 = new QPushButton(this);
//    b2->setText( tr("Cannon1(%1,%2)").arg(coordinate[0]).arg(coordinate[1] ) );
//    b2->setGeometry(0,100,100,30);
//    b2->show();
}
void ChessBoard::on_RCannon2_clicked()
{
     int originalXY[2] = { ui->RCannon2->x(), ui->RCannon2->y() };
     int XY[2]={ ui->RCannon2->x(), ui->RCannon2->y() };
     coordinateConversion(XY);
     /*---------顺序别乱------------*/
     if( Capture(originalXY,1) )
     {
         ui->RCannon2->setEnabled(false);
         ui->RCannon2->hide();
     }
     click->Choose_or_Move_Judge(2);
    /*-----------------------------*/
}
void ChessBoard::on_RRook_clicked()
{
    int originalXY[2] = { ui->RRook->x(), ui->RRook->y() };
    int XY[2]={ ui->RRook->x(), ui->RRook->y() };
    coordinateConversion(XY);
    /*---------顺序别乱------------*/
    if( Capture(originalXY,3) )
    {
        ui->RRook->setEnabled(false);
        ui->RRook->hide();
    }
    click->Choose_or_Move_Judge(3);
   /*-----------------------------*/
}
void ChessBoard::on_RRook2_clicked()
{
    int originalXY[2] = { ui->RRook2->x(), ui->RRook2->y() };
    int XY[2]={ ui->RRook2->x(), ui->RRook2->y() };
    coordinateConversion(XY);
    /*---------顺序别乱------------*/
    if( Capture(originalXY,4) )
    {
        ui->RRook2->setEnabled(false);
        ui->RRook2->hide();
    }
    click->Choose_or_Move_Judge(4);
   /*-----------------------------*/
}
/*****************************************槽函数部分**************************************************/


/*************基本没有问题部分**********************/
void ChessBoard::coordinateConversion(int *XY)
{
    int Xoffset=20, Yoffset=20;
    int originalPoint[2]={395,250};                 //原点像素坐标
    int h=50, w=50;                                  //小方格的长宽
    XY[0]-=originalPoint[0];
    XY[1]-=originalPoint[1];
    if(XY[1]>h*4)                                               //考虑楚河宽度 向上偏移  本次资源楚河与方格同宽
       XY[1]-=0;
    coordinate[0]=(XY[0]+Xoffset)/w;                     //偏移一定位置使点击交叉点附近区域即可p判断为点击在交叉处
    coordinate[1]=(XY[1]+Yoffset)/h;
}
int *ChessBoard::getConversionCoordinate(int *point)               //需要小改动
{
     point[0]=coordinate[0];
     point[1]=coordinate[1];
    return point;
}
/**********基本没有问题部分**************************/


/*------------实现功能后移到另一个文件中----------------*/
MoveRecord::MoveRecord():MoveStatu(true), doubleStatu(true),MovePieceCounter(0)
{
    Point[0]=Point[1]=-1;
}

void MoveRecord::setCounter(int count)
{
    MovePieceCounter = count;
}

int MoveRecord::getCounter()
{
    return MovePieceCounter;
}

void MoveRecord::resetStatuT()
{
    MoveStatu = doubleStatu = true;
}

bool MoveRecord::getDBStatu()
{
    return doubleStatu;
}
bool MoveRecord::getStatu()
{
    return MoveStatu;
}

//返回值可以去掉       现在该函数功能为改变棋子的状态
void MoveRecord::Choose_or_Move_Judge(int count)
{
    //-----------------------------测试完毕后这两个分支可合并------------------------------*/
    if(     MoveStatu == false  && doubleStatu ==false && MovePieceCounter == count   )
    {
        qDebug()<<"Cancel movement\n";
        MoveStatu  =  true;
    }
    else if( MoveStatu == false  && doubleStatu ==false && MovePieceCounter != count  )
    {
        qDebug()<<"Move to new button pos\n";
       MoveStatu  =  true;
    }
    //--------------------------可合并部分--------------------------------------------------*/
    else
    {
        qDebug()<<"The Button Is Ready To Move! ";
         MoveStatu = doubleStatu =  false;
    }
}

int *MoveRecord::updateClickCoordinate(int *XY)
{
    qDebug()<<"Update point"<<XY[0]<<","<<XY[1]<<endl;
    Point[0]=XY[0];     Point[1]=XY[1];
    return XY;
}
/*--------------------------------------------------------*/

/*--------------------------垃圾分割线---------------------------*/
//bool ChessBoard::validClick(int *XY)      //暂时不需要
//{
//     int originalPointEdge[2]={140,20};
//     int opposite[2]={1055,940};
//     for(int i=0; i<2;++i)
//     {
//        if(XY[i]<originalPointEdge[i] && XY[i]>opposite[i] )
//                return false;
//     }
//     return true;
//}



