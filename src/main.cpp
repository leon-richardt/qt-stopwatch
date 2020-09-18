#include <QApplication>

#include "StopwatchWidget.hpp"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    stopwatch::StopwatchWidget stopwatch;
    stopwatch.start();
    stopwatch.show();

    return app.exec();
}
