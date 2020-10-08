#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>

class MyButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyButton(QWidget *parent = nullptr);
    MyButton (QString startImg,QString pressImg="");

    QString StartImg;
    QString PressImg;


    void zoom1();//向下弹跳
    void zoom2();//向上弹跳

    //重写按钮的按下和释放事件
    void mousePressEvent(QMouseEvent * e);

    void mouseReleaseEvent(QMouseEvent * e);

    void setPixMap(QString path);
signals:

};

#endif // MYBUTTON_H
