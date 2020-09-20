#include "StopwatchWidget.hpp"

#include "UpdateWorker.hpp"

#include <QVBoxLayout>

namespace stopwatch {

StopwatchWidget::StopwatchWidget(QWidget *parent)
    : QWidget(parent)
{
    this->ui_.timeLabel = new QLabel(this);
    this->ui_.timeLabel->setFont(QFont("Liberation Mono", 48, QFont::Bold));

    auto *layout = new QVBoxLayout;
    layout->setAlignment(Qt::AlignCenter);
    layout->addWidget(this->ui_.timeLabel);
    this->setLayout(layout);

    this->show();
}

StopwatchWidget::~StopwatchWidget()
{
    if (this->updateThread_)
    {
        this->updateThread_->requestInterruption();
        this->updateThread_->wait();

        if (this->worker_)
            this->worker_->deleteLater();

        this->updateThread_->deleteLater();
    }
}

void StopwatchWidget::start()
{
    if (this->running_)
    {
        this->stop();
    }

    this->updateThread_ = new QThread;
    this->worker_ = new UpdateWorker(this);
    this->worker_->moveToThread(this->updateThread_);

    this->updateThread_->start();
    this->running_ = true;
    emit startRequested();
}

void StopwatchWidget::stop()
{
    if (this->running_)
    {
        this->running_ = false;
        this->updateThread_->requestInterruption();

        QObject::connect(this->updateThread_, &QThread::finished, this->worker_,
                         &QObject::deleteLater);
        QObject::connect(this->updateThread_, &QThread::finished,
                         this->updateThread_, &QThread::deleteLater);
    }
}

bool StopwatchWidget::running() const
{
    return this->running_;
}

}  // namespace stopwatch
