#include "UpdateWorker.hpp"

#include "StopwatchWidget.hpp"

namespace stopwatch {

UpdateWorker::UpdateWorker(StopwatchWidget *stopwatch, QObject *parent)
    : QObject(parent)
    , stopwatch_(stopwatch)
    , timer_()
{
    QObject::connect(this->stopwatch_, &StopwatchWidget::startRequested, this,
                     &UpdateWorker::start);
}

void UpdateWorker::start()
{
    static const QChar fill('0');

    // Account for different interfaces for starting and restarting
    if (!this->timer_.isValid())
        this->timer_.start();
    else
        this->timer_.restart();

    while (!QThread::currentThread()->isInterruptionRequested())
    {
        const qint64 millisElapsed = this->timer_.elapsed();
        const qint64 secondsElapsed = millisElapsed / 1000;
        const qint64 startedMillis = millisElapsed % 1000;

        const auto timeString = QString("%1s:%2")
                                    .arg(secondsElapsed, 2, 10, fill)
                                    .arg(startedMillis, 3, 10, fill);
        this->stopwatch_->ui_.timeLabel->setText(timeString);
    }

    QThread::currentThread()->quit();
}

}  // namespace stopwatch
