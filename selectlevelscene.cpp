#include "selectlevelscene.h"
#include <QPainter>
#include <QPixmap>
#include <QMenuBar>
#include "mybutton.h"
#include <QTimer>
#include <QDebug>
#include <QLabel>
#include "playscene.h"

selectLevelScene::selectLevelScene(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(320,588);
    this->setWindowTitle("CoinFilp");
    this->setWindowIcon(QIcon(":/GameSource/Coin0001.png"));

    QMenuBar * bar=menuBar();
    setMenuBar(bar);

    QMenu * startMenu=bar->addMenu("开始");

    QAction * quitAction=startMenu->addAction("退出");

    connect(quitAction,&QAction::triggered,[=](){
        close();
    });

    //返回按钮
    MyButton * backBtn=new MyButton(":/GameSource/BackButton.png",":/GameSource/BackButtonSelected.png");

    backBtn->setParent(this);

    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

    //点击返回
    connect(backBtn,&QPushButton::clicked,[=](){

        QTimer::singleShot(200,this,[=](){
            emit this->returnMainScene();
        });
    });

    //创建选择关卡的按钮

    for(int i=0;i<20;i++)
    {
        MyButton * itemBtn=new MyButton(":/GameSource/LevelIcon.png");
        itemBtn->setParent(this);
        itemBtn->move(25+i%4*70,130+i/4*70);

        connect(itemBtn,&QPushButton::clicked,[=](){
           //qDebug()<<i+1;


            QTimer::singleShot(200,this,[=](){

                //进入到游戏场景
                playScene=new PlayScene(i+1);

                playScene->setGeometry(this->geometry());

                playScene->show();

                this->hide();

                qDebug()<<0;

                connect(playScene,&PlayScene::returnSelectScene,[=](){

                    this->setGeometry(playScene->geometry());
                    delete playScene;
                    playScene=NULL;
                    this->show();
                });
            });

        });

        QLabel * label=new QLabel();
        label->setParent(this);
        label->setText(QString::number(i+1));
        label->move(25+i%4*70,130+i/4*70);
        label->setAlignment(Qt::AlignCenter);
        //设置鼠标穿透属性
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
        label->setFixedSize(itemBtn->width(),itemBtn->height());
    }

}

void selectLevelScene::paintEvent(QPaintEvent *ev)
{
    QPainter painter(this);

    QPixmap pix;
    pix.load(":/GameSource/PlayLevelSceneBg.png");

    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    pix.load(":/GameSource/Title.png");

    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);

    painter.drawPixmap(10,30,pix);

}
