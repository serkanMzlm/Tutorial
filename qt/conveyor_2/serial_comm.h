#ifndef SERIAL_COMM_H
#define SERIAL_COMM_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QThread>
#include <QDebug>

#define BAUDRATE 115200

class SerialComm : public QObject
{
    Q_OBJECT
private:
    QSerialPort *port_;
public:
    explicit SerialComm(QObject *parent = nullptr);
    ~SerialComm();
    void checkDeviceConnection();
    void readBytes();
    Q_INVOKABLE void writeBytes(uint8_t new_data = 0x11);
    Q_INVOKABLE void debugPort();
signals:
};

#endif // SERIAL_COMM_H
