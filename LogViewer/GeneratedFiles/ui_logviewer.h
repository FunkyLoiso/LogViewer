/********************************************************************************
** Form generated from reading UI file 'logviewer.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGVIEWER_H
#define UI_LOGVIEWER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "LogTabWidget.h"

QT_BEGIN_NAMESPACE

class Ui_LogViewerClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    LogTabWidget *tab;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *LogViewerClass)
    {
        if (LogViewerClass->objectName().isEmpty())
            LogViewerClass->setObjectName(QString::fromUtf8("LogViewerClass"));
        LogViewerClass->resize(983, 422);
        centralWidget = new QWidget(LogViewerClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setTabsClosable(true);
        tabWidget->setMovable(true);
        tabWidget->setTabBarAutoHide(false);
        tab = new LogTabWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        tabWidget->addTab(tab, QString());

        verticalLayout->addWidget(tabWidget);

        LogViewerClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(LogViewerClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 983, 21));
        LogViewerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(LogViewerClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        LogViewerClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(LogViewerClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        LogViewerClass->setStatusBar(statusBar);

        retranslateUi(LogViewerClass);

        QMetaObject::connectSlotsByName(LogViewerClass);
    } // setupUi

    void retranslateUi(QMainWindow *LogViewerClass)
    {
        LogViewerClass->setWindowTitle(QCoreApplication::translate("LogViewerClass", "LogViewer", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("LogViewerClass", "test", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LogViewerClass: public Ui_LogViewerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGVIEWER_H
