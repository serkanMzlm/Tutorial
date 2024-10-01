#include "serial_comm.h"

SerialComm::SerialComm(QObject *parent)
    : QObject{parent}
{
    port_ = new QSerialPort(this);
    debugPort();
}

SerialComm::~SerialComm()
{
    port_->close();
}

void SerialComm::checkDeviceConnection()
{
    for(const QSerialPortInfo port_list : QSerialPortInfo::availablePorts()){
        bool is_found = ((port_list.manufacturer() == "FTDI") ||
                         (port_list.description() == "Arduino Mega 2560"));
        if(is_found){
            port_->setPortName(port_list.portName());
            port_->setBaudRate(BAUDRATE);
            port_->setDataBits(QSerialPort::Data8);
            while(port_->open(QIODevice::ReadWrite)){ }
            QThread::sleep(1);
        }
    }
}

void SerialComm::readBytes()
{
}

void SerialComm::writeBytes(uint8_t new_data)
{
    if ( !(port_->isOpen()))
    {
        return ;
    }
    port_->write((char*)(new_data), 1);
    port_->flush();
}

void SerialComm::debugPort(){
    for(const QSerialPortInfo port_list : QSerialPortInfo::availablePorts()){
        if(port_list.description() == "") continue;
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
