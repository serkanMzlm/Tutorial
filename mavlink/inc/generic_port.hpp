#ifndef __GENERIC_PORT_H__
#define __GENERIC_PORT_H__

#include <stdio.h>
#include <fcntl.h>  // File control definitions
#include <pthread.h>

#include <cstdlib>

#include "mavlink/common/mavlink.h"

class GenericPort
{
public:
    GenericPort(){};
    virtual ~GenericPort(){};
    virtual int readMessage(mavlink_message_t &msg) = 0;
    virtual int writeMessage(const mavlink_message_t &msg) = 0;
    virtual bool isRunning() = 0;
    virtual void start() = 0;
    virtual void stop() = 0;
};

#endif