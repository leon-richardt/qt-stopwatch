#pragma once

#include <QLabel>
#include <QThread>
#include <QWidget>

namespace stopwatch {

class UpdateWorker;

class StopwatchWidget : public QWidget
{
    Q_OBJECT

public:
    StopwatchWidget(QWidget *parent = nullptr);
    ~StopwatchWidget();

    void start();
    void stop();
    bool running() const;

signals:
    void startRequested();

private:
    QThread updateThread_;
    UpdateWorker *worker_{};

    bool running_{};

    struct {
        QLabel *timeLabel{};
    } ui_;

    friend class UpdateWorker;
};

}  // namespace stopwatch
