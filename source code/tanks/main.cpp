#include "tanksgui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TanksGUI w;
    w.show();

    return a.exec();
}
