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
    //每次鼠标点击后修改coordinate的值(初始为0,0),通过getCurCoordinate提供给外部
    int *getCurCoordinate(int *point);

    void coordinateConversion(int *XY);
    bool validClick(int *XY);                                  //判断点击是否在棋盘内

private slots:
    void on_RCannon_clicked();

    void on_RCannon2_clicked();

private:
    Ui::ChessBoard *ui;
    int coordinate[2];              //记录坐标  通过mousePressEvent提供给类外使用
    int oldPoint[2];                   //前一点坐标
};

#endif // CHESSBOARD_H


