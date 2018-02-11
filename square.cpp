#include "square.h"

Square::Square(QWidget *parent) : QLabel (parent)
{
    width = height = 50;
}

int Square::getHeight(){
    return height;
}

int Square::getWidth(){
    return width;
}

void Square::mousePressEvent(QMouseEvent *)
{
    emit clicked();
}
