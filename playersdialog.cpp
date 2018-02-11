#include "playersdialog.h"
#include "ui_playersdialog.h"

PlayersDialog::PlayersDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlayersDialog)
{
    ui->setupUi(this);
}

PlayersDialog::~PlayersDialog()
{
    delete ui;
}

bool PlayersDialog::getNumOfPlayers()
{
    return ui->onePlayerButton->isChecked();
}
