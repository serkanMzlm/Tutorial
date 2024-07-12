#include <stdio.h>
#include <cstdlib>
#include <unistd.h>
#include <time.h>


#include <iostream>
#include <inttypes.h>
#include <cmath>
#include <string.h>

#include <fstream>
#include <signal.h>
#include <sys/time.h>

#include <mavlink/common/mavlink.h>

#include "autopilot_interface.h"
#include "serial_port.h"
#include "udp_port.h"

using std::string;
using namespace std;

int main(int argc, char **argv);
int top(int argc, char **argv);

void commands(Autopilot_Interface &autopilot_interface, bool autotakeoff);
void parse_commandline(int argc, char **argv, char *&uart_name, int &baudrate,
		bool &use_udp, char *&udp_ip, int &udp_port, bool &autotakeoff);

// quit handler
Autopilot_Interface *autopilot_interface_quit;
Generic_Port *port_quit;
void quit_handler( int sig );

