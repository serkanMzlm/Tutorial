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
    Q_PROPERTY(bool isactive READ isactive WRITE setIsactive NOTIFY isactiveChanged FINAL)
public:
    explicit SerialComm(QObject *parent = nullptr);
    SerialComm(const SerialComm &) = delete;
    SerialComm(SerialComm &&) = delete;
    SerialComm &operator=(const SerialComm &) = delete;
    SerialComm &operator=(SerialComm &&) = delete;
    ~SerialComm();
    void checkDeviceConnection();
    void readBytes();
    Q_INVOKABLE void writeBytes(uint8_t new_data = 'p');
    void debugPort();
    void init();

    QString info() const;
    bool isready() const;
    bool isactive() const;
    void setInfo(const QString &newInfo);
    void setIsready(bool newIsready);
    void setIsactive(bool newIsactive);

private:
    QString m_info;
    QSerialPort *port;
    QTimer* connection_timer;

    bool m_isready;
    bool m_isactive;
    uint8_t time_coef = 1;
    int milliseconds = 1000;

    std::chrono::steady_clock::time_point prev_time;
    std::chrono::steady_clock::duration elapsed_time;

signals:
    void infoChanged();
    void isreadyChanged();
    void isactiveChanged();
};

#endif // SERIAL_COMM_H
