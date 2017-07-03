#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QMainWindow>

namespace Ui {
class ChessBoard;
}

class ChessBoard : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChessBoard(QWidget *parent = 0);
    ~ChessBoard();
    void mousePressEvent(QMouseEvent *e);
    //ÿ����������޸�coordinate��ֵ(��ʼΪ0,0),ͨ��getCurCoordinate�ṩ���ⲿ
    int *getConversionCoordinate(int *point);
    //�޸� ÿ�ν�����Ч����ǽ������ṩ���ⲿ
    void coordinateConversion(int *XY);
//    bool validClick(int *XY);         //�жϵ���Ƿ���������  ��ʱ�޶���
    bool Capture(int *XY, int count);   //ͨ������ֵ���Ʊ�������ʧЧ

private slots:
    void on_RCannon_clicked();
    void on_RCannon2_clicked();
    void on_RRook_clicked();
    void on_RRook2_clicked();

private:
    Ui::ChessBoard *ui;
    int coordinate[2];              //��¼����  ��mousePressEvent����  getCurCoordinate�ṩ������ʹ��
    int oldPoint[2];                  //ǰһ������  ��ʱ��û����
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


