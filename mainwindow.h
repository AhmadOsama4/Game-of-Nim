#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QString>
#include "square.h"
#include "inputdialog.h"
#include "playersdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QVector < QVector<Square *> > grid;
    QString playersNames[2];
    int cellSide;
    int spacing;
    int num_piles;
    bool Turn = 0;
    bool isComp = 1;
    QVector < QPair<int,int> > mapper;

    void initializeGrid(QVector <int> piles);
    void updateWindow();
    void updatePositions();
    void doMove(int pile, int amount);

public slots:
    void onCellClicked(int c);
    void startCompMove(bool f);

signals:
    void playerMoveDone(bool f);
};

#endif // MAINWINDOW_H
