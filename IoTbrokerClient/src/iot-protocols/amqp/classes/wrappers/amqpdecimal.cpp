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

#include "amqpdecimal.h"

AMQPDecimal::AMQPDecimal()
{
    unsigned char * bytes;
    this->value = bytes;
}

AMQPDecimal::AMQPDecimal(unsigned char * value) : AMQPDecimal()
{
    this->value = value;
}

AMQPDecimal::AMQPDecimal(char value) : AMQPDecimal()
{
    this->value = malloc(sizeof(char));
    this->value[0] = value;
}

AMQPDecimal::AMQPDecimal(short value) : AMQPDecimal()
{
    this->value = malloc(sizeof(short));
    add_short(&this->value[0], value);
}

AMQPDecimal::AMQPDecimal(int value) : AMQPDecimal()
{
    this->value = malloc(sizeof(int));
    add_int(&this->value[0], value);
}

AMQPDecimal::AMQPDecimal(long value) : AMQPDecimal()
{
    this->value = malloc(sizeof(long));
    add_long(&this->value[0], value);
}

AMQPDecimal::AMQPDecimal(float value) : AMQPDecimal()
{
    this->value = malloc(sizeof(float));
    add_float(&this->value[0], value);
}

AMQPDecimal::AMQPDecimal(double value) : AMQPDecimal()
{
    this->value = malloc(sizeof(double));
    add_double(&this->value[0], value);
}

char AMQPDecimal::getByte()
{
    return this->value[0];
}

short AMQPDecimal::getShortNumber()
{
    return get_short(this->value, 0);
}

int AMQPDecimal::getIntNumber()
{
    return get_int(this->value, 0);
}

long AMQPDecimal::getLongNumber()
{
    return get_long(this->value, 0);
}

float AMQPDecimal::getFloatNumber()
{
    return get_float(this->value, 0);
}

double AMQPDecimal::getDoubleNumber()
{
    return get_double(this->value, 0);
}

unsigned char * AMQPDecimal::getValue() const
{
    return value;
}
