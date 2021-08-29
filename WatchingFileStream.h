#pragma once

#include <QtCore/QSharedPointer>
#include <QtCore/QFileSystemWatcher>
#include <QtCore/QFile>

#include "Stream.h"

class WatchingFileStream : public Stream {
  Q_OBJECT
public:
  WatchingFileStream(QObject* parent);

  bool setFile(QString path);
  QString path() const;

  virtual bool seek(int64_t) override; // returns false if fails, position is not changed in that case
  virtual Range range() const override;

private slots:
  void onFileChanged();

private:
  QFileSystemWatcher watcher_;
  typedef QSharedPointer<QFile> file_t;
  file_t file_;
  QString path_;
  Range range_{0, 0};

};