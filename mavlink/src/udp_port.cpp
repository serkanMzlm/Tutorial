#include "udp_port.hpp"

UDP_Port::UDP_Port()
{
	initialize();
}

UDP_Port::UDP_Port(const char *target_ip, int udp_port)
{
	initialize();
	this->target_ip = target_ip;
	this->rx_port  = udp_port;
	is_open = false;
}

UDP_Port::~UDP_Port()
{
	pthread_mutex_destroy(&lock);
}

int UDP_Port::readMessage(mavlink_message_t &message)
{
	uint8_t          cp;
	mavlink_status_t status;
	uint8_t          msg_received = false;

	int result = _readPort(cp);

	if (result > 0)
	{
		msg_received = mavlink_parse_char(MAVLINK_COMM_1, cp, &message, &status);

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
		fprintf(stderr, "ERROR: Could not read, res = %d, errno = %d : %m\n", result, errno);
	}

	if(msg_received && debug)
	{
		printf("Received message from UDP with ID #%d (sys:%d|comp:%d):\n", message.msgid, message.sysid, message.compid);

		fprintf(stderr,"Received UDP data: ");
		unsigned int i;
		uint8_t buffer[MAVLINK_MAX_PACKET_LEN];

		unsigned int message_length = mavlink_msg_to_send_buffer(buffer, &message);

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

int UDP_Port::writeMessage(const mavlink_message_t &message)
{
	char buf[300];
	unsigned len = mavlink_msg_to_send_buffer((uint8_t*)buf, &message);
	int bytes_written = _writePort(buf,len);
	if(bytes_written < 0){
		fprintf(stderr, "ERROR: Could not write, res = %d, errno = %d : %m\n", bytes_written, errno);
	}

	return bytes_written;
}

bool UDP_Port::isRunning()
{
    return is_open;
}

void UDP_Port::start()
{

	sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock < 0)
	{
		perror("error socket failed");
		throw EXIT_FAILURE;
	}

	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(target_ip);;
	addr.sin_port = htons(rx_port);

	if (bind(sock, (struct sockaddr *) &addr, sizeof(struct sockaddr)))
	{
		perror("error bind failed");
		close(sock);
		sock = -1;
		throw EXIT_FAILURE;
	}

	printf("Listening to %s:%i\n\n", target_ip, rx_port);
	last_status.packet_rx_drop_count = 0;

	is_open = true;
}

void UDP_Port::stop()
{
	printf("Close UDP Port\n\n");

	int result = close(sock);
	sock = -1;

	if ( result )
	{
		fprintf(stderr,"WARNING: Error on port close (%i)\n", result );
	}

	is_open = false;
}
void UDP_Port::initialize()
{
	// Initialize attributes
	target_ip = "127.0.0.1";
	rx_port  = 14550;
	tx_port  = -1;
	is_open = false;
	debug = false;
	sock = -1;

	// Start mutex
	int result = pthread_mutex_init(&lock, NULL);
	if ( result != 0 )
	{
		printf("\n mutex init failed\n");
		throw 1;
	}
}

int UDP_Port::_readPort(uint8_t &cp)
{

	socklen_t len;

	// Lock
	pthread_mutex_lock(&lock);

	int result = -1;
	if(buff_ptr < buff_len){
		cp=buff[buff_ptr];
		buff_ptr++;
		result=1;
	}else{
		struct sockaddr_in addr;
		len = sizeof(struct sockaddr_in);
		result = recvfrom(sock, &buff, BUFF_LEN, 0, (struct sockaddr *)&addr, &len);
		if(tx_port < 0){
			if(strcmp(inet_ntoa(addr.sin_addr), target_ip) == 0){
				tx_port = ntohs(addr.sin_port);
				printf("Got first packet, sending to %s:%i\n", target_ip, rx_port);
			}else{
				printf("ERROR: Got packet from %s:%i but listening on %s\n", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port), target_ip);
			}
		}
		if(result > 0){
			buff_len=result;
			buff_ptr=0;
			cp=buff[buff_ptr];
			buff_ptr++;
			//printf("recvfrom: %i %i\n", result, cp);
		}
	}

	// Unlock
	pthread_mutex_unlock(&lock);

	return result;
}

int UDP_Port::_writePort(char *buf, unsigned len)
{
	pthread_mutex_lock(&lock);

	int bytesWritten = 0;
	if(tx_port > 0){
		struct sockaddr_in addr;
		memset(&addr, 0, sizeof(addr));
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = inet_addr(target_ip);
		addr.sin_port = htons(tx_port);
		bytesWritten = sendto(sock, buf, len, 0, (struct sockaddr*)&addr, sizeof(struct sockaddr_in));
		//printf("sendto: %i\n", bytesWritten);
	}else{
		printf("ERROR: Sending before first packet received!\n");
		bytesWritten = -1;
	}

	pthread_mutex_unlock(&lock);
	return bytesWritten;
}
