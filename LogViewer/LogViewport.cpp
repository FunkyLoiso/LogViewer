#include "LogViewport.h"

#include <QtGui/QTextBlock>

#include <assert.h>

static const int scrollMin = 0;
static const int scrollMax = 10000;
static const double scrollRange = scrollMax - scrollMin;

LogViewport::LogViewport(QWidget *parent)
    : QWidget(parent)
    , provider_(nullptr)
		, follow_(true)
		, totalDisplayLines(0)
{
  ui.setupUi(this);

	connect(ui.textScrollBar, &QScrollBar::actionTriggered, this, &LogViewport::onScrollAction);
	connect(ui.textScrollBar, &QScrollBar::valueChanged, this, &LogViewport::onScrollValueChanged);

	ui.textScrollBar->setRange(scrollMin, scrollMax);	//scroll range is constant, it is than mapped to actual provider offsets
}

LogViewport::~LogViewport()
{

}

void LogViewport::setProvider(AbstractLinesProvider* provider) {
  assert(provider);
  if(provider_) {
    disconnect(provider_, 0, this, 0);
  }
  provider_ = provider;
  connect(provider_, &AbstractLinesProvider::rangeChanged, this, &LogViewport::onRangeChanged, Qt::QueuedConnection);
  onRangeChanged(provider_->range(), true);
}

void LogViewport::onRangeChanged(AbstractLinesProvider::Range r, bool invalidate) {  
	if (r.second <= r.first) {
		ui.textViewport->clear();
		blocks_.clear();
		return;
	}

	static auto last = std::chrono::high_resolution_clock::now();
	auto now = std::chrono::high_resolution_clock::now();
	if (now - last < std::chrono::milliseconds(1000/60))
	{	// too often
		return;
	}
	last = now;

	if (invalidate) {
		ui.textViewport->clear();
		blocks_.clear();
	}
	
	if (follow_) {
		provider_->seek(r.second);

		std::list<BlockInfo> newBlocks;
		quint64 totalNewDisplayLines = 0;
		const auto vrect = ui.textViewport->rect();
		const auto lineHeight = ui.textViewport->fontMetrics().lineSpacing();
		const auto optimalDisplayLines = vrect.height() / lineHeight + 10;
		auto heightLeft = optimalDisplayLines * lineHeight;
		bool keepOld = false;

		while (provider_->hasPrev() && heightLeft > 0) {
			auto lineInfo = provider_->prev();
			if (!blocks_.empty() && blocks_.back().info.range == lineInfo.range) {
				// line is already buffered, stop
				keepOld = true;
				break;
			}

			if (ui.textViewport->wordWrapMode() == QTextOption::NoWrap) {
				newBlocks.push_front({ lineInfo, 1 });
				heightLeft -= lineHeight;
				++totalNewDisplayLines;
			}
			else {
				auto lineRect = ui.textViewport->fontMetrics().boundingRect(vrect, Qt::TextWordWrap, lineInfo.text);
				auto nDisplayLines = lineRect.height() / lineHeight;
				newBlocks.push_front({ lineInfo, nDisplayLines });
				heightLeft -= lineRect.height();
				totalNewDisplayLines += nDisplayLines;
			}
		}

		if (keepOld) {
			auto cursor = QTextCursor(ui.textViewport->document());
			cursor.movePosition(QTextCursor::End);
			for (auto i = newBlocks.cbegin(); i != newBlocks.cend(); ++i) {
				cursor.insertBlock();
				//cursor.insertText(i->info.text);
				cursor.movePosition(QTextCursor::End);
			}
			blocks_.splice(blocks_.end(), newBlocks);
			totalDisplayLines += totalNewDisplayLines;

			// remove excess lines
			cursor.movePosition(QTextCursor::Start);
			for (auto i = blocks_.begin(); i != blocks_.end();) {
				if (totalDisplayLines - i->nDisplayLines > optimalDisplayLines) {
					totalDisplayLines -= i->nDisplayLines;
					i = blocks_.erase(i);
					cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
					cursor.removeSelectedText();
				}
				else break;
			}
		}
		else {
			ui.textViewport->clear();
			auto cursor = QTextCursor(ui.textViewport->document());
			for (auto i = newBlocks.cbegin(); i != newBlocks.cend(); ++i) {
				cursor.insertBlock();
				//cursor.insertText(i->info.text);
				cursor.movePosition(QTextCursor::End);
			}
			blocks_.swap(newBlocks);
			totalDisplayLines = totalNewDisplayLines;
		}

		//if (ui.textViewport->wordWrapMode() == QTextOption::NoWrap) {
		//	auto lineHeight = ui.textViewport->fontMetrics().lineSpacing();
		//	auto heightLeft = ui.textViewport->rect().height();

		//	while (provider_->hasPrev() && heightLeft > 0) {
		//		renderedText.prepend(provider_->prev().text);
		//		heightLeft -= lineHeight;
		//	}
		//}
		//else {
		//	QRect vrect = ui.textViewport->rect();

		//	auto heightLeft = vrect.height();
		//	while (provider_->hasPrev() && heightLeft > 0) {
		//		auto txt = provider_->prev().text;
		//		renderedText.prepend(txt + '\n');
		//		auto lineRect = ui.textViewport->fontMetrics().boundingRect(vrect, Qt::TextWordWrap, txt);
		//		heightLeft -= lineRect.height();
		//	}
		//}

		//ui.textViewport->setPlainText(renderedText);
		//ui.textViewport->verticalScrollBar()->setValue(ui.textViewport->verticalScrollBar()->maximum());

		// map text size to scrollbar range
		assert(!blocks_.empty());
		const double pageStep = scrollRange / (r.second - r.first) * (blocks_.back().info.range.second - blocks_.front().info.range.first);
		ui.textScrollBar->setPageStep(int(pageStep));
		ui.textScrollBar->setValue(ui.textScrollBar->maximum());

		ui.textViewport->verticalScrollBar()->setValue(ui.textViewport->verticalScrollBar()->maximum());
	}

}

void LogViewport::setFollow(bool on) {
	throw std::exception("The method or operation is not implemented.");

}

void LogViewport::onScrollAction(int action) {
	auto v = action;
}

void LogViewport::onScrollValueChanged(int val) {
	
}

