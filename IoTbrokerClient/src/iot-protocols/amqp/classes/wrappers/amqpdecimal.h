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

#ifndef AMQPDECIMAL_H
#define AMQPDECIMAL_H

#include <cstring>
#include <cstdlib>
#include "utils/helpers.h"

class AMQPDecimal
{

private:

    unsigned char * value;

public:

    AMQPDecimal();
    AMQPDecimal(unsigned char * value);
    AMQPDecimal(char value);
    AMQPDecimal(short value);
    AMQPDecimal(int value);
    AMQPDecimal(long value);
    AMQPDecimal(float value);
    AMQPDecimal(double value);

    unsigned char * getValue() const;

    char getByte();
    short getShortNumber();
    int getIntNumber();
    long getLongNumber();
    float getFloatNumber();
    double getDoubleNumber();
};
//Q_DECLARE_METATYPE(AMQPDecimal *)

#endif // AMQPDECIMAL_H
