#include "playscene.h"
#include <QMenuBar>
#include<QPixmap>
#include <QPainter>
#include <mybutton.h>
#include <QTimer>
#include <QLabel>
#include "coin.h"
#include "dataconfig.h"
#include <QPropertyAnimation>
#include <QSound>

PlayScene::PlayScene(int num)
{
    this->levelIndex=num;

    QString title=QString("CoinFlip第%1关").arg(num);

    this->setWindowTitle(title);

    this->setFixedSize(320,588);

    this->setWindowIcon(QIcon(":/GameSource/Coin0001.png"));

    QMenuBar * start_Menu=menuBar();

    setMenuBar(start_Menu);

    QMenu * menu=start_Menu->addMenu("开始");

    QAction * quitAction= menu->addAction("退出");

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
            emit this->returnSelectScene();
        });
    });

    QPixmap coinGround;
    coinGround.load(":/GameSource/BoardNode.png");

    dataConfig dataconfig;

    for (int i=0;i<4;i++) {
        for (int j=0;j<4;j++) {
            this->coinArray[i][j]=dataconfig.mData[levelIndex][i][j];
        }
    }

    //设置胜利动画
    QLabel * winLabel=new QLabel(this);
    QPixmap winPix;
    winPix.load(":/GameSource/LevelCompletedDialogBg.png");
    winLabel->setFixedSize(QSize(winPix.width(),winPix.height()));
    winLabel->setPixmap(winPix);
    winLabel->move(this->width()/2-winLabel->width()/2,-100-winPix.height());

    int startx=(this->width()-4*coinGround.width())/2;
    int starty=this->height()/4;

    QSound * filpSound=new QSound(":/GameSource/ConFlipSound.wav");

    QSound * winSound=new QSound(":/GameSource/LevelWinSound.wav");

    for(int i=0;i<4;i++)
    {
        for (int j=0;j<4;j++) {
            QLabel * label=new QLabel(this);
            label->setFixedSize(coinGround.width(),coinGround.height());
            label->setPixmap(coinGround);
            label->move(startx+i*50,starty+j*50);

            Coin * coin;
            if(this->coinArray[i][j]==1)
            {
                coin=new Coin(":/GameSource/Coin0001.png");
            }
            else
            {
                 coin=new Coin(":/GameSource/Coin0008.png");
            }
            coin->pox=i;
            coin->poy=j;

            coin->flag=coinArray[i][j];

            coin->setParent(this);
            coin->move(startx+2+i*50,starty+4+j*50);

            gameItem[i][j]=coin;

            connect(coin,&Coin::clicked,[=](){
                coin->changeFlag();

                filpSound->play();
                coinArray[i][j]=!coinArray[i][j];
                QTimer::singleShot(100,this,[=](){
                    if(i<3)
                    {
                        coinArray[i+1][j]=!coinArray[i+1][j];
                        gameItem[i+1][j]->changeFlag();
                    }
                    if(i>0)
                    {
                        coinArray[i-1][j]=!coinArray[i-1][j];
                        gameItem[i-1][j]->changeFlag();
                    }
                    if(j<3)
                    {
                        coinArray[i][j+1]=!coinArray[i][j+1];
                        gameItem[i][j+1]->changeFlag();
                    }
                    if(j>0)
                    {
                        coinArray[i][j-1]=!coinArray[i][j-1];
                        gameItem[i][j-1]->changeFlag();
                    }

                    bool isWin=true;
                    for(int i=0;i<=4;i++)
                    {
                        for(int j=0;j<4;j++)
                        {
                            if(coinArray[i][j]==0)
                            {
                                isWin=0;
                                break;
                            }
                        }
                    }

                    if (isWin)
                    {
                        for(int i=0;i<4;i++)
                        {
                            for(int j=0;j<4;j++)
                            {
                                gameItem[i][j]->isWin=true;
                            }
                        }

                        QTimer::singleShot(300,this,[=](){
                            QPropertyAnimation * animal=new QPropertyAnimation(winLabel,"geometry");
                            animal->setDuration(1000);
                            animal->setStartValue(QRect(winLabel->x(),winLabel->y(), winLabel->width(),winLabel->height()));
                            animal->setEndValue(QRect(winLabel->x(),250+winLabel->y(), winLabel->width(),winLabel->height()));

                            animal->setEasingCurve(QEasingCurve::OutBounce);


                            winSound->play();
                            animal->start();
                        });


                    }

                });
            });
        }
    }
}

void PlayScene::paintEvent(QPaintEvent *ev)
{
    QPainter painter(this);

    QPixmap pix;

    pix.load(":/GameSource/PlayLevelSceneBg.png");

    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    pix.load(":/GameSource/Title.png");

    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);

    painter.drawPixmap(10,30,pix);



}
