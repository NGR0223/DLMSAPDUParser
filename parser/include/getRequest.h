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
    SELECTIVE_ACCESS_DESCRIPTOR *pSelectiveAccessDescriptor;
} COSEM_APDU_GET_REQUEST_NORMAL;

typedef struct
{
    InvokeIdAndPriority invokeIdAndPriority;
    COSEM_ATTRIBUTE_DESCRIPTOR *pCosemAttributeDescriptor;
    SELECTIVE_ACCESS_DESCRIPTOR *pSelectiveAccessDescriptor;
} COSEM_APDU_GET_REQUEST_NEXT;

typedef struct
{
    InvokeIdAndPriority invokeIdAndPriority;
    COSEM_ATTRIBUTE_DESCRIPTOR *pCosemAttributeDescriptor;
    SELECTIVE_ACCESS_DESCRIPTOR *pSelectiveAccessDescriptor;
} COSEM_APDU_GET_REQUEST_WITH_LIST;

typedef union
{
    DLMS_GET_COMMAND_TYPE getRequestType;
    COSEM_APDU_GET_REQUEST_NORMAL *pGetRequestNormal;
    COSEM_APDU_GET_REQUEST_NEXT *pGetRequestNext;
    COSEM_APDU_GET_REQUEST_WITH_LIST *pGetRequestWithList;
} COSEM_APDU_GET_REQUEST;

COSEM_APDU_GET_REQUEST *handle_get_request(gxByteBuffer *pByteBuffer, int32_t *pErrorCode);

#endif //DLMSAPDUPARSER_GETREQUEST_H
