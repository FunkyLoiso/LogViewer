#ifndef ABSTRACTLINESPROVIDER_H
#define ABSTRACTLINESPROVIDER_H

#include <QtCore/QObject>
#include <QtGui/QBrush>

class AbstractLinesProvider : public QObject {
  Q_OBJECT

public:
  using Range = QPair<int64_t, int64_t>;

  struct LineInfo {
  public:
	  Range range;    // the range in provider's range that this line correspond to
    int64_t block;   // line block start position in provider's range
    QString text;

    struct StyledRegion {
      int64_t beg, end;
      QBrush foreground, background;

      StyledRegion(int64_t _beg, int64_t _end, const QBrush& _background, const QBrush& _foreground = QBrush())
        : beg(_beg), end(_end), foreground(_foreground), background(_background) {}
    };

    QVector<StyledRegion> styledRegions;

    LineInfo()
      : range(0, 0), block(0) {}

    LineInfo(Range _range, int64_t _block, const QString& _text)
      : range(_range), block(_block), text(_text) {}

    explicit operator bool() const {
      return range != Range() || !text.isNull();
    }
  };

  AbstractLinesProvider(QObject *parent);
  virtual ~AbstractLinesProvider() {};

  virtual Range range() const = 0;  // if begin == end, the provider is empty
  virtual bool seek(int64_t) = 0; // returns false if fails, position is not changed in that case
  virtual bool hasNext() const = 0;
  virtual LineInfo next() = 0;
  virtual bool hasPrev() const = 0;
  virtual LineInfo prev() = 0;

signals:
  void rangeChanged(Range, bool); // second argument signals that the data must be invalidated

};

class AbstractLinesProxy : public AbstractLinesProvider {
  Q_OBJECT

public:
  AbstractLinesProxy(QObject *parent);
  void setProvider(QSharedPointer<AbstractLinesProvider> _provider);
  void clearProvider();

protected slots:
  virtual void handleRangeChanged(Range, bool) = 0;

private:
  QSharedPointer<AbstractLinesProvider> provider;
};

#endif // ABSTRACTLINESPROVIDER_H
