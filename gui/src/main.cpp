#include <QApplication>

#include "IpcServer.hpp"
#include "StopwatchWidget.hpp"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    stopwatch::StopwatchWidget stopwatch;
    stopwatch::IpcServer server(&stopwatch);

    if (!server.start())
    {
        qCritical("Unable to start IPC server with name %s",
                  qUtf8Printable(stopwatch::IpcServer::SERVER_NAME));
        return 1;
    }

    stopwatch.show();

    return app.exec();
}
