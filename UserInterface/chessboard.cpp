#include "chessboard.h"
#include "ui_chessboard.h"
#include <QPushButton>
#include <QMouseEvent>
#include <QDebug>
#include "AllChess.h"
#include "Chessman.h"
#include <string>
#include <QSound>
#include <QMessageBox>

static MoveRecord *click = new MoveRecord;      //创建一个MoveRecord的类对象,  通过指针调用choose_or_move函数
static QPushButton *ChessmanButton[32] = {0};    //创建一个PushButton指针存放所有按钮地址

static ChessController *tmp = new ChessController;


ChessBoard::ChessBoard(Client* client, QWidget *parent) :
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
    myClient = client;
    connect(myClient, SIGNAL(sendPoint(QString)), this, SLOT(react(QString)));

    m=new music_player;
    QIcon ico(":/ChessImages/Images/play.png");
    findBtn=new QPushButton(this);
    findBtn->setIcon(ico);
    findBtn->setFlat(true);
    findBtn->raise();
    status=0;
    m->Play_stop();
    connect(findBtn,SIGNAL(clicked()),this,SLOT(mousePressEventSlot()));
    login = new logindlg(myClient, this);
    login->setModal(true);
    login->show();
    QRCode = 0;
    ui->QRCodeLabel->hide();
    ui->Play->setEnabled(false);
}


void ChessBoard::mousePressEventSlot()
{
    if(status==1)
    {
        m->Play_stop();
        findBtn->setIcon(QIcon(":/ChessImages/Images/play.png"));
        status=0;
    }
    else
    {
        m->Play_in_loop();
        findBtn->setIcon(QIcon(":/ChessImages/Images/pause.png"));
        status=1;
    }
}

QString ChessBoard::convertFromCharToQS(char *charArr)
{
    QString str = QString(QLatin1String(charArr));
    return str;
}

void ChessBoard::convertFromChessToReal(int *des)

{
    int ori[2]={395,250};
        int h=50,w=50;
        des[0]=ori[0]+w*des[0] - 20;
        des[1]=ori[1]+h*des[1] - 20;
}

void ChessBoard::convertFromIntToChar(int *intArr, char *charArr)
{
    sprintf(charArr, "%d%d%d%d", intArr[0], intArr[1], intArr[2], intArr[3]);
}

void ChessBoard::convertFromQSToChar(QString str, char* charArr)
{
    QByteArray tmp = str.toLatin1();
    strcpy(charArr, tmp.data());
}

void ChessBoard::convertFromCharToIntArr(char *charArr, int *intArr)
{
    char* tmp = charArr;
    int i = 0;
    while(*tmp)
    {
        if(*tmp>=48 && *tmp <= 57)
        {
            intArr[i] = *tmp - 48;
            i++;
        }
        tmp++;
    }
}

void ChessBoard::react(QString chessPoint)
{
    if(chessPoint.startsWith("point"))
    {
        char tmpCh[5] = {0};
        int Point[4], old[2] = {0}, des[2] = {0};
        int posInArr = 0, oldPosInArr = 0;
        Chessman* tmpChessman = NULL;
        Chessman* enemy = NULL;
        QString str = chessPoint.mid(5);
        convertFromQSToChar(str, tmpCh);
        convertFromCharToIntArr(tmpCh, Point);
        old[0] = Point[0];
        old[1] = Point[1];
        des[0] = Point[2];
        des[1] = Point[3];
        enemy = tmp->whetherExist(des);

        click->setDoubleStatu();
        if(enemy == NULL)
        {
            tmpChessman = tmp->whetherExist(old);
            tmpChessman->setPoint(des, tmp);
            posInArr = tmp->posInArr(des);
            convertFromChessToReal(des);
            ChessmanButton[posInArr]->move(des[0], des[1]);
        }
        else
        {
               Chessman* oldChessman = tmp->whetherExist(old);
               Chessman* desChessman = tmp->whetherExist(des);
               oldPosInArr = tmp->posInArr(old);
               posInArr = tmp->posInArr(des);
               oldChessman->setPoint(des, tmp);
               ChessmanButton[posInArr]->hide();
               ChessmanButton[posInArr]->setEnabled(false);

               if(posInArr == 4 )
               {
                   QMessageBox lose(QMessageBox::Information, tr("游戏结束"), tr("你输了!"), QMessageBox::Yes);
                   if(lose.exec() == QMessageBox::Yes)
                   {
                       QByteArray outcome = "outcome0";
                       myClient->sendMesg(outcome);
                   }
               }
               int tmpPoint[2] = {-1, -1};
               desChessman->forceSetPoint(tmpPoint);
               convertFromChessToReal(des);
               ChessmanButton[oldPosInArr]->move(des[0], des[1]);
        }
    }
    else if(chessPoint.startsWith("camp"))
    {
        if(chessPoint.mid(4,1).toInt() == 0)
        {
            myCamp = 0;
            click->setDoubleStatu();
            QIcon R1( ":/ChessImages/Images/RookR.GIF" );
            ChessmanButton[0]->setIcon(R1);
            ChessmanButton[8]->setIcon(R1);
            QIcon R2( ":/ChessImages/Images/KnightR.GIF" );
            ChessmanButton[1]->setIcon(R2);
            ChessmanButton[7]->setIcon(R2);
            QIcon R3( ":/ChessImages/Images/RB.GIF" );
            ChessmanButton[2]->setIcon(R3);
            ChessmanButton[6]->setIcon(R3);
            QIcon R4( ":/ChessImages/Images/MandarinR.GIF" );
            ChessmanButton[3]->setIcon(R4);
            ChessmanButton[5]->setIcon(R4);
            QIcon R5( ":/ChessImages/Images/KingR.GIF" );
            ChessmanButton[4]->setIcon(R5);
            QIcon R6( ":/ChessImages/Images/CannonR.GIF" );
            ChessmanButton[9]->setIcon(R6);
            ChessmanButton[10]->setIcon(R6);
            QIcon R7( ":/ChessImages/Images/PawnR.GIF" );
            for(int i=11; i<16;++i)
            {
                ChessmanButton[i]->setIcon(R7);
            }
            QIcon B1(":/ChessImages/Images/Rook.GIF");
            ChessmanButton[23]->setIcon(B1);
            ChessmanButton[31]->setIcon(B1);
            QIcon B2(":/ChessImages/Images/Knight.GIF");
            ChessmanButton[24]->setIcon(B2);
            ChessmanButton[30]->setIcon(B2);
            QIcon B3(":/ChessImages/Images/BishopB.GIF");
            ChessmanButton[25]->setIcon(B3);
            ChessmanButton[29]->setIcon(B3);
            QIcon B4(":/ChessImages/Images/Mandarin.GIF");
            ChessmanButton[26]->setIcon(B4);
            ChessmanButton[28]->setIcon(B4);
            QIcon B5(":/ChessImages/Images/King.GIF");
            ChessmanButton[27]->setIcon(B5);
            QIcon B6(":/ChessImages/Images/Cannon.GIF");
            ChessmanButton[21]->setIcon(B6);
            ChessmanButton[22]->setIcon(B6);
            QIcon B7(":/ChessImages/Images/pawn.GIF");
            for(int i = 16; i<21;++i)
            {
                ChessmanButton[i]->setIcon(B7);
            }
        }
        else
        {
            myCamp = 1;
            QIcon R1( ":/ChessImages/Images/RookR.GIF" );
            ChessmanButton[23]->setIcon(R1);
            ChessmanButton[31]->setIcon(R1);
            QIcon R2( ":/ChessImages/Images/KnightR.GIF" );
            ChessmanButton[24]->setIcon(R2);
            ChessmanButton[30]->setIcon(R2);
            QIcon R3( ":/ChessImages/Images/RB.GIF" );
            ChessmanButton[25]->setIcon(R3);
            ChessmanButton[29]->setIcon(R3);
            QIcon R4( ":/ChessImages/Images/MandarinR.GIF" );
            ChessmanButton[26]->setIcon(R4);
            ChessmanButton[28]->setIcon(R4);
            QIcon R5( ":/ChessImages/Images/KingR.GIF" );
            ChessmanButton[27]->setIcon(R5);
            QIcon R6( ":/ChessImages/Images/CannonR.GIF" );
            ChessmanButton[21]->setIcon(R6);
            ChessmanButton[22]->setIcon(R6);
            QIcon R7( ":/ChessImages/Images/PawnR.GIF" );
            for(int i=16; i<21;++i)
            {
                ChessmanButton[i]->setIcon(R7);
            }
            QIcon B1(":/ChessImages/Images/Rook.GIF");
            ChessmanButton[0]->setIcon(B1);
            ChessmanButton[8]->setIcon(B1);
            QIcon B2(":/ChessImages/Images/Knight.GIF");
            ChessmanButton[1]->setIcon(B2);
            ChessmanButton[7]->setIcon(B2);
            QIcon B3(":/ChessImages/Images/BishopB.GIF");
            ChessmanButton[2]->setIcon(B3);
            ChessmanButton[6]->setIcon(B3);
            QIcon B4(":/ChessImages/Images/Mandarin.GIF");
            ChessmanButton[3]->setIcon(B4);
            ChessmanButton[5]->setIcon(B4);
            QIcon B5(":/ChessImages/Images/King.GIF");
            ChessmanButton[4]->setIcon(B5);
            QIcon B6(":/ChessImages/Images/Cannon.GIF");
            ChessmanButton[9]->setIcon(B6);
            ChessmanButton[10]->setIcon(B6);
            QIcon B7(":/ChessImages/Images/pawn.GIF");
            for(int i = 11; i<16;++i)
            {
                ChessmanButton[i]->setIcon(B7);
            }
        }
        ui->Play->hide();
        ui->Play->setEnabled(false);
        int do1, do2;
        do1 = chessPoint.indexOf(",");
        do2 = chessPoint.indexOf(",", do1+1);
        QString account = chessPoint.mid(5, do1-5);
        QString win = chessPoint.mid(do1+1, do2-do1-1);
        QString lose = chessPoint.mid(do2+1);
        ui->theName->setText(account);
        ui->theWin->setText(win);
        ui->theLose->setText(lose);
    }
    else if(chessPoint.startsWith("account"))
    {
        if(chessPoint.mid(7,1).toInt() == 0)
                {
                    login = new logindlg(myClient, this);
                    login->setModal(true);
                    login->show();
                }
        else
        {
            int do1, do2, do3;
            do1 = chessPoint.indexOf(",");
            do2 = chessPoint.indexOf(",", do1+1);
            do3 = chessPoint.indexOf(",", do2+1);
            QString account = chessPoint.mid(8, do1-8);
            QString win = chessPoint.mid(do1+1, do2-do1-1);
            QString lose;
            if(do3 != -1)
            {
                lose = chessPoint.mid(do2+1, do3-do2-1);
            }
            else
                lose = chessPoint.mid(do2+1);
            ui->myName->setText(account);
            ui->myWin->setText(win);
            ui->myLose->setText(lose);
            ui->Play->setEnabled(true);
            if(do3 != -1)
            {
                QMessageBox play(QMessageBox::Information,tr("提示"),tr("匹配成功，请开始游戏"),QMessageBox::Yes);
                if(play.exec() == QMessageBox::Yes);
            }
        }
    }
    else if(chessPoint.startsWith("conversation"))
    {
        QString mesFromOth = chessPoint.mid(12);
        ui->MesRecord->append(mesFromOth);
    }
    else if(chessPoint.startsWith(",start"))
    {
        QMessageBox play(QMessageBox::Information,tr("提示"),tr("匹配成功，请开始游戏"),QMessageBox::Yes);
        if(play.exec() == QMessageBox::Yes);
    }
    else if(chessPoint.startsWith("surrender"))
    {
        QMessageBox box(QMessageBox::Information,tr("对方认输"),tr("亲，对方下不过你，认输啦(〃￣ω￣〃)"),QMessageBox::Yes);
        if(box.exec() == QMessageBox::Yes);
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
    if(  (originalXYcur[0]>325 && originalXYcur[0]<830) && (originalXYcur[1]>223 && originalXYcur[1]<735)  )  //点击在棋盘内
    {
        if( click->getStatu() == false && click->getDBStatu() == false)
        {
           int *lastpoint = tmp->piece[ click->getCounter()-1 ]->getPoint();
            if( tmp->move(lastpoint ,coordinate)  )             //若移动符合规则, 则本句先更新棋子对象的坐标并返回真 , 进入if后开始移动按钮坐标
            {
                char charArr[10] = "point";
                QString mes;
                Chessman* tmpChessman = NULL;
                tmpChessman = tmp->whetherExist(lastpoint);
                int newArr[5]={ tmpChessman->getOldPoint()[0], tmpChessman->getOldPoint()[1], coordinate[0],  coordinate[1] };
                boardCoordinateConversion(newArr);
                charArr[5] = newArr[0] + 48;
                charArr[6] = newArr[1] + 48;
                charArr[7] = newArr[2] + 48;
                charArr[8] = newArr[3] + 48;
                mes = convertFromCharToQS(charArr);
                QByteArray qba = mes.toLatin1();
                myClient->sendMesg(qba);
                int realPoint[2];
                getConversionCoordinate(realPoint);
                boardToReal(realPoint);
                ChessmanButton[ click->getCounter()-1 ]->move(realPoint[0], realPoint[1]);

                QSound::play("luozi.wav");
                click->resetStatuT();
            }
        }
        click->resetMoveStatu();
    }
}
//控制上一次选中按钮移动到本次点击按钮位置
bool ChessBoard::Capture(int *XY,int count)
{
    if(  click->getStatu() == true  )
    {
        if(count >= 16)
            return false;
         click->setCounter(count);
         return false;
    }
    else if(click->getDBStatu() == false)
    {
        int *lastpoint = tmp->piece[ click->getCounter()-1 ]->getPoint();
        if( tmp->move( lastpoint, coordinate )  )
        {
            char charArr[10] = "point";
            QString mes;
            Chessman* tmpChessman = NULL;
            tmpChessman = tmp->whetherExist(lastpoint);
            int newArr[5]={ tmpChessman->getOldPoint()[0], tmpChessman->getOldPoint()[1], coordinate[0],  coordinate[1] };
            boardCoordinateConversion(newArr);
            charArr[5] = newArr[0] + 48;
            charArr[6] = newArr[1] + 48;
            charArr[7] = newArr[2] + 48;
            charArr[8] = newArr[3] + 48;
            mes = convertFromCharToQS(charArr);
            myClient->sendMesg(mes);
            click->setLastCounter(count);
            ChessmanButton[click->getCounter()-1]->move(XY[0], XY[1]);
            QSound::play("chizi.wav");
            return true;
        }
        else
            return false;
    }
    else
        return false;
}
/**********************************按钮槽函数(**************)*************************************************/

void ChessBoard::on_Play_clicked()      //开始游戏 初始化棋盘
{
    char campMesg[5] = "camp";
    QString QcampMesg = convertFromCharToQS(campMesg);
    myClient->sendMesg(QcampMesg);
   ui->Play->hide();
   ui->Play->setEnabled(false);
}
/********************************** 吃子(走到另一个按钮并使其失效)*******************************************/
void ChessBoard::on_RRook_clicked()
{
    int originalXY[2] = { ui->RRook->x(), ui->RRook->y() };
    int XY[2]={ ui->RRook->x() , ui->RRook->y() };
    coordinateConversion(XY);
    /*---------顺序别乱------------*/
    if( Capture(originalXY,1) && 1 !=click->getCounter()  )
    {
        ui->RRook->setEnabled(false);
        ui->RRook->hide();
    }
    click->Choose_or_Move_Judge(1);
}
void ChessBoard::on_RKnight_clicked()
{
    int originalXY[2] = { ui->RKnight->x(), ui->RKnight->y() };
    int XY[2]={ ui->RKnight->x(), ui->RKnight->y() };
    coordinateConversion(XY);

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
    /*---------顺序别乱------------*/
    if( Capture(originalXY,5) && 5 !=click->getCounter()  )
    {
        ui->RKing->setEnabled(false);
        ui->RKing->hide();

        QMessageBox lose(QMessageBox::Information, "Game over!", "You lose!", QMessageBox::Yes);
        if(lose.exec() == QMessageBox::Yes);
    }
    click->Choose_or_Move_Judge(5);
}
void ChessBoard::on_RMandarin_2_clicked()
{
    int originalXY[2] = { ui->RMandarin_2->x(), ui->RMandarin_2->y() };
    int XY[2]={ ui->RMandarin_2->x(), ui->RMandarin_2->y() };
    coordinateConversion(XY);
    /*---------顺序别乱------------*/
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
    /*---------顺序别乱------------*/
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

    /*---------顺序别乱------------*/
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
    /*---------顺序别乱------------*/
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

     /**这两行顺序很重要, 两个函数通过class Movestatu中的MoveStatu的值进行判断并进行修改**/
    if( Capture(originalXY,10) &&  10 != click->getCounter() )
    {
        ui->RCannon->setEnabled(false);
        ui->RCannon->hide();
    }
    click->Choose_or_Move_Judge(10);
}
void ChessBoard::on_RCannon2_clicked()
{
     int originalXY[2] = { ui->RCannon2->x(), ui->RCannon2->y() };
     int XY[2]={ ui->RCannon2->x(), ui->RCannon2->y() };
     coordinateConversion(XY);
     /*---------顺序别乱------------*/
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
    /*---------顺序别乱------------*/
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
    /*---------顺序别乱------------*/
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
    /*---------顺序别乱------------*/
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
    /*---------顺序别乱------------*/
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
    /*---------顺序别乱------------*/
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
    /*---------顺序别乱------------*/
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
    /*---------顺序别乱------------*/
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
    /*---------顺序别乱------------*/
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
    /*---------顺序别乱------------*/
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
    /*---------顺序别乱------------*/
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
    /*---------顺序别乱------------*/
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
    /*---------顺序别乱------------*/
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
    /*---------顺序别乱------------*/
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
    /*---------顺序别乱------------*/
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
    /*---------顺序别乱------------*/
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
    /*---------顺序别乱------------*/
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
    if( Capture(originalXY,28) && 28 !=click->getCounter() )
    {
        ui->BKing->setEnabled(false);
        ui->BKing->hide();

        QMessageBox victory(QMessageBox::Information, tr("游戏结束!"), tr("你赢了!"), QMessageBox::Yes);
        if(victory.exec() == QMessageBox::Yes)
        {
            QByteArray outcome = "outcome1";
            myClient->sendMesg(outcome);
        }

    }
    click->Choose_or_Move_Judge(28);
}
void ChessBoard::on_BMandarin2_clicked()
{
    int originalXY[2] = { ui->BMandarin2->x(), ui->BMandarin2->y() };
    int XY[2]={ ui->BMandarin2->x() , ui->BMandarin2->y() };
    coordinateConversion(XY);
    /*---------顺序别乱------------*/
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
    /*---------顺序别乱------------*/
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
    /*---------顺序别乱------------*/
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
    /*---------顺序别乱------------*/
    if( Capture(originalXY,32) && 32 !=click->getCounter() )
    {
        ui->BRook2->setEnabled(false);
        ui->BRook2->hide();
    }
    click->Choose_or_Move_Judge(32);
}

void ChessBoard::on_sendButton_clicked()
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("hh:mm:ss");
    QString mesForShow = str+"\n"+ui->textEdit->toPlainText();
    QString mesForSend = "conversation"+mesForShow;
    ui->MesRecord->append(mesForShow);
    ui->textEdit->clear();
    myClient->sendMesg(mesForSend);
}


void ChessBoard::on_withdraw_clicked()
{

    if( click->getCounter() == click->getLastCounter() )                        //仅移动 没吃子
    {
        int *lastpoint=tmp->piece[ click->getCounter()-1 ]->getOldPoint();   //获取当前移动棋子的序号
        tmp->piece[ click->getCounter()-1 ]->forceSetPoint( lastpoint );
        boardToReal(lastpoint);
        ChessmanButton[ click->getCounter()-1 ]->move( lastpoint[0],lastpoint[1] );
    }
    else                        //吃子
    {
        ChessmanButton[ click->getLastCounter()-1]->show();
        ChessmanButton[ click->getLastCounter()-1]->setEnabled(true);
        int *lastpoint=tmp->piece[ click->getCounter()-1 ]->getOldPoint();
        int *pointOfHiddenP=tmp->piece[ click->getLastCounter()-1 ]->getOldPoint();
        tmp->piece[ click->getCounter()-1 ]->forceSetPoint( lastpoint );
        tmp->piece[ click->getLastCounter()-1 ]->forceSetPoint( pointOfHiddenP   );
        boardToReal(lastpoint);
        ChessmanButton[ click->getCounter()-1 ]->move( lastpoint[0],lastpoint[1] );
    }
}

/*****************************************槽函数部分**************************************************/


/*************基本没有问题部分**********************/
void ChessBoard::boardCoordinateConversion(int *des)            //将对方移动的棋盘坐标转化为与自己棋盘上坐标系对应的坐标
{
    des[0] = 8-des[0];
    des[1] = 9-des[1];
    des[2] = 8-des[2];
    des[3] = 9-des[3];
}

void ChessBoard::boardToReal(int *point)
{
    int w=50,h=50;
    int ori[2]={398,250};                   //原点坐标
    point[0] = ori[0]+point[0]*w-20;
    point[1] = ori[1]+point[1]*h-20;
}

void ChessBoard::coordinateConversion(int *XY)
{
    int Xoffset=25, Yoffset=25;
    int originalPoint[2]={395,250};                 //原点像素坐标
    int h=50, w=50;                                     //小方格的长宽
    XY[0]-=originalPoint[0];
    XY[1]-=originalPoint[1];
    if(XY[1]>h*4)                                               //考虑楚河宽度 向上偏移  本次资源楚河与方格同宽
       XY[1]-=0;
    coordinate[0]=(XY[0]+Xoffset)/w;                     //偏移一定位置使点击交叉点附近区域即可p判断为点击在交叉处
    coordinate[1]=(XY[1]+Yoffset)/h;
}

void ChessBoard::getConversionCoordinate(int *point)
{
     point[0]=coordinate[0];
     point[1]=coordinate[1];
}
/**********基本没有问题部分**************************/


/*------------实现功能后移到另一个文件中----------------*/
MoveRecord::MoveRecord():MoveStatu(true), doubleStatu(true),MovePieceCounter(0),lastMovePieceCounter(0)
{

}
void MoveRecord::setCounter(int count)
{
    MovePieceCounter = count;
}

int MoveRecord::getLastCounter()
{
    return lastMovePieceCounter;
}

void MoveRecord::setLastCounter(int count)
{
    lastMovePieceCounter=count;
}

int MoveRecord::getCounter()
{
    return MovePieceCounter;
}

void MoveRecord::setMoveStatu()
{
    doubleStatu = false;
}

void MoveRecord::resetMoveStatu()
{
    MoveStatu = true;
}

void MoveRecord::setDoubleStatu()
{
    doubleStatu = false;
}

void MoveRecord::setStatu()
{
        MoveStatu = doubleStatu = false;
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
//这个函数的传入参数没有使用 可以考虑去掉
//该函数功能为改变棋子的状态
void MoveRecord::Choose_or_Move_Judge(int count)
{
    if(     MoveStatu == false  && doubleStatu ==false && count == click->getCounter() )
    {
        MoveStatu  =  true;
    }
    else if( (MoveStatu == false  && doubleStatu ==false) && count != click->getCounter() )
    {
          MoveStatu = true;
    }
    else
    {
         MoveStatu = false;
    }
}
/*--------------------------------------------------------*/



void ChessBoard::on_pushButton_clicked()
{
    QRCode = QRCode==0?1:0;
    if(QRCode)
        ui->QRCodeLabel->show();
    else
        ui->QRCodeLabel->hide();
}

void ChessBoard::on_surrender_clicked()
{
    QMessageBox box(QMessageBox::Information,tr("认输"),tr("亲，您真的要认输么QAQ?"),QMessageBox::Yes|QMessageBox::No);
     if(box.exec() == QMessageBox::Yes)
     {
         QByteArray surrender = "surrender";
         myClient->sendMesg(surrender);
     }
}
