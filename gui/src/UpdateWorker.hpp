#pragma once

#include <QElapsedTimer>
#include <QObject>

namespace stopwatch {

class StopwatchWidget;

class UpdateWorker : public QObject
{
    Q_OBJECT

public:
    UpdateWorker(StopwatchWidget *stopwatch, QObject *parent = nullptr);

public slots:
    void start();

private:
    StopwatchWidget *stopwatch_{};
    QElapsedTimer timer_;
};

}  // namespace stopwatch
