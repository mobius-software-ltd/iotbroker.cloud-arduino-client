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

#include "amqpsymbol.h"

AMQPSymbol::AMQPSymbol()
{

}

AMQPSymbol::AMQPSymbol(String value)
{
    this->value = value;
}

bool AMQPSymbol::isEqual(AMQPSymbol *item)
{
    if (this == item) {
        return true;
    }
    if (item->getValue().length() == 0) {
        return false;
    }

    if (this->value.length() == 0) {
        if (item->getValue().length() != 0) {
            return false;
        }
    } else if (this->value != item->getValue()) {
        return false;
    }
    return true;
}

String AMQPSymbol::getValue() const
{
    return value;
}
