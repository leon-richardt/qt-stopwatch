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
    ~UpdateWorker() = default;

public slots:
    void start();

private:
    static const QString TIME_FORMAT;
    static const QChar FILL_CHAR;

    StopwatchWidget *stopwatch_{};
    QElapsedTimer timer_;
    QString timeString_;
};

}  // namespace stopwatch
