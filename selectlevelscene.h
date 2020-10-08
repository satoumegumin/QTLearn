#ifndef SELECTLEVELSCENE_H
#define SELECTLEVELSCENE_H

#include <QMainWindow>
#include <QWidget>
#include "playscene.h"

class selectLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit selectLevelScene(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent * ev);

    PlayScene * playScene;
signals:
    //写一个自定义的信号 告诉主场景 点击了返回
    void returnMainScene();
};

#endif // SELECTLEVELSCENE_H
