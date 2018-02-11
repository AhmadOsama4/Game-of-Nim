#ifndef COMPUTERMOVE_H
#define COMPUTERMOVE_H

#include <QPair>
#include <QVector>
#include "square.h"

class ComputerMove
{
public:
    ComputerMove();
    QPair <int,int> getMove(const QVector < QVector <Square *> > &grid);
};

#endif // COMPUTERMOVE_H
