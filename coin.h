#ifndef COIN_H
#define COIN_H

#include <QPushButton>

class Coin : public QPushButton
{
    Q_OBJECT
public:
    //explicit Coin(QWidget *parent = nullptr);
    Coin(QString path);

    int pox;
    int poy;
    bool flag;
    QTimer * timer;

    void changeFlag();

    int min=1;
    int max=8;

    bool isAnimal=false;

    bool isWin=false;

    void mousePressEvent(QMouseEvent * ev);

signals:

};

#endif // COIN_H
