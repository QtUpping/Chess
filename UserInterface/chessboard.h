#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QMainWindow>
#include "ChessController.h"
#include "client.h"
#include <QPushButton>
#include "music_player.h"
#include "logindlg.h"

class ChessController;
namespace Ui {
class ChessBoard;
}

class ChessBoard : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChessBoard(Client* client, QWidget *parent = 0);
    ~ChessBoard();
    void mousePressEvent(QMouseEvent *e);
    //每次鼠标点击后修改coordinate的值(初始为0,0),通过getCurCoordinate提供给外部
    void getConversionCoordinate(int *point);

    //修改 每次进行有效点击是将坐标提供给外部  点击鼠标或者按钮均更新坐标 //或者改为每次移动之后更新坐标
    void coordinateConversion(int *XY);

//    bool validClick(int *XY);         //判断点击是否在棋盘内  暂时无定义
    bool Capture(int *XY, int count);   //通过返回值控制被吃棋子失效

     //将对方移动的棋盘坐标转化为与自己棋盘上坐标系对应的坐标
    void boardCoordinateConversion(int *des);
    //在发送坐标的时候调用

    void boardToReal(int *point);

private slots:
    void on_RCannon_clicked();
    void on_RCannon2_clicked();
    void on_RRook_clicked();
    void on_RRook2_clicked();
    void on_RKnight_clicked();
    void on_RBIshop_clicked();
    void on_RMandarin_clicked();
    void on_RKing_clicked();
    void on_RMandarin_2_clicked();
    void on_RBishop2_clicked();
    void on_RKnight2_clicked();
    void on_RPawn1_clicked();
    void on_RPawn2_clicked();
    void on_Rpawn3_clicked();
    void on_RPawn4_clicked();
    void on_RPawn5_clicked();
    void on_BPawn1_clicked();
    void on_BPawn2_clicked();
    void on_BPawn3_clicked();
    void on_BPawn4_clicked();
    void on_BPawn5_clicked();
    void on_BRook1_clicked();
    void on_BKnight1_clicked();
    void on_BBishop1_clicked();
    void on_BMandarin_clicked();
    void on_BKing_clicked();
    void on_BRook2_clicked();
    void on_BCannon1_clicked();
    void on_BCannon2_clicked();
    void on_BMandarin2_clicked();
    void on_BBishop2_clicked();
    void on_BKnight2_clicked();

//    void noArgTrans();
    void react(QString chessPoint);

    void on_sendButton_clicked();

    void on_withdraw_clicked();

    void on_Play_clicked();


    void on_pushButton_clicked();

    void on_surrender_clicked();

signals:
    void clicked();
public slots:
    void mousePressEventSlot();

private:
    Client* myClient;
    Ui::ChessBoard *ui;
    int coordinate[2];              //记录坐标  在mousePressEvent更改  getCurCoordinate提供给类外使用
    int oldPoint[2];                  //前一点坐标  暂时还没用上
    void convertFromQSToChar(QString str, char* charArr);
    void convertFromCharToIntArr(char* charArr, int* intArr);
    void convertFromIntToChar(int* intArr, char* charArr);
    QString convertFromCharToQS(char* charArr);
    void convertFromChessToReal(int* des);
    int myCamp;
    logindlg* login;
    int status;
    music_player * m;
    QPushButton * findBtn;
    int QRCode;
};

class MoveRecord
{
private:
                                                         //*************两个bool值均为假时为可移动状态(选中状态),  等待下一次点击时控制按钮移动********************//
    bool MoveStatu;                          //记录状态 初始为false 第一次点击(在choose_or_move中使用)改为true 记为选中, 第二次改为false 记为移动 奇数次选中 偶数次移动
    bool doubleStatu;                        //只用一个变量  会出现可移动状态下按钮可以多次移动的情况  加入doubleStatu初始为真   只在点击按钮时改变, 达到选中后只能移动一次按钮的目的
    int MovePieceCounter;              //记录处于可移动状态棋子的序号
    int lastMovePieceCounter;              //记录被吃棋子的序号
public:
    MoveRecord();
    int getLastCounter();
    void setLastCounter(int count);
    void setCounter(int count);
    int getCounter();
    void setMoveStatu();
    void resetMoveStatu();
    void setDoubleStatu();
    void setStatu();
    void resetStatuT();                                       //用于在鼠标点击事件中将DBS设为真
    bool getDBStatu();
    bool getStatu();                                          //提供MoveStatu状态的接口
    void Choose_or_Move_Judge(int count);    //改变状态函数, 每次鼠标点击按钮均更新状态
};

#endif // CHESSBOARD_H


