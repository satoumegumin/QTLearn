#include "mybutton.h"
#include <QPainter>
#include <QPixmap>
#include <QPropertyAnimation>

//MyButton::MyButton(QWidget *parent) : QWidget(parent)
//{

//}

MyButton::MyButton(QString startImg,QString pressImg)
{
    StartImg=startImg;
    PressImg=pressImg;

    setPixMap(startImg);
//    QPixmap pix;
//    bool ret= pix.load(startImg);

//    if(!ret)
//    {

//    }


//    //设置图片固定大小
//    this->setFixedSize(pix.width(),pix.height());

//    //设置不规则图片央视
//    this->setStyleSheet("QPushButton{border:0px;}");

//    //设置图标
//    this->setIcon(pix);

//    //设置图标大小
//    this->setIconSize(QSize(pix.width(),pix.height()));
}

void MyButton::setPixMap(QString path)
{
    QPixmap pix;
    bool ret=pix.load(path);
    if(!ret)
    {

    }

    //设置图片固定大小
    this->setFixedSize(pix.width(),pix.height());

    //设置不规则图片央视
    this->setStyleSheet("QPushButton{border:0px;}");

    //设置图标
    this->setIcon(pix);

    //设置图标大小
    this->setIconSize(QSize(pix.width(),pix.height()));

}

void MyButton::zoom1()
{
    //创建动画对象
    QPropertyAnimation * animation=new QPropertyAnimation(this,"geometry");
    //设置时间间隔
    animation->setDuration(200);
    //起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //结束位置
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();
}

void MyButton::zoom2()
{
    //创建动画对象
    QPropertyAnimation * animation=new QPropertyAnimation(this,"geometry");
    //设置时间间隔
    animation->setDuration(200);

    //起始位置
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //结束位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();
}

void MyButton::mousePressEvent(QMouseEvent *e)
{
    //如果传入了按下的图片 那么需要切图
    if(PressImg!="")
    {
       setPixMap(PressImg);
    }
    //让父类执行其他的内容
    return QPushButton::mousePressEvent(e);
}

void MyButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(PressImg!="")
    {
       setPixMap(StartImg);
    }
    return QPushButton::mouseReleaseEvent(e);
}
