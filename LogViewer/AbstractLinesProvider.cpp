#include "AbstractLinesProvider.h"

AbstractLinesProvider::AbstractLinesProvider(QObject *parent)
  : QObject(parent)
{}

AbstractLinesProxy::AbstractLinesProxy(QObject *parent)
: AbstractLinesProvider(parent)
{}

void AbstractLinesProxy::setProvider(QSharedPointer<AbstractLinesProvider> _provider) {
  clearProvider();
  provider = _provider;
  connect(provider.data(), &AbstractLinesProvider::rangeChanged, this, &AbstractLinesProxy::handleRangeChanged);
}

void AbstractLinesProxy::clearProvider() {
  if (provider) {
    disconnect(provider.data(), 0, this, 0);
    provider.clear();
  }
}
