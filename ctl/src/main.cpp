#include <QLocalSocket>

enum class Message : char { STOP = 0, START = 1 };
enum class Response : char { OK = 0, ERROR = 1 };

constexpr char const *SERVER_NAME = "stopwatch";

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        qCritical("Wrong syntax, supply a message to send.");
        return 1;
    }

    QLocalSocket socket;
    socket.connectToServer(SERVER_NAME);
    if (!socket.waitForConnected(1000))
    {
        qCritical("Could not connect to server %s.", SERVER_NAME);
        return 1;
    }

    const QString command(argv[1]);
    char commandData;
    if (command == "stop")
    {
        commandData = static_cast<char>(Message::STOP);
        socket.write(&commandData, 1);
    }
    else if (command == "start")
    {
        commandData = static_cast<char>(Message::START);
        socket.write(&commandData, 1);
    }
    else
    {
        qCritical("%s is not a valid command.", qUtf8Printable(command));
        return 1;
    }

    if (!socket.waitForBytesWritten(1000))
    {
        qCritical("Error while sending command: %s",
                  qUtf8Printable(socket.errorString()));
        return 1;
    }

    if (!socket.waitForReadyRead(1000))
    {
        qCritical("Error while waiting for answer: %s",
                  qUtf8Printable(socket.errorString()));
        return 1;
    }

    char responseData;
    const qint64 read = socket.read(&responseData, 1);
    if (read != 1)
    {
        qCritical("Invalid answer received.");
        return 1;
    }

    const auto response = static_cast<Response>(responseData);
    if (response == Response::OK)
    {
        return 0;
    }
    else if (response == Response::ERROR)
    {
        qCritical("GUI reported an error.");
        return 1;
    }
    else
    {
        qCritical("Invalid answer received.");
        return 1;
    }
}
