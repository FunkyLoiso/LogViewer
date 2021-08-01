#include "test_text.h"



test_text::test_text(QWidget* parent) : QWidget(parent) {

}

void test_text::setText(QString text) {
  text_ = text;
  this->update();
}

void test_text::paintEvent(QPaintEvent *event) {
  QPainter p(this);
  p.drawText(rect(), Qt::TextWordWrap, text_);
}
