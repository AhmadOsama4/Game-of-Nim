#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "square.h"
#include "computermove.h"
#include <QDebug>
#include <QSignalMapper>
#include <QMessageBox>
#include <QThread>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setMinimumSize(920, 720);
    cellSide = 50;
    spacing = 10;

    QVector <int> V;

    InputDialog dlg;
    if( dlg.exec()){
        V = dlg.getValues();
    }
    else{
        // TODO: Terminate program if dialog outputs cancel
        //qDebug() << "FAILED";
        V.push_back(1);
        //this->close();
    }
    initializeGrid(V);
    updateWindow();
    connect(this, SIGNAL(playerMoveDone(bool)), this, SLOT(startCompMove(bool)));

    playersNames[0] = "Player 1";
    playersNames[1] = "Player 2";

    if(isComp)
        playersNames[1] = "Computer";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializeGrid(QVector <int> piles)
{
    num_piles = piles.size(); // max 10 piles
    grid.resize(num_piles);

    int cnt = 0;
    for(int i = 0; i < num_piles; i++){
        int cur = piles[i]; // max 10 per pile
        grid[i].resize(cur);
        cnt += cur;
    }

    mapper.resize(cnt);
}

void MainWindow::updateWindow()
{
    QSignalMapper *signalMapper = new QSignalMapper(this);

    int indx = 0;

    for(int i = 0; i < grid.size(); i++){
        for(int j = 0; j < grid[i].size(); j++){
            grid[i][j] = new Square(this);
            grid[i][j]->setText("");
            grid[i][j]->setStyleSheet("QLabel {background-color : red}");

            connect(grid[i][j], SIGNAL(clicked()), signalMapper, SLOT(map()));
            signalMapper->setMapping(grid[i][j], indx);
            mapper[indx] = qMakePair(i, j);

            indx++;
        }
    }
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(onCellClicked(int)));
    updatePositions();
}

void MainWindow::updatePositions()
{
    int row = 600;
    int col = (width() - cellSide * num_piles - (num_piles - 1) * spacing) / 2;

    for(int i = 0; i < grid.size(); i++){
        if(grid[i].size() == 0)
            continue;
        row = 600;
        for(int j = 0; j < grid[i].size(); j++){
            grid[i][j]->setGeometry(QRect(col, row, cellSide, cellSide));
            row -= (spacing + cellSide);
        }
        col += (spacing + cellSide);
    }

}

void MainWindow::onCellClicked(int c)
{
    int row = mapper[c].first;
    int col = mapper[c].second;

    doMove(row, grid[row].size() - col);
}

void MainWindow::doMove(int pile, int amount)
{    
    //if( grid[pile].size() <= 0 || amount > grid[pile].size())
        //return;
    Q_ASSERT(grid[pile].size() > 0 && amount <= grid[pile].size());

    int start = grid[pile].size() - amount;

    for(int i = start; i < grid[pile].size(); i++)
        delete grid[pile][i];

    grid[pile].erase(grid[pile].begin() + start, grid[pile].end());
    if(grid[pile].size() == 0){
        num_piles--;
        updatePositions();
    }
    if(num_piles == 0){
        QString Winner = playersNames[Turn];
        QMessageBox::information(this, "Winner", "Congratulations " + Winner + " Won !!");
        this->close();
        return;
    }    
    Turn = 1 - Turn;
    emit playerMoveDone(Turn && isComp);
}

void MainWindow::startCompMove(bool f)
{
    if(f){
        ComputerMove mv;
        QPair <int, int> move = mv.getMove(grid);
        //QThread::msleep(500);
        doMove(move.first, move.second);
    }
}
