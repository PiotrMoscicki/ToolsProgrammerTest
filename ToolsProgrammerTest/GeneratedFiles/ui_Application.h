/********************************************************************************
** Form generated from reading UI file 'Application.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APPLICATION_H
#define UI_APPLICATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ApplicationClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ApplicationClass)
    {
        if (ApplicationClass->objectName().isEmpty())
            ApplicationClass->setObjectName(QStringLiteral("ApplicationClass"));
        ApplicationClass->resize(600, 400);
        menuBar = new QMenuBar(ApplicationClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        ApplicationClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ApplicationClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ApplicationClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(ApplicationClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        ApplicationClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(ApplicationClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ApplicationClass->setStatusBar(statusBar);

        retranslateUi(ApplicationClass);

        QMetaObject::connectSlotsByName(ApplicationClass);
    } // setupUi

    void retranslateUi(QMainWindow *ApplicationClass)
    {
        ApplicationClass->setWindowTitle(QApplication::translate("ApplicationClass", "Application", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ApplicationClass: public Ui_ApplicationClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APPLICATION_H
