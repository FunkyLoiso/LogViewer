/********************************************************************************
** Form generated from reading UI file 'LogTabWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGTABWIDGET_H
#define UI_LOGTABWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "LogViewport.h"

QT_BEGIN_NAMESPACE

class Ui_LogTabWidget
{
public:
    QVBoxLayout *verticalLayout;
    LogViewport *logViewport;
    QHBoxLayout *horizontalLayout;
    QCheckBox *chbLineWrap;
    QCheckBox *chbFollow;
    QSpacerItem *horizontalSpacer;
    QPushButton *bClear;

    void setupUi(QWidget *LogTabWidget)
    {
        if (LogTabWidget->objectName().isEmpty())
            LogTabWidget->setObjectName(QString::fromUtf8("LogTabWidget"));
        LogTabWidget->resize(582, 406);
        verticalLayout = new QVBoxLayout(LogTabWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        logViewport = new LogViewport(LogTabWidget);
        logViewport->setObjectName(QString::fromUtf8("logViewport"));

        verticalLayout->addWidget(logViewport);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        chbLineWrap = new QCheckBox(LogTabWidget);
        chbLineWrap->setObjectName(QString::fromUtf8("chbLineWrap"));
        chbLineWrap->setChecked(true);

        horizontalLayout->addWidget(chbLineWrap);

        chbFollow = new QCheckBox(LogTabWidget);
        chbFollow->setObjectName(QString::fromUtf8("chbFollow"));
        chbFollow->setEnabled(false);
        chbFollow->setCheckable(true);
        chbFollow->setChecked(true);

        horizontalLayout->addWidget(chbFollow);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        bClear = new QPushButton(LogTabWidget);
        bClear->setObjectName(QString::fromUtf8("bClear"));
        bClear->setEnabled(false);

        horizontalLayout->addWidget(bClear);


        verticalLayout->addLayout(horizontalLayout);

        verticalLayout->setStretch(0, 1);

        retranslateUi(LogTabWidget);
        QObject::connect(chbLineWrap, SIGNAL(toggled(bool)), logViewport, SLOT(setLineWrap(bool)));
        QObject::connect(chbFollow, SIGNAL(toggled(bool)), logViewport, SLOT(setFollow(bool)));

        QMetaObject::connectSlotsByName(LogTabWidget);
    } // setupUi

    void retranslateUi(QWidget *LogTabWidget)
    {
        LogTabWidget->setWindowTitle(QCoreApplication::translate("LogTabWidget", "Form", nullptr));
        chbLineWrap->setText(QCoreApplication::translate("LogTabWidget", "Line &wrap", nullptr));
        chbFollow->setText(QCoreApplication::translate("LogTabWidget", "&Follow", nullptr));
        bClear->setText(QCoreApplication::translate("LogTabWidget", "Clear", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LogTabWidget: public Ui_LogTabWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGTABWIDGET_H
