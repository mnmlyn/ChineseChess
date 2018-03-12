/********************************************************************************
** Form generated from reading UI file 'ChineseChess.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHINESECHESS_H
#define UI_CHINESECHESS_H

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

class Ui_ChineseChessClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ChineseChessClass)
    {
        if (ChineseChessClass->objectName().isEmpty())
            ChineseChessClass->setObjectName(QStringLiteral("ChineseChessClass"));
        ChineseChessClass->resize(600, 400);
        menuBar = new QMenuBar(ChineseChessClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        ChineseChessClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ChineseChessClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ChineseChessClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(ChineseChessClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        ChineseChessClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(ChineseChessClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ChineseChessClass->setStatusBar(statusBar);

        retranslateUi(ChineseChessClass);

        QMetaObject::connectSlotsByName(ChineseChessClass);
    } // setupUi

    void retranslateUi(QMainWindow *ChineseChessClass)
    {
        ChineseChessClass->setWindowTitle(QApplication::translate("ChineseChessClass", "ChineseChess", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ChineseChessClass: public Ui_ChineseChessClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHINESECHESS_H
