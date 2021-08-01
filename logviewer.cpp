#include "logviewer.h"
#include <QtGui/QTextBlock>
#include "FileLinesProvider.h"
#include "SpeedtestLinesProvider.h"

static const QString filePath = R"(c:\!temp\serv13-us5-ims-msk_VGW_20210527_0002.txt)";

LogViewer::LogViewer(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

  //auto testProvider = new FileLinesProvider(this);
  //testProvider->setFile(filePath);
  auto testProvider = new SpeedtestLinesProvider(this);

  ui.tab->logViewport->setProvider(testProvider);
  testProvider->start(std::chrono::microseconds(500));
}

LogViewer::~LogViewer()
{
}
