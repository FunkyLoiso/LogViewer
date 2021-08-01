#ifndef LOGVIEWER_H
#define LOGVIEWER_H

#include <QtWidgets/QMainWindow>
#include "ui_logviewer.h"

#include <QtCore/QFile>
#include <QtCore/QFileSystemWatcher>

class LogViewer : public QMainWindow
{
	Q_OBJECT

public:
	LogViewer(QWidget *parent = 0);
	~LogViewer();

private:
	Ui::LogViewerClass ui;
};

#endif // LOGVIEWER_H
