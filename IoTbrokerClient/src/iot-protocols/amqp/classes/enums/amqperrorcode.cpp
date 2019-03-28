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

#include "amqperrorcode.h"

AMQPErrorCode::AMQPErrorCode()
{
    this->map = std::map<int, String>();
    this->map.insert(std::pair<int, String>(AMQP_INTERNAL_ERROR_CODE, AMQP_INTERNAL_ERROR_CODE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_NOT_FOUND_ERROR_CODE, AMQP_NOT_FOUND_ERROR_CODE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_UNAUTHORIZED_ACCESS_ERROR_CODE, AMQP_UNAUTHORIZED_ACCESS_ERROR_CODE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_DECODE_ERROR_CODE, AMQP_DECODE_ERROR_CODE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_RESOURCE_LIMIT_EXCEEDED_ERROR_CODE, AMQP_RESOURCE_LIMIT_EXCEEDED_ERROR_CODE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_NOT_ALLOWED_ERROR_CODE, AMQP_NOT_ALLOWED_ERROR_CODE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_INVALID_FIELD_ERROR_CODE, AMQP_INVALID_FIELD_ERROR_CODE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_NOT_IMPLEMENTED_ERROR_CODE, AMQP_NOT_IMPLEMENTED_ERROR_CODE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_RESOURCE_LOCKED_ERROR_CODE, AMQP_RESOURCE_LOCKED_ERROR_CODE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_PRECONDITION_FAILED_ERROR_CODE, AMQP_PRECONDITION_FAILED_ERROR_CODE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_RESOURCE_DELETED_ERROR_CODE, AMQP_RESOURCE_DELETED_ERROR_CODE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_ILLEGAL_STATE_ERROR_CODE, AMQP_ILLEGAL_STATE_ERROR_CODE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_FRAME_SIZE_TOO_SMALL_ERROR_CODE, AMQP_FRAME_SIZE_TOO_SMALL_ERROR_CODE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_CONNECTION_FORCED_ERROR_CODE, AMQP_CONNECTION_FORCED_ERROR_CODE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_FRAMING_ERROR_CODE, AMQP_FRAMING_ERROR_CODE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_REDIRECTED_ERROR_CODE, AMQP_REDIRECTED_ERROR_CODE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_WINDOW_VIOLATION_ERROR_CODE, AMQP_WINDOW_VIOLATION_ERROR_CODE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_ERRANT_LINK_ERROR_CODE, AMQP_ERRANT_LINK_ERROR_CODE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_HANDLE_IN_USE_ERROR_CODE, AMQP_HANDLE_IN_USE_ERROR_CODE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_UNATTACHED_HANDLE_ERROR_CODE, AMQP_UNATTACHED_HANDLE_ERROR_CODE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_DETACH_FORCED_ERROR_CODE, AMQP_DETACH_FORCED_ERROR_CODE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_TRANSFER_LIMIT_EXCEEDED_ERROR_CODE, AMQP_TRANSFER_LIMIT_EXCEEDED_ERROR_CODE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_MESSAGE_SIZE_EXCEEDED_ERROR_CODE, AMQP_MESSAGE_SIZE_EXCEEDED_ERROR_CODE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_REDIRECT_ERROR_CODE, AMQP_REDIRECT_ERROR_CODE_STRING));
    this->map.insert(std::pair<int, String>(AMQP_STOLEN_ERROR_CODE, AMQP_STOLEN_ERROR_CODE_STRING));
}

AMQPErrorCode::AMQPErrorCode(int value) : AMQPErrorCode()
{
    this->value = value;
}

int AMQPErrorCode::getValue()
{
    return this->value;
}

String AMQPErrorCode::getName()
{
    return EnumObject::getName(this->value);
}
