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
    static const QString timeFormat("%1s:%2");

    // Account for different interfaces for starting and restarting
    if (!this->timer_.isValid())
        this->timer_.start();
    else
        this->timer_.restart();

    for (;; QThread::currentThread()->usleep(1000))
    {
        const qint64 millisElapsed = this->timer_.elapsed();
        const qint64 secondsElapsed = millisElapsed / 1000;
        const qint64 startedMillis = millisElapsed % 1000;

        const auto timeString = timeFormat.arg(secondsElapsed, 2, 10, fill)
                                    .arg(startedMillis, 3, 10, fill);
        this->stopwatch_->ui_.timeLabel->setText(timeString);

        // Only check approx. once per second to keep overhead low
        if (startedMillis == 0 &&
            QThread::currentThread()->isInterruptionRequested())
        {
            break;
        }
    }

    QThread::currentThread()->quit();
}

}  // namespace stopwatch
