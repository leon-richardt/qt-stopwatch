#include "IpcServer.hpp"

#include <QLocalSocket>

namespace stopwatch {

IpcServer::IpcServer(StopwatchWidget *stopwatch, QObject *parent)
    : QObject(parent)
    , stopwatch_(stopwatch)
{
    this->server_ = new QLocalServer(this);

    QObject::connect(this->server_, &QLocalServer::newConnection, this,
                     &IpcServer::handleConnection);
}

IpcServer::~IpcServer()
{
    this->stop();
}

bool IpcServer::start()
{
    if (!this->server_->listen(SERVER_NAME))
    {
        qCritical("Error starting server: %s",
                  qUtf8Printable(this->server_->errorString()));
        return false;
    }

    return true;
}

void IpcServer::stop()
{
    this->server_->close();
    while (this->server_->hasPendingConnections())
    {
        this->handleConnection();
    }
}

void IpcServer::handleConnection()
{
    QLocalSocket *client = this->server_->nextPendingConnection();
    QObject::connect(client, &QLocalSocket::disconnected, client,
                     &QLocalSocket::deleteLater);

    if (!client->waitForReadyRead(1000))
    {
        qWarning("Client did not send any data.");
        // FIXME: close?
        return;
    }

    // We only need one byte for message passing
    char data;
    const qint64 read = client->read(&data, 1);
    if (read != 1)
    {
        qWarning("Error when receiving client command: %s",
                 qUtf8Printable(client->errorString()));
        // FIXME: close?
        return;
    }

    auto message = static_cast<Message>(data);

    auto response = Response::OK;
    switch (message)
    {
        case Message::STOP:
            this->stopwatch_->stop();
            break;
        case Message::START:
            this->stopwatch_->start();
            break;
        default:
            response = Response::ERROR;
            break;
    }

    char responseData = static_cast<char>(response);
    qint64 written = client->write(&responseData, 1);

    if (written != 1)
    {
        qWarning("Error occurred when sending resonse: %s",
                 qUtf8Printable(client->errorString()));
    }

    client->flush();
    client->disconnectFromServer();
}

}  // namespace stopwatch
