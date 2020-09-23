#include "UpdateWorker.hpp"

#include "StopwatchWidget.hpp"

namespace stopwatch {

const QString UpdateWorker::TIME_FORMAT("%1s:%2");
const QChar UpdateWorker::FILL_CHAR('0');

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

        this->timeString_ = TIME_FORMAT.arg(secondsElapsed, 2, 10, FILL_CHAR)
                                .arg(startedMillis, 3, 10, FILL_CHAR);
        this->stopwatch_->ui_.timeLabel->setText(this->timeString_);

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
