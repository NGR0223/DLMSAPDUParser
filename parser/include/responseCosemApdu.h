//
// Created by 720 on 2023/4/6.
//

#ifndef DLMSAPDUPARSER_RESPONSECOSEMAPDU_H
#define DLMSAPDUPARSER_RESPONSECOSEMAPDU_H

#include "base.h"

typedef struct
{
    InvokeIdAndPriority invokeIdAndPriority;
    uint8_t resultType;
    GET_DATA_RESULT *pResult;
} COSEM_APDU_GET_RESPONSE_NORMAL;

typedef struct
{
    InvokeIdAndPriority invokeIdAndPriority;
    DATABLOCK_G *pDatablockG;
} COSEM_APDU_GET_RESPONSE_WITH_DATABLOCK;

typedef struct
{
    DLMS_GET_COMMAND_TYPE dlmsGetCommandType;
    union
    {
        COSEM_APDU_GET_RESPONSE_NORMAL *pCosemApduGetResponseNormal;
        COSEM_APDU_GET_RESPONSE_WITH_DATABLOCK pCosemApduGetResponseWithDatablock;
    };
} COSEM_APDU_GET_RESPONSE;

void free_get_response(COSEM_APDU_GET_RESPONSE **ppCosemApduGetResponse);

COSEM_APDU_GET_RESPONSE *convert_data_to_get_response(gxByteBuffer *pByteBuffer, int32_t *pErrorCode);

unsigned char *convert_get_response_to_data(COSEM_APDU_GET_RESPONSE *pCosemApduGetResponse,
                                            int32_t *pLengthData, int32_t *pErrorCode);

#endif //DLMSAPDUPARSER_RESPONSECOSEMAPDU_H
