#include "StopwatchWidget.hpp"

#include "UpdateWorker.hpp"

#include <QVBoxLayout>

namespace stopwatch {

StopwatchWidget::StopwatchWidget(QWidget *parent)
    : QWidget(parent)
    , updateThread_(this)
{
    this->worker_ = new UpdateWorker(this);
    this->worker_->moveToThread(&this->updateThread_);
    this->updateThread_.start();

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
    this->stop();
    this->updateThread_.wait();
}

void StopwatchWidget::start()
{
    this->running_ = true;
    emit startRequested();
}

void StopwatchWidget::stop()
{
    this->running_ = false;
    this->updateThread_.requestInterruption();
}

bool StopwatchWidget::running() const
{
    return this->running_;
}

}  // namespace stopwatch
