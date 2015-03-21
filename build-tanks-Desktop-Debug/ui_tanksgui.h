/********************************************************************************
** Form generated from reading UI file 'tanksgui.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TANKSGUI_H
#define UI_TANKSGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TanksGUI
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TanksGUI)
    {
        if (TanksGUI->objectName().isEmpty())
            TanksGUI->setObjectName(QStringLiteral("TanksGUI"));
        TanksGUI->resize(400, 300);
        menuBar = new QMenuBar(TanksGUI);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        TanksGUI->setMenuBar(menuBar);
        mainToolBar = new QToolBar(TanksGUI);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        TanksGUI->addToolBar(mainToolBar);
        centralWidget = new QWidget(TanksGUI);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        TanksGUI->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(TanksGUI);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        TanksGUI->setStatusBar(statusBar);

        retranslateUi(TanksGUI);

        QMetaObject::connectSlotsByName(TanksGUI);
    } // setupUi

    void retranslateUi(QMainWindow *TanksGUI)
    {
        TanksGUI->setWindowTitle(QApplication::translate("TanksGUI", "TanksGUI", 0));
    } // retranslateUi

};

namespace Ui {
    class TanksGUI: public Ui_TanksGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TANKSGUI_H
