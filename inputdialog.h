#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include <QDialog>
#include <QComboBox>

namespace Ui {
class InputDialog;
}

class InputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InputDialog(QWidget *parent = 0);
    ~InputDialog();
    QVector <int> getValues();

private:
    Ui::InputDialog *ui;
    QVector <QComboBox *> pilesSizeBoxes;

public slots:
    void buttonToggled(bool);
    void onNumPilesChange(int);
};

#endif // INPUTDIALOG_H
