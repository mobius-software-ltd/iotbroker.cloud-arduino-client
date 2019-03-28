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

#ifndef ENUMOBJECT_H
#define ENUMOBJECT_H

#include <StandardCplusplus.h>
#include <map>
#include <WString.h>

int static const UNKNOWN_ENUM_VALUE = -99999;

class EnumObject
{

protected:

    std::map<int, String> map;

public:
    explicit EnumObject();

    std::map<int, String> getMap() const;

    String getName(int value);
    int getValue(String name);
};

#endif // ENUMOBJECT_H
