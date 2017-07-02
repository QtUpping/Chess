#include "chessboard.h"
#include "ui_chessboard.h"
#include <QPushButton>
#include <QMouseEvent>
#include <QDebug>

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
    int XY[2]={e->x(), e->y()};
//    if(validClick(XY))
         coordinateConversion(XY);
//    else  qDebug()<<"InvalidClick!";

    /********��ʾ������**********/
    QPushButton  *btn = new QPushButton(this);
    btn->setText( tr( "(%1,%2)").arg(e->x()).arg(e->y() ) );
    btn->show();
    QPushButton *b2 = new QPushButton(this);
    b2->setText( tr("(%1,%2)").arg(coordinate[0]).arg(coordinate[1] ) );
    b2->setGeometry(0,50,100,30);
    b2->show();

}

int *ChessBoard::getCurCoordinate(int *point)
{
     point[0]=coordinate[0];
     point[1]=coordinate[1];
    return point;
}

void ChessBoard::coordinateConversion(int *XY)
{
    int originalPoint[2]={155,40};                 //ԭ����������
    int h=90, w=110;                                  //С����ĳ���
    XY[0]-=originalPoint[0];
    XY[1]-=originalPoint[1];
    if(XY[1]>h*4)                                               //���ǳ��ӿ�� ����ƫ��
       XY[1]-=40;
    coordinate[0]=(XY[0]+50)/w;                     //ƫ��һ��λ��ʹ�������㸽�����򼴿�p�ж�Ϊ����ڽ��洦
    coordinate[1]=(XY[1]+30)/h;
}

bool ChessBoard::validClick(int *XY)
{
     int originalPointEdge[2]={140,20};
     int opposite[2]={1055,940};
     for(int i=0; i<2;++i)
     {
        if(XY[i]<originalPointEdge[i] && XY[i]>opposite[i] )
                return false;
     }
     return true;
}

void ChessBoard::on_RCannon_clicked()
{
   int XY[2]={ ui->RCannon->x(), ui->RCannon->y() };
    coordinateConversion(XY);

    /********��ʾ������**********/
    QPushButton *b2 = new QPushButton(this);
    b2->setText( tr("Cannon1(%1,%2)").arg(coordinate[0]).arg(coordinate[1] ) );
    b2->setGeometry(0,100,100,30);
    b2->show();
    ui->RCannon->move(245,210);
}

void ChessBoard::on_RCannon2_clicked()
{
    int XY[2]={ ui->RCannon2->x(), ui->RCannon2->y() };
     coordinateConversion(XY);

     /********��ʾ������**********/
     QPushButton *b2 = new QPushButton(this);
     b2->setText( tr("Cannon2(%1,%2)").arg(coordinate[0]).arg(coordinate[1] ) );
     b2->setGeometry(0,150,100,30);
     b2->show();
     ui->RCannon2->setGeometry(930,210,41,41);
}
