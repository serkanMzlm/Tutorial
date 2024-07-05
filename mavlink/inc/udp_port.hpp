#ifndef __UDP_PORT_HPP__
#define __UDP_PORT_HPP__

#include <time.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "generic_port.hpp"


class UDP_Port: public GenericPort
{
public:
	UDP_Port();
	UDP_Port(const char *target_ip, int udp_port);
	virtual ~UDP_Port();

	int readMessage(mavlink_message_t &message);
	int writeMessage(const mavlink_message_t &message);

	bool isRunning();
	void start();
	void stop();

private:

	int sock;
	int rx_port;
	int tx_port;
	int buff_ptr;
	int buff_len;
	const static int BUFF_LEN=2041;

	mavlink_status_t last_status;
	pthread_mutex_t  lock;

	bool debug;
	bool is_open;

	char buff[BUFF_LEN];
	const char *target_ip;

	void initialize();
	int  _readPort(uint8_t &cp);
	int _writePort(char *buf, unsigned len);
};

#endif