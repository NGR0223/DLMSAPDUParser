//
// Created by 720 on 2023/3/25.
//

#ifndef DLMSAPDUPARSER_REQUESTCOSEMAPDU_H
#define DLMSAPDUPARSER_REQUESTCOSEMAPDU_H

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
    DLMS_GET_COMMAND_TYPE dlmsGetCommandType;
    union
    {
        COSEM_APDU_GET_REQUEST_NORMAL *pGetRequestNormal;
        COSEM_APDU_GET_REQUEST_NEXT *pGetRequestNext;
        COSEM_APDU_GET_REQUEST_WITH_LIST *pGetRequestWithList;
    };
} COSEM_APDU_GET_REQUEST;

void free_get_request(COSEM_APDU_GET_REQUEST **ppCosemApduGetRequest);

COSEM_APDU_GET_REQUEST *convert_data_to_get_request(gxByteBuffer *pByteBuffer, int32_t *pErrorCode);

unsigned char *convert_get_request_to_data(COSEM_APDU_GET_REQUEST *pCosemApduGetRequest,
                                           int32_t *pLengthData, int32_t *pErrorCode);

void mutate_get_request(COSEM_APDU_GET_REQUEST *pCosemApduGetRequest,
                        MUTATE_POSITION mutatePosition, int32_t *pErrorCode);

typedef struct
{
    InvokeIdAndPriority invokeIdAndPriority;
    COSEM_ATTRIBUTE_DESCRIPTOR *pCosemAttributeDescriptor;
    SELECTIVE_ACCESS_DESCRIPTOR *pSelectiveAccessDescriptor;
} COSEM_APDU_SET_REQUEST_NORMAL;

typedef struct
{
    InvokeIdAndPriority invokeIdAndPriority;
    COSEM_ATTRIBUTE_DESCRIPTOR *pCosemAttributeDescriptor;
    SELECTIVE_ACCESS_DESCRIPTOR *pSelectiveAccessDescriptor;
} COSEM_APDU_SET_REQUEST_NEXT;

typedef struct
{
    InvokeIdAndPriority invokeIdAndPriority;
    COSEM_ATTRIBUTE_DESCRIPTOR *pCosemAttributeDescriptor;
    SELECTIVE_ACCESS_DESCRIPTOR *pSelectiveAccessDescriptor;
} COSEM_APDU_SET_REQUEST_WITH_LIST;

typedef struct
{
    DLMS_SET_COMMAND_TYPE setRequestType;

    // Only one of following pointer will be allocated
    COSEM_APDU_SET_REQUEST_NORMAL *pGetRequestNormal;
    COSEM_APDU_SET_REQUEST_NEXT *pGetRequestNext;
    COSEM_APDU_SET_REQUEST_WITH_LIST *pGetRequestWithList;
} COSEM_APDU_SET_REQUEST;


#endif //DLMSAPDUPARSER_REQUESTCOSEMAPDU_H
