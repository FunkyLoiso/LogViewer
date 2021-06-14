#include "SpeedtestLinesProvider.h"
#include <QtCore/QDateTime>

SpeedtestLinesProvider::SpeedtestLinesProvider(QObject* parent)
	:	AbstractLinesProvider(parent)
{
}

SpeedtestLinesProvider::~SpeedtestLinesProvider()
{
	if (thread_)
	{
		stop();
	}
}

void SpeedtestLinesProvider::start(std::chrono::nanoseconds delay)
{
	assert(!thread_);
	stop_flag_ = false;
	thread_.reset(QThread::create(&SpeedtestLinesProvider::run, this, delay));
	//this->moveToThread(thread_.get());
	thread_->start();
}

void SpeedtestLinesProvider::stop()
{
	if (!thread_) 
	{
		return;
	}
	stop_flag_ = true;
	thread_->wait();
	thread_.reset();
}

AbstractLinesProvider::Range SpeedtestLinesProvider::range() const
{
	return range_;
}

bool SpeedtestLinesProvider::seek(int64_t pos)
{
	if (pos < range_.first || pos > range_.second)
	{
		return false;
	}
	cur_ = pos;
	return false;
}

bool SpeedtestLinesProvider::hasNext() const
{
	return range_.first != range_.second && cur_ < range_.second-1;
}

AbstractLinesProvider::LineInfo SpeedtestLinesProvider::next()
{
	auto str = QDateTime::currentDateTime().toString("hh:mm:ss.zzz") + ":{ 0x7FB62CCD9700 } [DBG] <msnd> line #0(0x7fb628002600) - flush up to 6.980 sec.";
	auto line =  LineInfo{
		Range{cur_, cur_ + str.size()},
		cur_,
		str
	};
	cur_ += str.size();
	return line;
}

bool SpeedtestLinesProvider::hasPrev() const
{
	return range_.first != range_.second && cur_ > range_.first;
}

AbstractLinesProvider::LineInfo SpeedtestLinesProvider::prev()
{
	auto str = QDateTime::currentDateTime().toString("hh:mm:ss.zzz") + ":{ 0x7FB62CCD9700 } [DBG] <msnd> line #0(0x7fb628002600) - flush up to 6.980 sec.";
	auto line = LineInfo{
		Range{cur_ - str.size(), cur_},
		cur_ - str.size(),
		str
	};
	cur_ -= str.size();
	return line;
}

void SpeedtestLinesProvider::run(std::chrono::nanoseconds delay)
{
	using clock_t = std::chrono::high_resolution_clock;
	auto next = clock_t::now();
	while (!stop_flag_) 
	{
		range_.second += strlen("15:40:22.261:{ 0x7FB62CCD9700 } [DBG] <msnd> line #0(0x7fb628002600) - flush up to 6.980 sec.");
		emit rangeChanged(range_, false);
		next += delay;
		std::this_thread::sleep_until(next);
	}
}
