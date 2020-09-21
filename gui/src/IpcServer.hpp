#pragma once

#include "StopwatchWidget.hpp"

#include <QLocalServer>

namespace stopwatch {

enum class Message : char { STOP = 0, START = 1 };
enum class Response : char { OK = 0, ERROR = 1 };

class IpcServer : public QObject
{
    Q_OBJECT

public:
    static constexpr char const *SERVER_NAME = "stopwatch";

    IpcServer(StopwatchWidget *stopwatch, QObject *parent = nullptr);
    ~IpcServer();

    /**
     * @brief
     * Return `true` if the server could be started successfully;
     * `false` otherwise.
     */
    bool start();

    void stop();

private:
    void handleConnection();

    StopwatchWidget *stopwatch_{};
    QLocalServer *server_{};
};

}  // namespace stopwatch
