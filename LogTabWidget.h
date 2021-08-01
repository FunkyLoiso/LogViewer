#ifndef LOGTABWIDGET_H
#define LOGTABWIDGET_H

#include <QtWidgets/QWidget>
#include "ui_LogTabWidget.h"

class LogTabWidget : public QWidget, public Ui::LogTabWidget
{
    Q_OBJECT

public:
    LogTabWidget(QWidget *parent = 0);
    ~LogTabWidget();
};

#endif // LOGTABWIDGET_H
