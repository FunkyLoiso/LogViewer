#pragma once

#include <QtCore/QThread>
#include "AbstractLinesProvider.h"
class SpeedtestLinesProvider: public AbstractLinesProvider
{
public:
	SpeedtestLinesProvider(QObject* parent = 0);
	~SpeedtestLinesProvider();

public slots:
	void start(std::chrono::nanoseconds delay);
	void stop();

	// Inherited via AbstractLinesProvider
	virtual Range range() const override;
	virtual bool seek(int64_t) override;
	virtual bool hasNext() const override;
	virtual LineInfo next() override;
	virtual bool hasPrev() const override;
	virtual LineInfo prev() override;

private:
	void run(std::chrono::nanoseconds delay);

	std::unique_ptr<QThread> thread_;
	std::atomic_bool stop_flag_{ false };
	
	Range range_{0, 0};
	int64_t cur_{ 0 };
};

