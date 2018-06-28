#include "demonstration_window.h"
#include "ui_demonstration_window.h"
#include <QDebug>
#include <QMouseEvent>

Demonstration_Window::Demonstration_Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Demonstration_Window)
{
    ui->setupUi(this);

    QPalette palette;
    palette.setBrush(QPalette::Background,QBrush(QPixmap(":/images/map1.png")));
    this->setPalette(palette);
    this->resize( QPixmap(":/images/map1.png").size() );
    this->setAutoFillBackground(true);

    //港口
    image_port.load(":/images/port.jpg");
    image_port = image_port.scaled(50,50,Qt::IgnoreAspectRatio);
    port1 = new QLabel(this);
    port1->setPixmap( QPixmap(QPixmap::fromImage(image_port)) );
    port1->setScaledContents(true);
    port1->resize(image_port.width()/2,image_port.height()/2);
    port1->move(972,167);  //青岛港

    port2 = new QLabel(this);
    port2->setPixmap( QPixmap(QPixmap::fromImage(image_port)) );
    port2->setScaledContents(true);
    port2->resize(image_port.width()/2,image_port.height()/2);
    port2->move(1004,332); //上海港

    port2 = new QLabel(this);
    port2->setPixmap( QPixmap(QPixmap::fromImage(image_port)) );
    port2->setScaledContents(true);
    port2->resize(image_port.width()/2,image_port.height()/2);
    port2->move(1200,265); //福冈港

    //潜艇
    image_submarine.load(":/images/submarine_to_right.jpg");
    //ui->pic_label->setGeometry(0, 0, 200, 150);
    image_submarine = image_submarine.scaled(100, 62, Qt::IgnoreAspectRatio);
    ui->pic_label->setPixmap(QPixmap::fromImage(image_submarine));
    ui->pic_label->setScaledContents(true);
    ui->pic_label->resize(image_submarine.width()/2, image_submarine.height()/2);
    //ui->pic_label->move(1260,415);
    ui->pic_label->move(971,80);

    pathselect = 0;//初始化为未选择路径
    //path1to2Init();

    animat_timer = new QTimer(this);
    connect(animat_timer, SIGNAL(timeout()), this, SLOT(move_label()));

    ui->actionstop->setEnabled(false);

    //菜单项点击关联槽函数
    connect(ui->actionstart, SIGNAL(triggered(bool)), this, SLOT(on_actionstart_triggered()) );
    connect( ui->actionstop,SIGNAL(triggered(bool)), this, SLOT(on_actionstop_triggered()) );
    connect(ui->actionpath1,SIGNAL(triggered(bool)), this, SLOT(on_actionpath1_triggered()) );
    connect(ui->actionpath2,SIGNAL(triggered(bool)), this, SLOT(on_actionpath2_triggered()) );
}

Demonstration_Window::~Demonstration_Window()
{
    delete ui;
}

//定时器溢出槽函数
void Demonstration_Window::move_label()
{
  if(pathselect==0)
      return;
  if(pathselect==1)
      path1to2();
  if(pathselect==2)
      path2to3();
}


void Demonstration_Window::on_actionstart_triggered()
{
    ui->actionstart->setEnabled(false);
    ui->actionstop->setEnabled(true);
    animat_timer->start(50);
}

void Demonstration_Window::on_actionstop_triggered()
{
    ui->actionstart->setEnabled(true);
    ui->actionstop->setEnabled(false);
    if(animat_timer->isActive())
        animat_timer->stop();
}

void Demonstration_Window::mousePressEvent(QMouseEvent *event)
{
    int x = event->pos().x();
    int y = event->pos().y();
    qDebug() << "x:"<< x << " " << "y:" <<y;
}


void Demonstration_Window::path1to2()
{
    if(pos_x<1040 && pos_y==80)
    {
        pos_x+=2;

        image_submarine.load(":/images/submarine_to_right.jpg");
        image_submarine = image_submarine.scaled(100, 62, Qt::IgnoreAspectRatio);
        ui->pic_label->setPixmap(QPixmap::fromImage(image_submarine));
        ui->pic_label->resize(image_submarine.width()/2, image_submarine.height()/2);

        ui->pic_label->move(pos_x,pos_y);
    }
    else if(pos_x>=1040 && pos_y<265)
    {
        pos_y+=2;

        image_submarine.load(":/images/submarine_to_down.png");
        image_submarine = image_submarine.scaled(62, 100, Qt::IgnoreAspectRatio);
        ui->pic_label->setPixmap(QPixmap::fromImage(image_submarine));
        ui->pic_label->resize(image_submarine.width()/2, image_submarine.height()/2);

        ui->pic_label->move(pos_x,pos_y);
    }
    else if(pos_x>1013 && pos_y>=265)
    {
        pos_x-=2;

        image_submarine.load(":/images/submarine_to_left.jpg");
        image_submarine = image_submarine.scaled(100, 62, Qt::IgnoreAspectRatio);
        ui->pic_label->setPixmap(QPixmap::fromImage(image_submarine));
        ui->pic_label->resize(image_submarine.width()/2, image_submarine.height()/2);

        ui->pic_label->move(pos_x,pos_y);
    }
    //qDebug() << "当前潜艇坐标：" << "x:" << pos_x << "y:"<< pos_y;
}

void Demonstration_Window::on_actionpath1_triggered()
{
    pathselect = 1;
    pos_x = 974;
    pos_y = 80;
    ui->pic_label->move(pos_x,pos_y);
    qDebug() << "当前路线：" << pathselect << endl;
    qDebug() << "路线1初始潜艇坐标：" << "x:" << pos_x << "y:"<< pos_y;
}

void Demonstration_Window::on_actionpath2_triggered()
{
    pathselect = 2;
    pos_x = 1013;
    pos_y = 265;
    ui->pic_label->move(pos_x,pos_y);
    qDebug() << "当前路线：" << pathselect << endl;
    qDebug() << "路线2初始潜艇坐标：" << "x:" << pos_x << "y:"<< pos_y;
}

void Demonstration_Window::path2to3()
{
    if(pos_x<1145 && pos_y==265)
    {
        pos_x+=2;

        image_submarine.load(":/images/submarine_to_right.jpg");
        image_submarine = image_submarine.scaled(100, 62, Qt::IgnoreAspectRatio);
        ui->pic_label->setPixmap(QPixmap::fromImage(image_submarine));
        ui->pic_label->resize(image_submarine.width()/2, image_submarine.height()/2);

        ui->pic_label->move(pos_x,pos_y);
    }
    else if(pos_x>=1145 && pos_y>215)
    {
        pos_y-=2;

        image_submarine.load(":/images/submarine_to_up.png");
        image_submarine = image_submarine.scaled(62, 100, Qt::IgnoreAspectRatio);
        ui->pic_label->setPixmap(QPixmap::fromImage(image_submarine));
        ui->pic_label->resize(image_submarine.width()/2, image_submarine.height()/2);

        ui->pic_label->move(pos_x,pos_y);
    }
    else if(pos_x<1150 && pos_y<=215)
    {
        pos_x+=2;

        image_submarine.load(":/images/submarine_to_right.jpg");
        image_submarine = image_submarine.scaled(100, 62, Qt::IgnoreAspectRatio);
        ui->pic_label->setPixmap(QPixmap::fromImage(image_submarine));
        ui->pic_label->resize(image_submarine.width()/2, image_submarine.height()/2);

        ui->pic_label->move(pos_x,pos_y);
    }
}
