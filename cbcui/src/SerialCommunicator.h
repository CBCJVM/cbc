#ifndef SERIALCOMMUNICATOR_H
#define SERIALCOMMUNICATOR_H

#include <QThread>

#define SERIAL_MESSAGE_OK   ((quint8)1)
#define SERIAL_MESSAGE_FAIL ((quint8)2)
#define SERIAL_START        ((quint16)0xCBC)

#define HEADER_KEY (quint32)(0xB07BA11)
#define SERIAL_DEVICE "/dev/uart0"
#define TEMP_PATH "/tmp/upload"

class SerialCommunicator : public QThread
{
public:
    virtual void stop() = 0;
};

#endif // SERIALCOMMUNICATOR_H
