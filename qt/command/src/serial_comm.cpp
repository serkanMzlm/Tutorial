#include "serial_comm.h"

SerialComm::SerialComm(QObject *parent)
    : QObject{parent}
{
    debugPort();
    init();

    connect(port, &QSerialPort::readyRead, this, &SerialComm::readBytes);
    connect(connection_timer, &QTimer::timeout, this, &SerialComm::checkDeviceConnection);
    connection_timer->start();
}

SerialComm::~SerialComm()
{
    port->close();
    delete connection_timer;
}

void SerialComm::init()
{
    m_isready = false;
    port = new QSerialPort(this);
    connection_timer = new QTimer(this);
    connection_timer->setInterval(1200);
    checkDeviceConnection();
}

void SerialComm::checkDeviceConnection()
{
    elapsed_time = std::chrono::steady_clock::now() - prev_time;
    bool is_found = false;
    if((elapsed_time.count()/1000000) < time_coef * TIME_OUT)
    {
        return ;
    }

    for(const QSerialPortInfo &port_list : QSerialPortInfo::availablePorts()){
        is_found = ((port_list.manufacturer() == "FTDI") ||
                         (port_list.description() == "Arduino Mega 2560") ||
                         (port_list.description() == "STLINK-V3") ||
                         (port_list.manufacturer() == "STMicroelectronics") ||
                         (port_list.description() == "USB-SERIAL CH340"));
        if(is_found && !port->isOpen()){
            prev_time = std::chrono::steady_clock::now();
            port->setPortName(port_list.portName());
            port->setBaudRate(BAUDRATE);
            port->setDataBits(QSerialPort::Data8);
            while(port->open(QIODevice::ReadWrite)){ }
            time_coef = 10;
#ifdef _WIN32
            Sleep(milliseconds);
#else
            usleep(milliseconds * 1000);
#endif
            qDebug() << "Connected with Device";
            setInfo("Connected with Device");
        }

    }
    if(!is_found && port->isOpen()) {
        qDebug() << "Device Connection Lost";
        setInfo("Device Connection Lost");
        port->close();
    }
}

void SerialComm::debugPort(){
    for(const QSerialPortInfo &port_list : QSerialPortInfo::availablePorts()){
        qDebug() << "-----------------------------------------------------";
        qDebug() << "portName:          " << port_list.portName();
        qDebug() << "systemLocation:    " << port_list.systemLocation();
        qDebug() << "description:       " << port_list.description();
        qDebug() << "manufacturer:      " << port_list.manufacturer();
        qDebug() << "serialNumber:      " << port_list.serialNumber();
        qDebug() << "vendorIdentifier:  " << port_list.vendorIdentifier();
        qDebug() << "productIdentifier: " << port_list.productIdentifier();
    }
}

void SerialComm::readBytes()
{
    while(port->bytesAvailable()){
        uint8_t cur_byte;
        port->read((char*)&cur_byte, 1);
        if(cur_byte == 46)
        {
            setIsready(true);
            setInfo("Click a Number");
        }
    }
}

void SerialComm::writeBytes(uint8_t new_data)
{
    if (!(port->isOpen()))
    {
        qDebug() << "Port Closed";
        return ;
    }

    if(!isready() && new_data !=  0x11)
    {
        return;
    }

    QString new_data_str = QString::fromStdString(std::to_string(static_cast<int>(new_data)));
    char dataToSend[1] = { static_cast<char>(new_data) };
    qint64 bytesWritten = port->write(dataToSend, 1);
    if (bytesWritten == -1) {
        qDebug() << "Could not write data to port: " << port->errorString();
    } else {
        port->flush();
    }
}

void SerialComm::setInfo(const QString &newInfo)
{
    if (m_info == newInfo)
        return;
    m_info = newInfo;
    emit infoChanged();
}

QString SerialComm::info() const { return m_info; }

bool SerialComm::isready() const
{
    return m_isready;
}

void SerialComm::setIsready(bool newIsready)
{
    if (m_isready == newIsready)
        return;
    m_isready = newIsready;
    emit isreadyChanged();
}
