#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QMainWindow>
#include "ChessController.h"
#include "client.h"

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
    //ÿ����������޸�coordinate��ֵ(��ʼΪ0,0),ͨ��getCurCoordinate�ṩ���ⲿ
    void getConversionCoordinate(int *point);

    //�޸� ÿ�ν�����Ч����ǽ������ṩ���ⲿ  ��������߰�ť���������� //���߸�Ϊÿ���ƶ�֮���������
    void coordinateConversion(int *XY);

//    bool validClick(int *XY);         //�жϵ���Ƿ���������  ��ʱ�޶���
    bool Capture(int *XY, int count);   //ͨ������ֵ���Ʊ�������ʧЧ

     //���Է��ƶ�����������ת��Ϊ���Լ�����������ϵ��Ӧ������
    void boardCoordinateConversion(int *des);
    //�ڷ��������ʱ�����

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

private:
    Client* myClient;
    Ui::ChessBoard *ui;
    int coordinate[2];              //��¼����  ��mousePressEvent����  getCurCoordinate�ṩ������ʹ��
    int oldPoint[2];                  //ǰһ������  ��ʱ��û����
    void convertFromQSToChar(QString str, char* charArr);
    void convertFromCharToIntArr(char* charArr, int* intArr);
    void convertFromIntToChar(int* intArr, char* charArr);
    QString convertFromCharToQS(char* charArr);
    void convertFromChessToReal(int* des);
};

/*------����ʵ�ֹ������Ƶ���һ���ļ���--------------*/
class MoveRecord
{
private:
    int Point[2];
                                                                    //*************����boolֵ��Ϊ��ʱΪ���ƶ�״̬(ѡ��״̬),  �ȴ���һ�ε��ʱ���ư�ť�ƶ�********************//
    bool MoveStatu;                                     //��¼״̬ ��ʼΪfalse ��һ�ε��(��choose_or_move��ʹ��)��Ϊtrue ��Ϊѡ��, �ڶ��θ�Ϊfalse ��Ϊ�ƶ� ������ѡ�� ż�����ƶ�
    bool doubleStatu;                                   //ֻ��һ���������  ����ֿ��ƶ�״̬�°�ť���Զ���ƶ������  ���Ǽ�һ������  ֻ�ڵ����ťʱ�ı� doubleStatu��ʼΪ�� �Կ��Ƶ�һ�ε���յز����ƶ�
    int MovePieceCounter;                            //��¼�ڼ������Ӵ��ڿ��ƶ�״̬
public:
    MoveRecord();
    void setCounter(int count);
    int getCounter();
    void resetStatuT();                                       //������������¼��н�DBS��Ϊ��
    bool getDBStatu();
    bool getStatu();                                          //�ṩMoveStatu״̬�Ľӿ�
    void Choose_or_Move_Judge(int count);    //�ı�״̬����, ÿ���������ť������״̬
    int *updateClickCoordinate(int *XY);        //��������point   Ȼ��point������û������ ��������coordinate�����ظ�
};

#endif // CHESSBOARD_H


