#include "BetaServer.h"

BetaServer::BetaServer()
    :   m_port(SERIAL_DEVICE, this),
    m_stream(&m_port),
    m_quit(false)
{
}

BetaServer::~BetaServer()
{
    stop();
}

void BetaServer::run()
{
    m_port.open(QIODevice::ReadWrite);
    mkdir(TEMP_PATH, 0);

    //qWarning("BetaServer::run() looping");
    QByteArray header;
    while (!m_quit) {
        header.clear();
        if(readPacket(&header)) {
            processTransfer(header);
        }
    }
    m_quit = false;
    m_port.close();
}

void BetaServer::stop()
{
    m_quit = 1;
    while(isRunning());
}
