#include "FileLinesProvider.h"
#include <assert.h>
#include <QtCore/QDebug>

static const int checkIntervalMs = 333;
static const int64_t readBlock = 50 * 1024;

FileLinesProvider::FileLinesProvider(QObject *parent)
  : AbstractLinesProvider(parent)
  , range_(0, 0)
  , cur_(cache_.begin())
{
  connect(&watcher_, &QFileSystemWatcher::fileChanged, this, &FileLinesProvider::onFileChanged);
}

QString FileLinesProvider::path() const {
  return path_;
}

bool FileLinesProvider::setFile(QString new_path) {
  if (path_ == new_path) return true;

  auto new_file = file_t::create(new_path);
  if (!new_file->open(QIODevice::ReadOnly)) {
    return false;
  }

  if (!watcher_.addPath(new_path)) return false;

  // we are ok
  file_ = new_file;
  watcher_.removePath(path_);
  if (path_.isNull()) startTimer(checkIntervalMs);  // start timer when first file is set
  path_ = new_path;

  onFileChanged();
  return true;
}

void FileLinesProvider::onFileChanged() {
  assert(file_);
  auto newSize = file_->size();
  if (range_.second == newSize) return;
  
  bool invalidate = newSize < range_.second;
  range_.second = newSize;
  emit rangeChanged(range_, invalidate);
}

void FileLinesProvider::timerEvent(QTimerEvent *) {
  onFileChanged();
}

AbstractLinesProvider::Range FileLinesProvider::range() const {
  return range_;
}

template<typename C>
bool checkLineEnd(const C& c, typename C::const_iterator pos, typename C::const_iterator& outLineDataEnd, typename C::const_iterator& outLineEnd) {
  if (pos == c.end()) return false;
  if(*pos == '\n') {
    outLineEnd = pos + 1;
  }
  else if(*pos == '\r') {
    if (pos + 1 != c.end() && *(pos + 1) == '\n') {
      outLineEnd = pos + 2;
    }
    else {
      outLineEnd = pos + 1;
    }
  }
  else {
    return false;
  }

  outLineDataEnd = pos;
  return true;
}

bool FileLinesProvider::seek(int64_t pos) {
  {
    auto i = cache_.find(pos);
    if (i != cache_.end()) {
      cur_ = i;
      return true; // already cached
    }
  }
  
  if (!file_->seek(pos)) return false;

  cache_.clear();

  file_->seek(qMax(0ll, pos - readBlock / 2));
  readAndCacheLines(readBlock);

  auto i = cache_.find(pos);
  cur_ = i;
  return true;
}

bool FileLinesProvider::hasNext() const {
  return range_.first != range_.second && (cur_ != cache_.cend() || cache_.lastKey().second < range_.second);
}

AbstractLinesProvider::LineInfo FileLinesProvider::next() {
  if (cur_ != cache_.cend()) return *cur_++;
  auto curPos = cache_.lastKey().second;
  if (curPos >= file_->size() || !file_->seek(cur_.key().second)) return LineInfo();

  // add new lines
  readAndCacheLines(readBlock / 2);

  // remove excess lines
  for (;;) {
    auto cachedRange = cache_.lastKey().second - cache_.firstKey().first;
    auto firstSize = cache_.firstKey().size();

    if (cachedRange - firstSize >= readBlock) cache_.erase(cache_.begin());
    else break;
  }

  cur_ = cache_.find(curPos);
  assert(cur_ != cache_.cend());
  return *cur_++;
}

bool FileLinesProvider::hasPrev() const {
  return range_.first != range_.second && ( cur_ != cache_.cbegin() || cache_.firstKey().first > range_.first);
}

AbstractLinesProvider::LineInfo FileLinesProvider::prev() {
  if (cur_ != cache_.cbegin()) return *--cur_;
  auto curEndPos = cache_.firstKey().first;
  auto begRead = qMax(0ll, curEndPos - readBlock / 2);
  if (curEndPos <= 0 || !file_->seek(begRead)) return LineInfo();

  // add new lines
  readAndCacheLines(curEndPos - begRead);

  // remove excess lines
  for (;;) {
    auto cachedRange = cache_.lastKey().second - cache_.firstKey().first;
    auto lastSize = cache_.lastKey().size();

    if (cachedRange - lastSize >= readBlock) cache_.erase(cache_.end()-1);
    else break;
  }

  cur_ = cache_.find(curEndPos);
  assert(cur_ != cache_.cbegin());
  return *--cur_;
}

void FileLinesProvider::readAndCacheLines(int64_t bytes) {
  int64_t dataBegAbs = file_->pos();
  const auto data = file_->read(bytes);
  decltype(data.cbegin()) beg = data.cend(), end, lineDataEnd; // lineDataEnd points to the first newline character (after line contents)
	if (dataBegAbs == 0) beg = data.cbegin();	// we are at line start if we are at file start
  for (auto i = data.cbegin(); i != data.cend();) {
    auto atLineEnd = checkLineEnd(data, i, lineDataEnd, end);
    if (atLineEnd) {
      if (beg == data.cend() && i != data.cend() - 1) beg = end;	// if beg is invalid and we are not at buffer end
      else {
        int64_t rangeBeg = dataBegAbs + (beg - data.cbegin());
        int64_t rangeEnd = rangeBeg + (end - beg);
				Range range(rangeBeg, rangeEnd);
				cache_[range] = LineInfo(range, rangeBeg, QString::fromUtf8(beg, lineDataEnd - beg));
        beg = end;
      }
      i = end;
    }
    else {
      ++i;
    }
  }
  if (beg != data.cend()) {  // file does not end on line break
    int64_t rangeBeg = dataBegAbs + (beg - data.cbegin());
    int64_t rangeEnd = range_.second;
		Range range(rangeBeg, rangeEnd);
		cache_[range] = LineInfo(range, rangeBeg, QString::fromUtf8(beg, data.cend() - beg));
  }
}
