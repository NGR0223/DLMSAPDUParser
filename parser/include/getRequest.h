//
// Created by 720 on 2023/3/25.
//

#ifndef DLMSAPDUPARSER_GETREQUEST_H
#define DLMSAPDUPARSER_GETREQUEST_H

#include "base.h"

typedef struct
{
    InvokeIdAndPriority invokeIdAndPriority;
    COSEM_ATTRIBUTE_DESCRIPTOR *pCosemAttributeDescriptor;
    uint8_t isUseAccessSelector;
    SELECTIVE_ACCESS_DESCRIPTOR *pSelectiveAccessDescriptor;
} COSEM_APDU_GET_REQUEST_NORMAL;

typedef struct
{
    InvokeIdAndPriority invokeIdAndPriority;
    COSEM_ATTRIBUTE_DESCRIPTOR *pCosemAttributeDescriptor;
    uint8_t isUseAccessSelector;
    SELECTIVE_ACCESS_DESCRIPTOR *pSelectiveAccessDescriptor;
} COSEM_APDU_GET_REQUEST_NEXT;

typedef struct
{
    InvokeIdAndPriority invokeIdAndPriority;
    COSEM_ATTRIBUTE_DESCRIPTOR *pCosemAttributeDescriptor;
    uint8_t isUseAccessSelector;
    SELECTIVE_ACCESS_DESCRIPTOR *pSelectiveAccessDescriptor;
} COSEM_APDU_GET_REQUEST_WITH_LIST;

typedef struct
{
    DLMS_GET_COMMAND_TYPE getRequestType;
    union
    {
        COSEM_APDU_GET_REQUEST_NORMAL *pGetRequestNormal;
        COSEM_APDU_GET_REQUEST_NEXT *pGetRequestNext;
        COSEM_APDU_GET_REQUEST_WITH_LIST *pGetRequestWithList;
    };
} COSEM_APDU_GET_REQUEST;

COSEM_APDU_GET_REQUEST *convert_data_to_get_request(gxByteBuffer *pByteBuffer, int32_t *pErrorCode);

unsigned char *
convert_get_request_to_data(COSEM_APDU_GET_REQUEST *pCosemApduGetRequest, int32_t *pLengthData, int32_t *pErrorCode);

void free_get_request(COSEM_APDU_GET_REQUEST **ppGetRequest);

#endif //DLMSAPDUPARSER_GETREQUEST_H
