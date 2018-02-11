#ifndef SQUARE_H
#define SQUARE_H

#include <QObject>
#include <QWidget>
#include <QLabel>

class Square : public QLabel
{
    Q_OBJECT
public:
    Square (QWidget *parent = 0);
    int getWidth();
    int getHeight();

protected:
    void mousePressEvent(QMouseEvent *);

private:
    int width, height;

signals:
    void clicked();
};

#endif // SQUARE_H
