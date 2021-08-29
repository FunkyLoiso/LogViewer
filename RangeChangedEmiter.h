#pragma once

#include <QtCore/QObject>

class RangeChangedEmiter: public QObject {
  Q_OBJECT
public:
  RangeChangedEmiter(QObject* parent)
    : QObject(parent)
  {}
  using Range = std::pair<int64_t, int64_t>;
  enum class Invaldate {
    yes, no
  };
signals:
  void rangeChanged(Range, Invaldate);
};