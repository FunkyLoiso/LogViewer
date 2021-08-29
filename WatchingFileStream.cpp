#include "WatchingFileStream.h"

static constexpr int checkIntervalMs = 333;
static constexpr int64_t readBlock = 50 * 1024;

WatchingFileStream::WatchingFileStream(QObject* parent)
  : Stream(parent)
{
  connect(&watcher_, &QFileSystemWatcher::fileChanged, this, &WatchingFileStream::onFileChanged);
}

bool WatchingFileStream::setFile(QString new_path) {
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

QString WatchingFileStream::path() const {
  return QString();
}

bool WatchingFileStream::seek(int64_t) {
  return false;
}

RangeChangedEmiter::Range WatchingFileStream::range() const {
  return {};
}

void WatchingFileStream::onFileChanged() {
  assert(file_);
  auto newSize = file_->size();
  if (range_.second == newSize) return;

  bool invalidate = newSize < range_.second;
  range_.second = newSize;
  emit rangeChanged(range_, Invaldate::yes);
}
