#ifndef BETASERVER_H
#define BETASERVER_H

#include "SerialCommunicator.h"
#include "SerialPort.h"
#include <QDataStream>

#define COMMAND     1 // Run a command on the CBC
#define CBCUI       2 // Modify CBCUI's state
#define DOWNLOAD    3 // Download a file to a specific path
#define TOO_HIGH    4 // Denotes beginning of invalid types

class BetaServer : public SerialCommunicator
{
public:
    BetaServer(QObject* parent = 0);
    ~BetaServer();

    void run();
    void stop();

private:

    bool readPacket(QByteArray* packetData);
    bool writePacket(QByteArray* packetData);
    bool checkAck();
    void sendAck();
    void processPacket(QByteArray* packet);

    void doCommand(char* data, quint16 len);
    void doCbcui(char* data, quint16 len);
    void doFile(char* data, quint16 len);

    SerialPort m_port;
    QDataStream m_stream;
    bool m_quit;
};

#endif // BETASERVER_H
