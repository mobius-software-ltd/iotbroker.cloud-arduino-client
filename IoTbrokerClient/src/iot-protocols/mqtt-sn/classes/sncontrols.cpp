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

#include "sncontrols.h"

SNControls::SNControls()
{

}

SNControls::SNControls(SNRadius radius)
{
    this->radius = radius;
}

SNControls *SNControls::decode(unsigned char byte)
{
    if (byte > 3 || byte < 0) {
       printf("Invalid radius value in 'SNControls'. Value = " + byte);
       return new SNControls((SNRadius)0);
    }
    return new SNControls((SNRadius)byte);
}

unsigned char SNControls::encode(SNRadius radius)
{
    unsigned char byte = 0;
    byte |= (unsigned char)radius;
    return byte;
}

SNRadius SNControls::getRadius() const
{
    return radius;
}

void SNControls::setRadius(const SNRadius &value)
{
    radius = value;
}
