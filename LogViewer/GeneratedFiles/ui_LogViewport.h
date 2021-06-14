/********************************************************************************
** Form generated from reading UI file 'LogViewport.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGVIEWPORT_H
#define UI_LOGVIEWPORT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LogViewport
{
public:
    QGridLayout *gridLayout;
    QTextEdit *textViewport;
    QScrollBar *textScrollBar;

    void setupUi(QWidget *LogViewport)
    {
        if (LogViewport->objectName().isEmpty())
            LogViewport->setObjectName(QString::fromUtf8("LogViewport"));
        LogViewport->resize(443, 362);
        gridLayout = new QGridLayout(LogViewport);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        textViewport = new QTextEdit(LogViewport);
        textViewport->setObjectName(QString::fromUtf8("textViewport"));
        textViewport->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        gridLayout->addWidget(textViewport, 0, 0, 1, 1);

        textScrollBar = new QScrollBar(LogViewport);
        textScrollBar->setObjectName(QString::fromUtf8("textScrollBar"));
        textScrollBar->setOrientation(Qt::Vertical);

        gridLayout->addWidget(textScrollBar, 0, 1, 1, 1);


        retranslateUi(LogViewport);

        QMetaObject::connectSlotsByName(LogViewport);
    } // setupUi

    void retranslateUi(QWidget *LogViewport)
    {
        LogViewport->setWindowTitle(QCoreApplication::translate("LogViewport", "LogViewport", nullptr));
        textViewport->setHtml(QCoreApplication::translate("LogViewport", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">my cock is black and I am white</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">my cock is black and I am white<br />my cock is black and I am white<br />my cock is black and I am white<br />my cock is black and I am white<br />my cock is black and I am white<br />my cock is black and I am white<br />my cock is black and I am white<br />my cock is black and I am white<br />my cock is black and I am white<"
                        "br />my cock is black and I am white<br />my cock is black and I am white<br />my cock is black and I am white<br />my cock is black and I am white</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LogViewport: public Ui_LogViewport {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGVIEWPORT_H
