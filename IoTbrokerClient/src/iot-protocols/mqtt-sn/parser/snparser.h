/**
 * Mobius Software LTD
 * Copyright 2015-2018, Mobius Software LTD
 *
 * This is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2.1 of
 * the License, or (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this software; if not, write to the Free
 * Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA, or see the FSF site: http://www.fsf.org.
 */

#ifndef SNPARSER_H
#define SNPARSER_H

#include <cstring>
#include <cstdlib>
#include <list>
#include "utils/helpers.h"

#include "iot-protocols/classes/message.h"
#include "iot-protocols/mqtt-sn/messages/snadvertise.h"
#include "iot-protocols/mqtt-sn/messages/snconnack.h"
#include "iot-protocols/mqtt-sn/messages/snconnect.h"
#include "iot-protocols/mqtt-sn/messages/sndisconnect.h"
#include "iot-protocols/mqtt-sn/messages/snencapsulated.h"
#include "iot-protocols/mqtt-sn/messages/sngwinfo.h"
#include "iot-protocols/mqtt-sn/messages/snpingreq.h"
#include "iot-protocols/mqtt-sn/messages/snpingresp.h"
#include "iot-protocols/mqtt-sn/messages/snpuback.h"
#include "iot-protocols/mqtt-sn/messages/snpubcomp.h"
#include "iot-protocols/mqtt-sn/messages/snpublish.h"
#include "iot-protocols/mqtt-sn/messages/snpubrec.h"
#include "iot-protocols/mqtt-sn/messages/snpubrel.h"
#include "iot-protocols/mqtt-sn/messages/snregack.h"
#include "iot-protocols/mqtt-sn/messages/snregister.h"
#include "iot-protocols/mqtt-sn/messages/snsearchgw.h"
#include "iot-protocols/mqtt-sn/messages/snsuback.h"
#include "iot-protocols/mqtt-sn/messages/snsubscribe.h"
#include "iot-protocols/mqtt-sn/messages/snunsuback.h"
#include "iot-protocols/mqtt-sn/messages/snunsubscribe.h"
#include "iot-protocols/mqtt-sn/messages/snwillmsg.h"
#include "iot-protocols/mqtt-sn/messages/snwillmsgreq.h"
#include "iot-protocols/mqtt-sn/messages/snwillmsgresp.h"
#include "iot-protocols/mqtt-sn/messages/snwillmsgupd.h"
#include "iot-protocols/mqtt-sn/messages/snwilltopic.h"
#include "iot-protocols/mqtt-sn/messages/snwilltopicreq.h"
#include "iot-protocols/mqtt-sn/messages/snwilltopicresp.h"
#include "iot-protocols/mqtt-sn/messages/snwilltopicupd.h"

#include "iot-protocols/mqtt-sn/classes/mqttsnenums.h"

class SNParser
{
private:

    int decodeContentLength(unsigned char *data);

public:
    Message *decode(unsigned char * data);
    unsigned char * encode(Message *message);

};

#endif // SNPARSER_H
