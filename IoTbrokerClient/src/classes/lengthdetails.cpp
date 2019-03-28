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

#include "lengthdetails.h"

LengthDetails::LengthDetails()
{

}

LengthDetails::LengthDetails(int length, int size)
{
    this->length = length;
    this->size = size;
}

int LengthDetails::getLength()
{
    return this->length;
}

int LengthDetails::getSize()
{
    return this->size;
}

LengthDetails *LengthDetails::decode(unsigned char * byteArray)
{
    int length = 0;
    int multiplier = 1;
    int byteUsed = 0;
    char encodedByte = 0;
    int i = 0;

    do {
        if (!(multiplier > 128 * 128 * 128)) {
            encodedByte = byteArray[i++];
            length += (encodedByte & 0x7f) * multiplier;
            multiplier *= 128;
            byteUsed++;
        }
    } while ((encodedByte & 128) != 0);

    return new LengthDetails(length, byteUsed);
}
