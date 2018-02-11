#include "inputdialog.h"
#include "ui_inputdialog.h"

InputDialog::InputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputDialog)
{
    ui->setupUi(this);
    ui->randomButton->setChecked(true);

    connect(ui->randomButton, SIGNAL(toggled(bool)), this, SLOT(buttonToggled(bool)));
    connect(ui->comboBox, SIGNAL(activated(int)), this, SLOT(onNumPilesChange(int)));

    for(int i = 1; i <= 10; i++){
        QString s = QString::number(i);
        ui->comboBox->addItem(s);
    }
    ui->comboBox->setVisible(false);
    ui->label->setVisible(false);

    // Combo Boxes to get piles sizes
    pilesSizeBoxes.resize(10);


    for(int i = 0; i < 10; i++){
        pilesSizeBoxes[i] = new QComboBox(this);
        for(int j = 1; j <= 10; j++){
            QString s = QString::number(j);
            pilesSizeBoxes[i]->addItem(s);
        }
        ui->pilesLayout->addWidget(pilesSizeBoxes[i], 0, i);
        pilesSizeBoxes[i]->setVisible(false);
    }

}

void InputDialog::onNumPilesChange(int)
{
    int num = ui->comboBox->currentText().toInt();

    for(int i = 0; i < num; i++)
        pilesSizeBoxes[i]->setVisible(true);
    for(int i = num; i < 10; i++)
        pilesSizeBoxes[i]->setVisible(false);
}
void InputDialog::buttonToggled(bool)
{
    if(ui->randomButton->isChecked()){ //initialize randomly
        ui->comboBox->setVisible(false);
        ui->label->setVisible(false);
        for(int i = 0; i < 10; i++)
            pilesSizeBoxes[i]->setVisible(false);
    }
    else if(ui->manualButton->isChecked()){ // initialize manually
        ui->comboBox->setVisible(true);
        ui->label->setVisible(true);
        onNumPilesChange(1);
    }
}

QVector<int> InputDialog::getValues()
{
    QVector <int> retVec;

    if(ui->randomButton->isChecked()){ // random initialization
        int num_piles = qrand() % 10 + 1; // max 10 piles

        for(int i = 0; i < num_piles; i++){
            int cur = qrand() % 10 + 1; // max 10 per pile
            retVec.push_back(cur);
        }
    }
    else if(ui->manualButton->isChecked()){
        int num_piles = ui->comboBox->currentText().toInt();

        for(int i = 0; i < num_piles; i++){
            int cur = pilesSizeBoxes[i]->currentText().toInt();
            retVec.push_back(cur);
        }
    }
    else{
        Q_ASSERT(0);
    }
    return retVec;
}

InputDialog::~InputDialog()
{
    delete ui;
}
