#include "coin.h"
#include <QPixmap>
#include <QTimer>
#include <QDebug>
//Coin::Coin(QWidget *parent) : QWidget(parent)
//{

//}

Coin::Coin(QString path)
{
    QPixmap pix;
    bool ret=pix.load(path);

    if  (!ret)
    {

    }

    timer =new QTimer(this);
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));

    connect(timer,&QTimer::timeout,[=](){
       QString path;
       if(this->flag==true)
       {
           path=QString(":/GameSource/Coin000%1.png").arg(max--);
       }
       else{
           path=QString(":/GameSource/Coin000%1.png").arg(min++);
       }
       QPixmap pix;
       pix.load(path);
       this->setFixedSize(pix.width(),pix.height());
       this->setStyleSheet("QPushButton{border:0px;}");
       this->setIcon(pix);
       this->setIconSize(QSize(pix.width(),pix.height()));

       if(min>max)
       {
           this->min=1;
           this->max=8;
           this->isAnimal=false;
           timer->stop();
           //
       }

    });
}

void Coin::changeFlag()
{
    timer->start(30);
    if(this->flag==0)
    {
        this->flag=true;
    }else
    {
        this->flag=false;
    }
    this->isAnimal=true;
}

void Coin::mousePressEvent(QMouseEvent *ev)
{
    if(isAnimal||isWin)
    {
        //qDebug()<<"不呢个";
        return;
    }
    else
    {
        QPushButton::mousePressEvent(ev);
    }
}
