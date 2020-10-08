#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include "coin.h"

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit PlayScene(QWidget *parent = nullptr);
    PlayScene(int levelIndex);
    int levelIndex;

    void paintEvent(QPaintEvent * ev);
    //维护金币数组
    int coinArray[4][4];

    Coin * gameItem[4][4];
signals:
    void returnSelectScene();
};

#endif // PLAYSCENE_H
