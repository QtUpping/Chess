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
    int *getCurCoordinate(int *point);

    void coordinateConversion(int *XY);
    bool validClick(int *XY);                                  //�жϵ���Ƿ���������

private slots:
    void on_RCannon_clicked();

    void on_RCannon2_clicked();

private:
    Ui::ChessBoard *ui;
    int coordinate[2];              //��¼����  ͨ��mousePressEvent�ṩ������ʹ��
    int oldPoint[2];                   //ǰһ������
};

#endif // CHESSBOARD_H


