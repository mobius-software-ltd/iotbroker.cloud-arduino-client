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

#ifndef IOTPROTOCOLI_H
#define IOTPROTOCOLI_H

//#include "internet-protocols/internetprotocol.h"

class IotProtocolI
{
    /*virtual void connectionDidStart(InternetProtocol *protocol) = 0;
    virtual void connectionDidStop(InternetProtocol *protocol) = 0;
    virtual void didReceiveMessage(InternetProtocol *protocol, unsigned char bytes[]) = 0;
    virtual void didFailWithError(InternetProtocol *protocol, string error) = 0;
    */

    void ready(IotProtocol *protocol);
    void connackReceived(IotProtocol *protocol, int returnCode);
    void publishReceived(IotProtocol *protocol, String topic, int qos, unsigned char bytes[], bool dup, bool retainFlag);
    void pubackReceived(IotProtocol *protocol, String topic, int qos, unsigned char bytes[], bool dup, bool retainFlag, int returnCode);
    void subackReceived(IotProtocol*protocol, String topic, int qos, int returnCode);
    void unsubackReceived(IotProtocol*protocol, String topic);
    void pingrespReceived(IotProtocol*protocol);
    void disconnectReceived(IotProtocol*protocol);
    void timeout(IotProtocol*protocol);
    void errorReceived(IotProtocol*protocol, String error);
};

#endif // IOTPROTOCOLI_H
