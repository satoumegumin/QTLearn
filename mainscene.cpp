#include "mainscene.h"
#include "ui_mainscene.h"
#include <QPixmap>
#include <QPainter>
#include "mybutton.h"
#include <QDebug>
#include <QTimer>
#include "selectlevelscene.h"

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);

    this->setFixedSize(320,588);
    this->setWindowTitle("CoinFilp");
    this->setWindowIcon(QIcon(":/GameSource/Coin0001.png"));

    connect(ui->men_Exit,&QAction::triggered,[=](){
        close();
    });

    MyButton * btn_start=new MyButton(":/GameSource/MenuSceneStartButton.png");

    btn_start->setParent(this);

    btn_start->move(this->width()*0.5-btn_start->width()*0.5,this->height()*0.7);

    slectScene =new selectLevelScene(this);

   connect(slectScene,&selectLevelScene::returnMainScene,[=](){
       slectScene->hide();

       this->setGeometry(slectScene->geometry());

       this->show();
   });

    connect(btn_start,&QPushButton::clicked,[=](){
        //qDebug()<<"按下了开始按钮";
        btn_start->zoom1();
        btn_start->zoom2();

        QTimer::singleShot(500,this,[=](){

            slectScene->setGeometry(this->geometry());

            this->hide();
            slectScene->show();
        });
    });

}

void MainScene::paintEvent(QPaintEvent *ev)
{
    QPixmap pix;
    pix.load(":/GameSource/PlayLevelSceneBg.png");

    QPainter painter(this);
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    pix.load(":/GameSource/Title.png");

    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);

    painter.drawPixmap(10,30,pix);

}

MainScene::~MainScene()
{
    delete ui;
}

