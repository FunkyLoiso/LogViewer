#ifndef LOGVIEWPORT_H
#define LOGVIEWPORT_H

#include <QtWidgets/QWidget>
#include <list>
#include "ui_LogViewport.h"
#include "AbstractLinesProvider.h"

class LogViewport : public QWidget {
  Q_OBJECT

public:
  LogViewport(QWidget *parent = 0);
  ~LogViewport();

  void setProvider(AbstractLinesProvider* provider);

public slots:
	void setFollow(bool on);

private slots:
  void onRangeChanged(AbstractLinesProvider::Range r, bool invalidate);
	void onScrollAction(int action);
	void onScrollValueChanged(int val);

private:
  Ui::LogViewport ui;

  AbstractLinesProvider* provider_;
	bool follow_;

	struct BlockInfo {
		AbstractLinesProvider::LineInfo info;
		int64_t nDisplayLines;
	};

	std::list<BlockInfo> blocks_;
	quint64 totalDisplayLines;
};

#endif // LOGVIEWPORT_H
