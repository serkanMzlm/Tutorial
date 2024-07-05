#include "serial_port.hpp"

SerialPort::SerialPort()
{
    initialize();
}

SerialPort::SerialPort(const char* uart_name, int baudrate)
{
    initialize();
    this->uart_name = uart_name;
    this->baudrate = baudrate;

}

SerialPort::~SerialPort()
{
	pthread_mutex_destroy(&lock);
}

int SerialPort::readMessage(mavlink_message_t &msg)
{
    uint8_t cp;
    uint8_t msg_received = false;
    mavlink_status_t status;

    int result = _readPort(cp);
    if(result > 0)
    {
		msg_received = mavlink_parse_char(MAVLINK_COMM_1, cp, &msg, &status);
        if ( (last_status.packet_rx_drop_count != status.packet_rx_drop_count) && debug )
		{
			printf("ERROR: DROPPED %d PACKETS\n", status.packet_rx_drop_count);
			unsigned char v=cp;
			fprintf(stderr,"%02x ", v);
		}
		last_status = status;
    }
    else
	{
		fprintf(stderr, "ERROR: Could not read from fd %d\n", fd);
	}

    if(msg_received && debug)
	{
		printf("Received message from serial with ID #%d (sys:%d|comp:%d):\n", 
                                    msg.msgid, msg.sysid, msg.compid);

		fprintf(stderr,"Received serial data: ");
		unsigned int i;
		uint8_t buffer[MAVLINK_MAX_PACKET_LEN];

		unsigned int message_length = mavlink_msg_to_send_buffer(buffer, &msg);

		if (message_length > MAVLINK_MAX_PACKET_LEN)
		{
			fprintf(stderr, "\nFATAL ERROR: MESSAGE LENGTH IS LARGER THAN BUFFER SIZE\n");
		}

		else
		{
			for (i=0; i<message_length; i++)
			{
				unsigned char v=buffer[i];
				fprintf(stderr,"%02x ", v);
			}
			fprintf(stderr,"\n");
		}
	}

	return msg_received;
}

int SerialPort::writeMessage(const mavlink_message_t &msg)
{
    char buf[300];
	unsigned len = mavlink_msg_to_send_buffer((uint8_t*)buf, &msg);
	return _writePort(buf, len);
}

bool SerialPort::isRunning()
{
    return is_open;
}

void SerialPort::start()
{
	printf("Open Port\n");
    fd = _openPort(uart_name);

    if(fd == -1)
    {
        printf("failure, could not open port.\n");
        throw EXIT_FAILURE;
    }

	bool success = _setupPort(baudrate, 8, 1, false, false);
    if(!success)
    {
       printf("failure, could not configure port.\n");
		throw EXIT_FAILURE;
	}
	if (fd <= 0)
	{
		printf("Connection attempt to port %s with %d baud, 8N1 failed, exiting.\n", uart_name, baudrate);
		throw EXIT_FAILURE;
	}

    printf("Connected to %s with %d baud, 8 data bits, no parity, 1 stop bit (8N1)\n\n", uart_name, baudrate);
	last_status.packet_rx_drop_count = 0;

	is_open = true;
}

void SerialPort::stop()
{
    printf("Close Serial Port\n\n");

	int result = close(fd);

	if ( result )
	{
		fprintf(stderr,"WARNING: Error on port close (%i)\n", result );
	}

	is_open = false;
}

void SerialPort::initialize()
{
    debug = false;
    fd = -1;
    is_open = false;
    uart_name = (char*)"/dev/ttyUSB0";
    baudrate = 57600;

    int result = pthread_mutex_init(&lock, NULL);
    if(result != 0)
    {
        printf("\nmutex init faild!\n");
    }
}

int SerialPort::_openPort(const char* port)
{
	// O_RDWR - Read and write
	// O_NOCTTY - Ignore special chars like CTRL-C
	fd = open(port, O_RDWR | O_NOCTTY | O_NDELAY);

	if (fd == -1)
	{
		return -1;
	}

	else
	{
		fcntl(fd, F_SETFL, 0);
	}

	return fd;
}

int  SerialPort::_readPort(uint8_t &cp)
{
	pthread_mutex_lock(&lock);
	int result = read(fd, &cp, 1);
	pthread_mutex_unlock(&lock);

	return result;
}

int SerialPort::_writePort(char *buf, unsigned len)
{
	pthread_mutex_lock(&lock);
	const int bytesWritten = static_cast<int>(write(fd, buf, len));
	tcdrain(fd);
	pthread_mutex_unlock(&lock);

	return bytesWritten;

}

bool SerialPort::_setupPort(int baud, int data_bits, int stop_bits, bool parity, bool hardware_control)
{
    if(!isatty(fd))
	{
		fprintf(stderr, "\nERROR: file descriptor %d is NOT a serial port\n", fd);
		return false;
	}

	struct termios  config;
	if(tcgetattr(fd, &config) < 0)
	{
		fprintf(stderr, "\nERROR: could not read configuration of fd %d\n", fd);
		return false;
	}

	config.c_iflag &= ~(IGNBRK | BRKINT | ICRNL |
						INLCR | PARMRK | INPCK | ISTRIP | IXON);

	config.c_oflag &= ~(OCRNL | ONLCR | ONLRET |
						 ONOCR | OFILL | OPOST);

	#ifdef OLCUC
		config.c_oflag &= ~OLCUC;
	#endif

	#ifdef ONOEOT
		config.c_oflag &= ~ONOEOT;
	#endif

	config.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN | ISIG);
	config.c_cflag &= ~(CSIZE | PARENB);
	config.c_cflag |= CS8;
	config.c_cc[VMIN]  = 1;
	config.c_cc[VTIME] = 10; // was 0

    switch (baud)
	{
		case 1200:
			if (cfsetispeed(&config, B1200) < 0 || cfsetospeed(&config, B1200) < 0)
			{
				fprintf(stderr, "\nERROR: Could not set desired baud rate of %d Baud\n", baud);
				return false;
			}
			break;
		case 1800:
			cfsetispeed(&config, B1800);
			cfsetospeed(&config, B1800);
			break;
		case 9600:
			cfsetispeed(&config, B9600);
			cfsetospeed(&config, B9600);
			break;
		case 19200:
			cfsetispeed(&config, B19200);
			cfsetospeed(&config, B19200);
			break;
		case 38400:
			if (cfsetispeed(&config, B38400) < 0 || cfsetospeed(&config, B38400) < 0)
			{
				fprintf(stderr, "\nERROR: Could not set desired baud rate of %d Baud\n", baud);
				return false;
			}
			break;
		case 57600:
			if (cfsetispeed(&config, B57600) < 0 || cfsetospeed(&config, B57600) < 0)
			{
				fprintf(stderr, "\nERROR: Could not set desired baud rate of %d Baud\n", baud);
				return false;
			}
			break;
		case 115200:
			if (cfsetispeed(&config, B115200) < 0 || cfsetospeed(&config, B115200) < 0)
			{
				fprintf(stderr, "\nERROR: Could not set desired baud rate of %d Baud\n", baud);
				return false;
			}
			break;

		// These two non-standard (by the 70'ties ) rates are fully supported on
		// current Debian and Mac OS versions (tested since 2010).
		case 460800:
			if (cfsetispeed(&config, B460800) < 0 || cfsetospeed(&config, B460800) < 0)
			{
				fprintf(stderr, "\nERROR: Could not set desired baud rate of %d Baud\n", baud);
				return false;
			}
			break;
		case 921600:
			if (cfsetispeed(&config, B921600) < 0 || cfsetospeed(&config, B921600) < 0)
			{
				fprintf(stderr, "\nERROR: Could not set desired baud rate of %d Baud\n", baud);
				return false;
			}
			break;
		default:
			fprintf(stderr, "ERROR: Desired baud rate %d could not be set, aborting.\n", baud);
			return false;

			break;
	}

	if(tcsetattr(fd, TCSAFLUSH, &config) < 0)
	{
		fprintf(stderr, "\nERROR: could not set configuration of fd %d\n", fd);
		return false;
	}

	return true;
}

