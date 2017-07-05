#include "chessboard.h"
#include "ui_chessboard.h"
#include <QPushButton>
#include <QMouseEvent>
#include <QDebug>
#include "AllChess.h"
#include "Chessman.h"

static MoveRecord *click = new MoveRecord;      //����һ��MoveRecord�������,  ͨ��ָ�����choose_or_move����
static QPushButton *ChessmanButton[32] = {0};    //����һ��PushButtonָ�������а�ť��ַ

static ChessController *tmp = new ChessController;


ChessBoard::ChessBoard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChessBoard)
{
    coordinate[0]=oldPoint[0]=coordinate[1]=oldPoint[1]=0;
    ui->setupUi(this);

    ChessmanButton[0]=ui->RRook;
    ChessmanButton[1]=ui->RKnight;
    ChessmanButton[2]=ui->RBIshop;
    ChessmanButton[3]=ui->RMandarin;
    ChessmanButton[4]=ui->RKing;
    ChessmanButton[5]=ui->RMandarin_2;
    ChessmanButton[6]=ui->RBishop2;
    ChessmanButton[7]=ui->RKnight2;
    ChessmanButton[8]=ui->RRook2;
    ChessmanButton[9]=ui->RCannon;
    ChessmanButton[10]=ui->RCannon2;
    ChessmanButton[11]=ui->RPawn1;
    ChessmanButton[12]=ui->RPawn2;
    ChessmanButton[13]=ui->Rpawn3;
    ChessmanButton[14]=ui->RPawn4;
    ChessmanButton[15]=ui->RPawn5;

    ChessmanButton[16]=ui->BPawn1;
    ChessmanButton[17]=ui->BPawn2;
    ChessmanButton[18]=ui->BPawn3;
    ChessmanButton[19]=ui->BPawn4;
    ChessmanButton[20]=ui->BPawn5;
    ChessmanButton[21]=ui->BCannon1;
    ChessmanButton[22]=ui->BCannon2;
    ChessmanButton[23]=ui->BRook1;
    ChessmanButton[24]=ui->BKnight1;
    ChessmanButton[25]=ui->BBishop1;
    ChessmanButton[26]=ui->BMandarin;
    ChessmanButton[27]=ui->BKing;
    ChessmanButton[28]=ui->BMandarin2;
    ChessmanButton[29]=ui->BBishop2;
    ChessmanButton[30]=ui->BKnight2;
    ChessmanButton[31]=ui->BRook2;

//������Ӫ��ʼ����ť��ʾ��ͬ������
//��Ҫ��ȡ��ǰΪ�췽�ڷ�
    QIcon R1( ":/ChessImages/Images/RookR.GIF" );
    ChessmanButton[0]->setIcon(R1);
    ChessmanButton[0]->setIconSize(QSize(40,40) );
    ChessmanButton[0]->setFlat(true);
    ChessmanButton[8]->setIcon(R1);
    ChessmanButton[8]->setIconSize(QSize(40,40) );
    ChessmanButton[8]->setFlat(true);

    QIcon R2( ":/ChessImages/Images/KnightR.GIF" );
    ChessmanButton[1]->setIcon(R2);
    ChessmanButton[1]->setIconSize(QSize(40,40) );
    ChessmanButton[1]->setFlat(true);
    ChessmanButton[7]->setIcon(R2);
    ChessmanButton[7]->setIconSize(QSize(40,40) );
    ChessmanButton[7]->setFlat(true);

    QIcon R3( ":/ChessImages/Images/RB.GIF" );
    ChessmanButton[2]->setIcon(R3);
    ChessmanButton[2]->setIconSize(QSize(40,40) );
    ChessmanButton[2]->setFlat(true);
    ChessmanButton[6]->setIcon(R3);
    ChessmanButton[6]->setIconSize(QSize(40,40) );
    ChessmanButton[6]->setFlat(true);

    QIcon R4( ":/ChessImages/Images/MandarinR.GIF" );
    ChessmanButton[3]->setIcon(R4);
    ChessmanButton[3]->setIconSize(QSize(40,40) );
    ChessmanButton[3]->setFlat(true);
    ChessmanButton[5]->setIcon(R4);
    ChessmanButton[5]->setIconSize(QSize(40,40) );
    ChessmanButton[5]->setFlat(true);

    QIcon R5( ":/ChessImages/Images/KingR.GIF" );
    ChessmanButton[4]->setIcon(R5);
    ChessmanButton[4]->setIconSize(QSize(40,40) );
    ChessmanButton[4]->setFlat(true);

    QIcon R6( ":/ChessImages/Images/CannonR.GIF" );
    ChessmanButton[9]->setIcon(R6);
    ChessmanButton[9]->setIconSize(QSize(40,40) );
    ChessmanButton[9]->setFlat(true);
    ChessmanButton[10]->setIcon(R6);
    ChessmanButton[10]->setIconSize(QSize(40,40) );
    ChessmanButton[10]->setFlat(true);

    QIcon R7( ":/ChessImages/Images/PawnR.GIF" );
    for(int i=11; i<16;++i)
    {
        ChessmanButton[i]->setIcon(R7);
        ChessmanButton[i]->setIconSize(QSize(40,40) );
        ChessmanButton[i]->setFlat(true);
    }

}

ChessBoard::~ChessBoard()
{
    delete ui;
}

void ChessBoard::mousePressEvent(QMouseEvent *e)
{
    int originalXYcur[2] = {e->x(), e->y()};
    int XY[2]={e->x(), e->y()};
    coordinateConversion(XY);

    //û���ϵ����  ����ɾ��
    click->updateClickCoordinate(originalXYcur);

//    if( click->getStatu() == false && click->getDBStatu() == false)
//    {
//        qDebug()<<"mouse at "<<originalXY[0]<<","<<originalXY[1];
//        //ʵ�ֵ�����ť���ߵ��յ�
//        //ƫ��20�����ص�ʹ��ť���ڵ��������  ��ť��С40*40
//          ChessmanButton[ click->getCounter()-1 ]->move(originalXY[0]-20, originalXY[1]-20);
//    }
//    click->resetStatuT();

    if( click->getStatu() == false && click->getDBStatu() == false)
    {
//        qDebug()<<"Mouse at "<<originalXYcur[0]<<","<<originalXYcur[1];
        qDebug()<<"Button tried to move to ("<<coordinate[0]<<","<<coordinate[1]<<")";

       int *lastpoint = tmp->piece[ click->getCounter()-1 ]->getPoint();
        //��ʹ�� tmp->piece[ click->getCounter()-1 ]->setPoint(coordinate, tmp) ��Ϊʹ��tmp->move(lastpoint ,coordinate)
       qDebug("lastpoint in mouseEvent is (%d,%d)",lastpoint[0],lastpoint[1]);
        if( tmp->move(lastpoint ,coordinate)  )
        {
           qDebug()<<"Button arrived at "<<coordinate[0]<<","<<coordinate[1];
          ChessmanButton[ click->getCounter()-1 ]->move(originalXYcur[0]-20, originalXYcur[1]-20);
//          click->resetStatuT();
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

//������һ��ѡ�а�ť�ƶ������ε����ťλ��  ����ĺ�����
bool ChessBoard::Capture(int *XY,int count)
{
    if(  click->getStatu() == true  )
    {
         click->setCounter(count);
         //�����  �ǵ�ɾ*********************************
        qDebug()<<click->getCounter();
         return false;
    }
    else
    {
//      ChessmanButton[click->getCounter()-1]->move(XY[0], XY[1]);
//tmp->piece[ click->getCounter() -1] ->setPoint(XY,tmp)

        int *lastpoint = tmp->piece[ click->getCounter()-1 ]->getPoint();
        //��ʹ�� tmp->piece[ click->getCounter()-1 ]->setPoint(coordinate, tmp) ��Ϊʹ��
        if( tmp->move( lastpoint, coordinate )  )
        {
            ChessmanButton[click->getCounter()-1]->move(XY[0], XY[1]);
            return true;
        }
        else
            return false;
    }
}

/*
 *    Bishop->setStyleSheet(QString("QPushButton{border-image: url(:/POLISH/CannonR.GIF);}"

                                  "QPushButton:pressed{ border-image: url(:/POLISH/CannonR2.GIF);}"   ) );
    bool imageStatu = true;
    if( imageStatu == true)
    {
        ChessmanButton[0]->setStyleSheet("QPushButton{border-image: qrc:/ChessImages/Images/RookR.GIF};");
        imageStatu = false;
    }else {
        ChessmanButton[0]->setStyleSheet("QPushButton{border-image: qrc:/ChessImages/Images/RookRS.GIF};");
        imageStatu = true;
    }
*/
/**********************************��ť�ۺ���(**************)*************************************************/
/********************************** ����(�ߵ���һ����ť��ʹ��ʧЧ)*******************************************/
void ChessBoard::on_RRook_clicked()
{
    int originalXY[2] = { ui->RRook->x(), ui->RRook->y() };
    int XY[2]={ ui->RRook->x() , ui->RRook->y() };
    coordinateConversion(XY);
    /*---------˳�����------------*/
    if( Capture(originalXY,1) && 1 !=click->getCounter()  )
    {
        ui->RRook->setEnabled(false);
        ui->RRook->hide();
    }
    click->Choose_or_Move_Judge(1);
   /*-----------------------------*/
}
void ChessBoard::on_RKnight_clicked()
{
    int originalXY[2] = { ui->RKnight->x(), ui->RKnight->y() };
    int XY[2]={ ui->RKnight->x(), ui->RKnight->y() };
    coordinateConversion(XY);

    qDebug("(%d,%d)",coordinate[0],coordinate[1]);
    /*---------˳�����------------*/
    if( Capture(originalXY,2) && 2 !=click->getCounter()  )
    {
        ui->RKnight->setEnabled(false);
        ui->RKnight->hide();
    }
    click->Choose_or_Move_Judge(2);
}
void ChessBoard::on_RBIshop_clicked()
{
    int originalXY[2] = { ui->RBIshop->x(), ui->RBIshop->y() };
    int XY[2]={ ui->RBIshop->x(), ui->RBIshop->y() };
    coordinateConversion(XY);
    /*---------˳�����------------*/
    if( Capture(originalXY,3) && 3 !=click->getCounter()  )
    {
        ui->RBIshop->setEnabled(false);
        ui->RBIshop->hide();
    }
    click->Choose_or_Move_Judge(3);
}
void ChessBoard::on_RMandarin_clicked()
{
    int originalXY[2] = { ui->RMandarin->x(), ui->RMandarin->y() };
    int XY[2]={ ui->RMandarin->x(), ui->RMandarin->y() };
    coordinateConversion(XY);
    /*---------˳�����------------*/
    if( Capture(originalXY,4) && 4 !=click->getCounter()  )
    {
        ui->RMandarin->setEnabled(false);
        ui->RMandarin->hide();
    }
    click->Choose_or_Move_Judge(4);
}
void ChessBoard::on_RKing_clicked()
{
    int originalXY[2] = { ui->RKing->x(), ui->RKing->y() };
    int XY[2]={ ui->RKing->x(), ui->RKing->y() };
    coordinateConversion(XY);
    /*---------˳�����------------*/
    if( Capture(originalXY,5) && 5 !=click->getCounter()  )
    {
        ui->RKing->setEnabled(false);
        ui->RKing->hide();
    }
    click->Choose_or_Move_Judge(5);
}
void ChessBoard::on_RMandarin_2_clicked()
{
    int originalXY[2] = { ui->RMandarin_2->x(), ui->RMandarin_2->y() };
    int XY[2]={ ui->RMandarin_2->x(), ui->RMandarin_2->y() };
    coordinateConversion(XY);
    /*---------˳�����------------*/
    if( Capture(originalXY,6) && 6 !=click->getCounter()  )
    {
        ui->RMandarin_2->setEnabled(false);
        ui->RMandarin_2->hide();
    }
    click->Choose_or_Move_Judge(6);
}
void ChessBoard::on_RBishop2_clicked()
{
    int originalXY[2] = { ui->RBishop2->x(), ui->RBishop2->y() };
    int XY[2]={ ui->RBishop2->x(), ui->RBishop2->y() };
    coordinateConversion(XY);
    /*---------˳�����------------*/
    if( Capture(originalXY,7) && 7 !=click->getCounter()  )
    {
        ui->RBishop2->setEnabled(false);
        ui->RBishop2->hide();
    }
    click->Choose_or_Move_Judge(7);
}
void ChessBoard::on_RKnight2_clicked()
{
    int originalXY[2] = { ui->RKnight2->x(), ui->RKnight2->y() };
    int XY[2]={ ui->RKnight2->x(), ui->RKnight2->y() };
    coordinateConversion(XY);

    qDebug("(%d,%d)",coordinate[0],coordinate[1]);
    /*---------˳�����------------*/
    if( Capture(originalXY,8) && 8 !=click->getCounter()  )
    {
        ui->RKnight2->setEnabled(false);
        ui->RKnight2->hide();
    }
    click->Choose_or_Move_Judge(8);
}
void ChessBoard::on_RRook2_clicked()
{
    int originalXY[2] = { ui->RRook2->x(), ui->RRook2->y() };
    int XY[2]={ ui->RRook2->x(), ui->RRook2->y() };
    coordinateConversion(XY);
    /*---------˳�����------------*/
    if( Capture(originalXY,9) && 9 !=click->getCounter()  )
    {
        ui->RRook2->setEnabled(false);
        ui->RRook2->hide();
    }
    click->Choose_or_Move_Judge(9);
   /*-----------------------------*/
}
void ChessBoard::on_RCannon_clicked()
{
    int originalXY[2]={ ui->RCannon->x(), ui->RCannon->y() };
    int XY[2]={ ui->RCannon->x(), ui->RCannon->y() };
    coordinateConversion(XY);

     /**������˳�����Ҫ, ��������ͨ��class Movestatu�е�MoveStatu��ֵ�����жϲ������޸�**/
    if( Capture(originalXY,10) &&  10 != click->getCounter() )
    {
        ui->RCannon->setEnabled(false);
        ui->RCannon->hide();
    }
    click->Choose_or_Move_Judge(10);
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
     if( Capture(originalXY,11) && 11 !=click->getCounter() )
     {
         ui->RCannon2->setEnabled(false);
         ui->RCannon2->hide();
     }
     click->Choose_or_Move_Judge(11);
    /*-----------------------------*/
}
void ChessBoard::on_RPawn1_clicked()
{
    int originalXY[2] = { ui->RPawn1->x(), ui->RPawn1->y() };
    int XY[2]={ ui->RPawn1->x(), ui->RPawn1->y() };
    coordinateConversion(XY);
    /*---------˳�����------------*/
    if( Capture(originalXY,12) && 12 !=click->getCounter() )
    {
        ui->RPawn1->setEnabled(false);
        ui->RPawn1->hide();
    }
    click->Choose_or_Move_Judge(12);
}
void ChessBoard::on_RPawn2_clicked()
{
    int originalXY[2] = { ui->RPawn2->x(), ui->RPawn2->y() };
    int XY[2]={ ui->RPawn2->x(), ui->RPawn2->y() };
    coordinateConversion(XY);
    /*---------˳�����------------*/
    if( Capture(originalXY,13) && 13 !=click->getCounter() )
    {
        ui->RPawn2->setEnabled(false);
        ui->RPawn2->hide();
    }
    click->Choose_or_Move_Judge(13);
}
void ChessBoard::on_Rpawn3_clicked()
{
    int originalXY[2] = { ui->Rpawn3->x(), ui->Rpawn3->y() };
    int XY[2]={ ui->Rpawn3->x(), ui->Rpawn3->y() };
    coordinateConversion(XY);
    /*---------˳�����------------*/
    if( Capture(originalXY,14) && 14 !=click->getCounter() )
    {
        ui->Rpawn3->setEnabled(false);
        ui->Rpawn3->hide();
    }
    click->Choose_or_Move_Judge(14);
}
void ChessBoard::on_RPawn4_clicked()
{
    int originalXY[2] = { ui->RPawn4->x(), ui->RPawn4->y() };
    int XY[2]={ ui->RPawn4->x(), ui->RPawn4->y() };
    coordinateConversion(XY);
    /*---------˳�����------------*/
    if( Capture(originalXY,15) && 15 !=click->getCounter() )
    {
        ui->RPawn4->setEnabled(false);
        ui->RPawn4->hide();
    }
    click->Choose_or_Move_Judge(15);
}
void ChessBoard::on_RPawn5_clicked()
{
    int originalXY[2] = { ui->RPawn5->x() , ui->RPawn5->y()  };
    int XY[2]={ ui->RPawn5->x(), ui->RPawn5->y()  };
    coordinateConversion(XY);
    /*---------˳�����------------*/
    if( Capture(originalXY,16) && 16 !=click->getCounter() )
    {
        ui->RPawn5->setEnabled(false);
        ui->RPawn5->hide();
    }
    click->Choose_or_Move_Judge(16);
}
void ChessBoard::on_BPawn1_clicked()
{
    int originalXY[2] = { ui->BPawn1->x() , ui->BPawn1->y()  };
    int XY[2]={ ui->BPawn1->x(), ui->BPawn1->y()  };
    coordinateConversion(XY);
    /*---------˳�����------------*/
    if( Capture(originalXY,17) && 17 !=click->getCounter() )
    {
        ui->BPawn1->setEnabled(false);
        ui->BPawn1->hide();
    }
    click->Choose_or_Move_Judge(17);
}
void ChessBoard::on_BPawn2_clicked()
{
    int originalXY[2] = { ui->BPawn2->x() , ui->BPawn2->y()  };
    int XY[2]={ ui->BPawn2->x() , ui->BPawn2->y()  };
    coordinateConversion(XY);
    /*---------˳�����------------*/
    if( Capture(originalXY,18) && 18 !=click->getCounter() )
    {
        ui->BPawn2->setEnabled(false);
        ui->BPawn2->hide();
    }
    click->Choose_or_Move_Judge(18);
}
void ChessBoard::on_BPawn3_clicked()
{
    int originalXY[2] = { ui->BPawn3->x(), ui->BPawn3->y() };
    int XY[2]={ ui->BPawn3->x() , ui->BPawn3->y() };
    coordinateConversion(XY);
    /*---------˳�����------------*/
    if( Capture(originalXY,19) && 19 !=click->getCounter() )
    {
        ui->BPawn3->setEnabled(false);
        ui->BPawn3->hide();
    }
    click->Choose_or_Move_Judge(19);
}
void ChessBoard::on_BPawn4_clicked()
{
    int originalXY[2] = { ui->BPawn4->x(), ui->BPawn4->y() };
    int XY[2]={ ui->BPawn4->x() , ui->BPawn4->y() };
    coordinateConversion(XY);
    /*---------˳�����------------*/
    if( Capture(originalXY,20) && 20 !=click->getCounter() )
    {
        ui->BPawn4->setEnabled(false);
        ui->BPawn4->hide();
    }
    click->Choose_or_Move_Judge(20);
}
void ChessBoard::on_BPawn5_clicked()
{
    int originalXY[2] = { ui->BPawn5->x(), ui->BPawn5->y() };
    int XY[2]={ ui->BPawn5->x() , ui->BPawn5->y() };
    coordinateConversion(XY);
    /*---------˳�����------------*/
    if( Capture(originalXY,21) && 21 !=click->getCounter() )
    {
        ui->BPawn5->setEnabled(false);
        ui->BPawn5->hide();
    }
    click->Choose_or_Move_Judge(21);
}
void ChessBoard::on_BCannon1_clicked()
{
    int originalXY[2] = { ui->BCannon1->x(), ui->BCannon1->y() };
    int XY[2]={ ui->BCannon1->x() , ui->BCannon1->y() };
    coordinateConversion(XY);
    /*---------˳�����------------*/
    if( Capture(originalXY,22) && 22 !=click->getCounter() )
    {
        ui->BCannon1->setEnabled(false);
        ui->BCannon1->hide();
    }
    click->Choose_or_Move_Judge(22);
}
void ChessBoard::on_BCannon2_clicked()
{
    int originalXY[2] = { ui->BCannon2->x(), ui->BCannon2->y() };
    int XY[2]={ ui->BCannon2->x() , ui->BCannon2->y() };
    coordinateConversion(XY);
    /*---------˳�����------------*/
    if( Capture(originalXY,23) && 23 !=click->getCounter() )
    {
        ui->BCannon2->setEnabled(false);
        ui->BCannon2->hide();
    }
    click->Choose_or_Move_Judge(23);
}
void ChessBoard::on_BRook1_clicked()
{

    int originalXY[2] = { ui->BRook1->x(), ui->BRook1->y() };
    int XY[2]={ ui->BRook1->x() , ui->BRook1->y() };
    coordinateConversion(XY);
    /*---------˳�����------------*/
    if( Capture(originalXY,24) && 24 !=click->getCounter() )
    {
        ui->BRook1->setEnabled(false);
        ui->BRook1->hide();
    }
    click->Choose_or_Move_Judge(24);
}
void ChessBoard::on_BKnight1_clicked()
{
    int originalXY[2] = { ui->BKnight1->x(), ui->BKnight1->y() };
    int XY[2]={ ui->BKnight1->x() , ui->BKnight1->y() };
    coordinateConversion(XY);
    /*---------˳�����------------*/
    if( Capture(originalXY,25) && 25 !=click->getCounter() )
    {
        ui->BKnight1->setEnabled(false);
        ui->BKnight1->hide();
    }
    click->Choose_or_Move_Judge(25);
}
void ChessBoard::on_BBishop1_clicked()
{
    int originalXY[2] = { ui->BBishop1->x(), ui->BBishop1->y() };
    int XY[2]={ ui->BBishop1->x() , ui->BBishop1->y() };
    coordinateConversion(XY);
    /*---------˳�����------------*/
    if( Capture(originalXY,26) && 26 !=click->getCounter() )
    {
        ui->BBishop1->setEnabled(false);
        ui->BBishop1->hide();
    }
    click->Choose_or_Move_Judge(26);
}
void ChessBoard::on_BMandarin_clicked()
{
    int originalXY[2] = { ui->BMandarin->x(), ui->BMandarin->y() };
    int XY[2]={ ui->BMandarin->x() , ui->BMandarin->y() };
    coordinateConversion(XY);
    /*---------˳�����------------*/
    if( Capture(originalXY,27) && 27 !=click->getCounter() )
    {
        ui->BMandarin->setEnabled(false);
        ui->BMandarin->hide();
    }
    click->Choose_or_Move_Judge(27);
}
void ChessBoard::on_BKing_clicked()
{

    int originalXY[2] = { ui->BKing->x(), ui->BKing->y() };
    int XY[2]={ ui->BKing->x() , ui->BKing->y() };
    coordinateConversion(XY);
    /*---------˳�����------------*/
    if( Capture(originalXY,28) && 28 !=click->getCounter() )
    {
        ui->BKing->setEnabled(false);
        ui->BKing->hide();
    }
    click->Choose_or_Move_Judge(28);
}
void ChessBoard::on_BMandarin2_clicked()
{
    int originalXY[2] = { ui->BMandarin2->x(), ui->BMandarin2->y() };
    int XY[2]={ ui->BMandarin2->x() , ui->BMandarin2->y() };
    coordinateConversion(XY);
    /*---------˳�����------------*/
    if( Capture(originalXY,29) && 29 !=click->getCounter() )
    {
        ui->BMandarin2->setEnabled(false);
        ui->BMandarin2->hide();
    }
    click->Choose_or_Move_Judge(29);
}
void ChessBoard::on_BBishop2_clicked()
{
    int originalXY[2] = { ui->BBishop2->x(), ui->BBishop2->y() };
    int XY[2]={ ui->BBishop2->x() , ui->BBishop2->y() };
    coordinateConversion(XY);
    /*---------˳�����------------*/
    if( Capture(originalXY,30) && 30 !=click->getCounter() )
    {
        ui->BBishop2->setEnabled(false);
        ui->BBishop2->hide();
    }
    click->Choose_or_Move_Judge(30);
}
void ChessBoard::on_BKnight2_clicked()
{
    int originalXY[2] = { ui->BKnight2->x(), ui->BKnight2->y() };
    int XY[2]={ ui->BKnight2->x() , ui->BKnight2->y() };
    coordinateConversion(XY);
    /*---------˳�����------------*/
    if( Capture(originalXY,31) && 31 !=click->getCounter() )
    {
        ui->BKnight2->setEnabled(false);
        ui->BKnight2->hide();
    }
    click->Choose_or_Move_Judge(31);
}
void ChessBoard::on_BRook2_clicked()
{
    int originalXY[2] = { ui->BRook2->x(), ui->BRook2->y() };
    int XY[2]={ ui->BRook2->x() , ui->BRook2->y() };
    coordinateConversion(XY);
    /*---------˳�����------------*/
    if( Capture(originalXY,32) && 32 !=click->getCounter() )
    {
        ui->BRook2->setEnabled(false);
        ui->BRook2->hide();
    }
    click->Choose_or_Move_Judge(32);
}
/*****************************************�ۺ�������**************************************************/


/*************����û�����ⲿ��**********************/
void ChessBoard::boardCoordinateConversion(int *des)            //���Է��ƶ�����������ת��Ϊ���Լ�����������ϵ��Ӧ������
{
    des[0] = 8-des[0];
    des[1] = 9-des[1];
}

void ChessBoard::coordinateConversion(int *XY)
{
    int Xoffset=25, Yoffset=25;
    int originalPoint[2]={395,250};                 //ԭ����������
    int h=50, w=50;                                     //С����ĳ���
    XY[0]-=originalPoint[0];
    XY[1]-=originalPoint[1];
    if(XY[1]>h*4)                                               //���ǳ��ӿ�� ����ƫ��  ������Դ�����뷽��ͬ��
       XY[1]-=0;
    coordinate[0]=(XY[0]+Xoffset)/w;                     //ƫ��һ��λ��ʹ�������㸽�����򼴿�p�ж�Ϊ����ڽ��洦
    coordinate[1]=(XY[1]+Yoffset)/h;
}

void ChessBoard::getConversionCoordinate(int *point)
{
     point[0]=coordinate[0];
     point[1]=coordinate[1];
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
//��������Ĵ������û��ʹ�� ���Կ���ȥ��
//�ú�������Ϊ�ı����ӵ�״̬
void MoveRecord::Choose_or_Move_Judge(int count)
{
    if(     MoveStatu == false  && doubleStatu ==false   )
    {
        qDebug()<<"Cancel movement or capture";
        MoveStatu  =  true;
    }
    else
    {
        qDebug()<<"The Button Is Ready To Move! ";
         MoveStatu = doubleStatu =  false;
    }
}

int *MoveRecord::updateClickCoordinate(int *XY)
{
//    qDebug()<<"Update point"<<XY[0]<<","<<XY[1]<<endl;
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





