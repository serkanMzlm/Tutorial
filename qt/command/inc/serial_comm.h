#ifndef SERIAL_COMM_H
#define SERIAL_COMM_H

#include <QDebug>
#include <QTimer>
#include <QVector>
#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#define TIME_OUT 1500    // ms
#define BAUDRATE 115200

class SerialComm : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString info READ info WRITE setInfo NOTIFY infoChanged FINAL)
    Q_PROPERTY(bool isready READ isready WRITE setIsready NOTIFY isreadyChanged FINAL)

public:
    explicit SerialComm(QObject *parent = nullptr);
    SerialComm(const SerialComm &) = delete;
    SerialComm(SerialComm &&) = delete;
    SerialComm &operator=(const SerialComm &) = delete;
    SerialComm &operator=(SerialComm &&) = delete;
    ~SerialComm();
    void checkDeviceConnection();
    void readBytes();
    Q_INVOKABLE void writeBytes(uint8_t new_data = 0x11);
    void debugPort();
    void init();

    QString info() const;
    void setInfo(const QString &newInfo);

    bool isready() const;
    void setIsready(bool newIsready);

private:
    QString m_info;
    QSerialPort *port;
    QTimer* connection_timer;

    uint8_t time_coef = 1;
    int milliseconds = 1000;

    std::chrono::steady_clock::time_point prev_time;
    std::chrono::steady_clock::duration elapsed_time;
    bool m_isready;

signals:
    void infoChanged();
    void isreadyChanged();
};

#endif // SERIAL_COMM_H
