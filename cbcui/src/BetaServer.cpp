#include "BetaServer.h"
#include <QDebug>

BetaServer::BetaServer(QObject* parent)
    :   m_port(SERIAL_DEVICE, 0),
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

    qWarning("BetaServer started");
    QByteArray packet;
    while (!m_quit) {
        packet.clear();
        if(readPacket(&packet)) {
            processPacket(&packet);
        }
    }
    m_quit = false;
    m_port.close();
}

void BetaServer::stop()
{
    m_quit = 1;
    qWarning("BetaServer stopped");
}

void BetaServer::processPacket(QByteArray* packet)
{
    packet->chop(1); // Get rid of null term
    qWarning() << packet->size();
    for(quint16 i = 0; i < packet->size(); ++i) {
       printf("%x ", packet->data()[i]);
    }
    printf("\n");

    QDataStream stream(*packet);

    quint8 type = 0;
    quint16 len = 0;

    stream >> type;

    if(type >= TOO_HIGH || type < 1) {
        qWarning("Invalid packet type");
        return;
    }

    stream >> len;
    qWarning() << "Packet Data len: " << len;

    char data[len];
    if(stream.readRawData(data, len) == -1) {
        qWarning("Error reading data from stream");
    }

    qWarning() << data;

    switch(type) {
    case COMMAND:
        doCommand(data, len);
        break;
    case CBCUI:
        doCbcui(data, len);
        break;
    case DOWNLOAD:
        doFile(data, len);
        break;
    }
}

void BetaServer::doCommand(char* data, quint16 len)
{
    char dataNullTerm[len + 1];
    memcpy(dataNullTerm, data, len);
    dataNullTerm[len] = 0;

    FILE* in;

    if (!(in = popen(dataNullTerm, "r"))) {
        qWarning() << "Unable to invoke " << dataNullTerm;
    }

    QString output;
    char buff[512];
    while (fgets(buff, sizeof(buff), in) != NULL ) {
        output += buff;
    }

    pclose(in);

    QByteArray oArray(output.toAscii(), output.size());

    qWarning() << output;

    writePacket(&oArray);
}

void BetaServer::doCbcui(char* data, quint16 len)
{

}

void BetaServer::doFile(char* data, quint16 len)
{
    QByteArray array(data, len);
    QDataStream stream(array);

    quint16 pathLen = 0;
    stream >> pathLen;

    char path[pathLen + 1];
    stream.readRawData(path, pathLen);
    path[pathLen] = 0;

    qWarning() << path;

    quint16 fileLen = 0;
    stream >> fileLen;
    char file[fileLen];
    stream.readRawData(file, fileLen);

    FILE* pFile = fopen(path, "w");
    if(pFile == NULL) {
        qWarning() << "Error opening" << path << "for writing";
    }

    fwrite(file, 1, fileLen, pFile);

    fclose(pFile);
}

bool BetaServer::writePacket(QByteArray* data)
{
    qWarning("writePacket()");
    qWarning() << data->constData();
    for(int i = 0;i < 5;i++) {
        m_stream << HEADER_KEY;
        m_stream << data->size();
        m_stream.writeRawData(data->constData(), data->size());
        if(checkAck()) {
            qWarning("Acked!");
            return true;
        }
    }
    return false;
}

bool BetaServer::readPacket(QByteArray *packetData)
{
    qWarning("BetaServer::readPacket");
    while(1){
        QByteArray data;
        quint32 key = 0;
        quint16 checksum = 0xFFFF;

        qWarning("reading stream");
        m_stream >> key;
        qWarning("checking key");
        if (key == HEADER_KEY) {
            m_stream >> data;
            qWarning("data.size()=%d", data.size());
            *packetData = data;
            sendAck();
            return true;
        }
        m_stream.skipRawData(512);
        m_stream.resetStatus();
        qWarning("Retry...");
        if(m_quit) return false;
    }
    return false;
}

bool BetaServer::checkAck()
{
    qWarning("checkAck()");
    quint8 ret = 0;
    m_stream >> ret;
    if(ret == SERIAL_MESSAGE_OK)
        return true;
    return false;
}

void BetaServer::sendAck()
{
    m_stream << SERIAL_MESSAGE_OK;
}
