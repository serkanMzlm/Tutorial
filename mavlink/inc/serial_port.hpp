#ifndef __SERIAL_PORT_HPP__
#define __SERIAL_PORT_HPP__

#include <unistd.h>
#include <signal.h>
#include <termios.h>

#include "generic_port.hpp"

#ifndef B460800
#define B460800 460800
#endif

#ifndef B921600
#define B921600 921600
#endif

class SerialPort: public GenericPort
{
public:
    SerialPort();
    SerialPort(const char *uart_name, int baudrate);
    virtual ~SerialPort();

    int readMessage(mavlink_message_t &msg);
    int writeMessage(const mavlink_message_t &msg);
    bool isRunning();
    void start();
    void stop();

private:
    int fd;
    int baudrate;
    bool debug;
    bool is_open;
    const char* uart_name;

    mavlink_status_t last_status;
    pthread_mutex_t lock;

    void initialize();
    int _openPort(const char* port);
    int  _readPort(uint8_t &cp);
	int _writePort(char *buf, unsigned len);
    bool _setupPort(int baud, int data_bits, int stop_bits, bool parity, bool hardware_control);
};

#endif // __SERIAL_PORT_HPP__