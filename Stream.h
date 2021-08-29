#pragma once

#include "RangeChangedEmiter.h"

class Stream: public RangeChangedEmiter {
  Q_OBJECT

public:
  Stream(QObject* parent)
    : RangeChangedEmiter(parent)
  {}
  virtual ~Stream() {};

  virtual bool seek(int64_t) = 0; // returns false if fails, position is not changed in that case
  virtual Range range() const = 0;
  bool empty() const {
    const auto [beg, end] = range();
    return beg == end;
  }
  explicit operator bool() const {
    return !empty();
  }
};