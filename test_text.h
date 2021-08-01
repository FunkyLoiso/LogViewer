#pragma once

#include <QtWidgets/QWidget>
#include <QtGui/QPainter>

class test_text : public QWidget {
  Q_OBJECT

public:
  test_text(QWidget* parent);

  void setText(QString text);

private:
  QString text_;
protected:
  virtual void paintEvent(QPaintEvent *event) override;

};

