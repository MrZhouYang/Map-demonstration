#ifndef DEMONSTRATION_WINDOW_H
#define DEMONSTRATION_WINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QImage>
#include <QLabel>
#include <QTimer>
#include <QList>
#include <QPoint>

namespace Ui {
class Demonstration_Window;
}

class Demonstration_Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Demonstration_Window(QWidget *parent = 0);
    ~Demonstration_Window();

private:
    Ui::Demonstration_Window *ui;

    QImage image_submarine;
    QImage image_port;

    QTimer *animat_timer;
    int pos_x; //潜艇x坐标
    int pos_y; //潜艇y坐标

    //选择的路线 0:未选择 1：青岛港-》上海港
    int pathselect;

    QLabel *port1; //青岛港
    QLabel *port2; //上海港
    QLabel *port3;

    void path1to2();
    void path2to3();

    //QList<QPoint> list_1to2;  //保存从青岛港到上海港的路线点

protected:
    void mousePressEvent(QMouseEvent *event);

private slots:
  void move_label();
  void on_actionstart_triggered();
  void on_actionstop_triggered();
  void on_actionpath1_triggered();
  void on_actionpath2_triggered();
};

#endif // DEMONSTRATION_WINDOW_H
