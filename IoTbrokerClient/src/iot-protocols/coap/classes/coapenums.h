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

#ifndef COAPENUMS_H
#define COAPENUMS_H

enum CoAPCode
{
    COAP_GET_METHOD                                 = 1,
    COAP_POST_METHOD                                = 2,
    COAP_PUT_METHOD                                 = 3,
    COAP_DELETE_METHOD                              = 4,
    COAP_CREATED_RESPONSE_CODE                      = 65,
    COAP_DELETED_RESPONSE_CODE                      = 66,
    COAP_VALID_RESPONSE_CODE                        = 67,
    COAP_CHANGED_RESPONSE_CODE                      = 68,
    COAP_CONTENT_RESPONSE_CODE                      = 69,
    COAP_BAD_REQUEST_RESPONSE_CODE                  = 128,
    COAP_UNAUTHORIZED_RESPONSE_CODE                 = 129,
    COAP_BADOPTION_RESPONSE_CODE                    = 130,
    COAP_FORBIDDEN_RESPONSE_CODE                    = 131,
    COAP_NOT_FOUND_RESPONSE_CODE                    = 132,
    COAP_METHOD_NOT_ALLOWED_RESPONSE_CODE           = 133,
    COAP_NOT_ACCEPTABLE_RESPONSE_CODE               = 134,
    COAP_PRECONDITION_FAILED_RESPONSE_CODE          = 140,
    COAP_REQUEST_ENTITY_TOOLARGERESPONSE_CODE       = 141,
    COAP_UNSUPPORTED_CONTENT_FORMAT_RESPONSE_CODE   = 143,
    COAP_INTERNAL_SERVER_ERROR_RESPONSE_CODE        = 160,
    COAP_NOT_IMPLEMENTED_RESPONSE_CODE              = 161,
    COAP_BAD_GATEWAY_RESPONSE_CODE                  = 162,
    COAP_SERVICE_UNAVAILABLE_RESPONSE_CODE          = 163,
    COAP_GATEWAY_TIMEOUT_RESPONSE_CODE              = 164,
    COAP_PROXYING_NOT_SUPPORTED_RESPONSE_CODE       = 165
};

enum CoAPTypes
{
    COAP_CONFIRMABLE_TYPE       = 0,
    COAP_NONCONFIRMABLE_TYPE    = 1,
    COAP_ACKNOWLEDGMENT_TYPE    = 2,
    COAP_RESET_TYPE             = 3,
};

enum CoAPOptionDefinitions
{
    COAP_IF_MATCH_OPTION        = 1,
    COAP_URI_HOST_OPTION        = 3,
    COAP_ETAG_OPTION            = 4,
    COAP_IF_NONE_MATCH_OPTION   = 5,
    COAP_OBSERVE_OPTION         = 6,
    COAP_URI_PORT_OPTION        = 7,
    COAP_LOCATION_PATH_OPTION   = 8,
    COAP_URI_PATH_OPTION        = 11,
    COAP_CONTENT_FORMAT_OPTION  = 12,
    COAP_MAX_AGE_OPTION         = 14,
    COAP_URI_QUERY_OPTION       = 15,
    COAP_ACCEPT_OPTION          = 17,
    COAP_LOCATION_QUERY_OPTION  = 20,
    COAP_BLOCK2_OPTION          = 23,
    COAP_BLOCK1_OPTION          = 27,
    COAP_SIZE2_OPTION           = 28,
    COAP_PROXY_URI_OPTION       = 35,
    COAP_PROXY_SCHEME_OPTION    = 39,
    COAP_SIZE1_OPTION           = 60,
    COAP_NODE_ID_OPTION         = 2050,
};

enum CoAPContentFormats
{
    COAP_PLAIN_CONTENT_FORMAT           = 0,
    COAP_LINK_CONTENT_FORMAT            = 40,
    COAP_XML_CONTENT_FORMAT             = 41,
    COAP_OCTET_STREAM_CONTENT_FORMAT    = 42,
    COAP_EXI_CONTENT_FORMAT             = 47,
    COAP_JSON_CONTENT_FORMAT            = 50,
};

#endif // COAPENUMS_H
