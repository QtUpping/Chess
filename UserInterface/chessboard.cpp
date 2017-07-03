#include "chessboard.h"
#include "ui_chessboard.h"
#include <QPushButton>
#include <QMouseEvent>
#include <QDebug>

static MoveRecord *click = new MoveRecord;      //����һ��MoveRecord����,  ͨ��ָ�����choose_or_move����

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
            ui->RCannon->move(originalXY[0]-20, originalXY[1]-20);                  //ƫ��20������ʹ��ť���ڵ��������  ��ť��С40*40
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

    /********�������갴ť**********/
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
        switch(click->getCounter() )               //������һ�ε��û�ȡ�ı���ֵ �ƶ���ͬ����
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
/**********************************��ť�ۺ���(ʵ���ƶ�, ʧЧ)*****************************************/
/**********************************������, ����*******************************************************/
void ChessBoard::on_RCannon_clicked()
{
    int originalXY[2]={ ui->RCannon->x(), ui->RCannon->y() };
    int XY[2]={ ui->RCannon->x(), ui->RCannon->y() };
    coordinateConversion(XY);

     /**������˳�����Ҫ, ��������ͨ��class Movestatu�е�MoveStatu��ֵ�����жϲ������޸�**/
    if( Capture(originalXY,1) )
    {
        ui->RCannon->setEnabled(false);
        ui->RCannon->hide();
    }
    click->Choose_or_Move_Judge(1);
    /**ǧ���ܵߵ�, ���ߵ������ƶ������޷���ȫʵ��**/
    /********************�������갴ť**********************/
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
     /*---------˳�����------------*/
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
    /*---------˳�����------------*/
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
    /*---------˳�����------------*/
    if( Capture(originalXY,4) )
    {
        ui->RRook2->setEnabled(false);
        ui->RRook2->hide();
    }
    click->Choose_or_Move_Judge(4);
   /*-----------------------------*/
}
/*****************************************�ۺ�������**************************************************/


/*************����û�����ⲿ��**********************/
void ChessBoard::coordinateConversion(int *XY)
{
    int Xoffset=20, Yoffset=20;
    int originalPoint[2]={395,250};                 //ԭ����������
    int h=50, w=50;                                  //С����ĳ���
    XY[0]-=originalPoint[0];
    XY[1]-=originalPoint[1];
    if(XY[1]>h*4)                                               //���ǳ��ӿ�� ����ƫ��  ������Դ�����뷽��ͬ��
       XY[1]-=0;
    coordinate[0]=(XY[0]+Xoffset)/w;                     //ƫ��һ��λ��ʹ�������㸽�����򼴿�p�ж�Ϊ����ڽ��洦
    coordinate[1]=(XY[1]+Yoffset)/h;
}
int *ChessBoard::getConversionCoordinate(int *point)               //��ҪС�Ķ�
{
     point[0]=coordinate[0];
     point[1]=coordinate[1];
    return point;
}
/**********����û�����ⲿ��**************************/


/*------------ʵ�ֹ��ܺ��Ƶ���һ���ļ���----------------*/
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

//����ֵ����ȥ��       ���ڸú�������Ϊ�ı����ӵ�״̬
void MoveRecord::Choose_or_Move_Judge(int count)
{
    //-----------------------------������Ϻ���������֧�ɺϲ�------------------------------*/
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
    //--------------------------�ɺϲ�����--------------------------------------------------*/
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

/*--------------------------�����ָ���---------------------------*/
//bool ChessBoard::validClick(int *XY)      //��ʱ����Ҫ
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



