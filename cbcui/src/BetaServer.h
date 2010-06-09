#ifndef BETASERVER_H
#define BETASERVER_H

#include "SerialCommunicator.h"
#include "SerialPort.h"

class BetaServer
{
public:
    BetaServer();

    void run();
    void stop();

private:

    SerialPort m_port;
    QDataStream m_stream;
    bool m_quit;
};

#endif // BETASERVER_H
