#include "tanksgui.h"
#include "ui_tanksgui.h"

TanksGUI::TanksGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TanksGUI)
{
    ui->setupUi(this);
}

TanksGUI::~TanksGUI()
{
    delete ui;
}
