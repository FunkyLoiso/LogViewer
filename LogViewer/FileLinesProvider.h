#ifndef FILELINESPROVIDER_H
#define FILELINESPROVIDER_H

#include "AbstractLinesProvider.h"
#include <QtCore/QFileSystemWatcher>
#include <QtCore/QFile>
#include <QtCore/QMap>

class FileLinesProvider : public AbstractLinesProvider
{
  Q_OBJECT

public:
  FileLinesProvider(QObject *parent);

  bool setFile(QString path);
  QString path() const;

  virtual Range range() const override;
  virtual bool seek(int64_t) override;
  virtual bool hasNext() const override;
  virtual LineInfo next() override;
  virtual bool hasPrev() const override;
  virtual LineInfo prev() override;

private slots:
  void onFileChanged();

private:
  QFileSystemWatcher watcher_;
  typedef QSharedPointer<QFile> file_t;
  file_t file_;
  QString path_;
  Range range_;

  // buffer
  Range bufferedRange_;

  // special modification of Range allowing single-value search among range keys
  struct CacheKey : public Range {
    CacheKey() = default;
    CacheKey(int64_t val) : Range(val, val) {} // implicit conversion from single value
    CacheKey(int64_t beg, int64_t end) : Range(beg, end) {}
		CacheKey(const Range& r) : Range(r) {}

    int64_t size() const { return second - first; }

    bool operator<(CacheKey& other) {
      if(other.first == other.second) { // we are single-value range
        if (other.first >= first && other.first < second) return false;
        else return second < other.first;
      }
      else if(first == second) {  // they are single-value range
        if (first >= other.first && first < other.second) return false;
        else return first < other.first;
      }
      else return second < other.first;
    }
  };
  typedef QMap<CacheKey, LineInfo> Cache;
  Cache cache_;
  Cache::const_iterator cur_;

  virtual void timerEvent(QTimerEvent *) override;

  void readAndCacheLines(int64_t bytes);
};

#endif // FILELINESPROVIDER_H
