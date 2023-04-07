//
// Created by 720 on 2023/4/6.
//

#include <stdlib.h>
#include "../include/responseCosemApdu.h"
#include "../../development/include/datainfo.h"
#include "../../development/include/dlms.h"
#include "../../development/include/gxmem.h"

void free_get_response_normal(COSEM_APDU_GET_RESPONSE_NORMAL **ppCosemApduGetResponseNormal)
{
    if (*ppCosemApduGetResponseNormal != NULL)
    {
        if ((*ppCosemApduGetResponseNormal)->pResult != NULL)
        {
            var_clear(&(*ppCosemApduGetResponseNormal)->pResult->data);
            free((*ppCosemApduGetResponseNormal)->pResult);
            (*ppCosemApduGetResponseNormal)->pResult = NULL;
        }
        free(*ppCosemApduGetResponseNormal);
        *ppCosemApduGetResponseNormal = NULL;
    }
}

void free_get_response(COSEM_APDU_GET_RESPONSE **ppCosemApduGetResponse)
{
    if (*ppCosemApduGetResponse != NULL)
    {
        switch ((*ppCosemApduGetResponse)->dlmsGetCommandType)
        {
            case DLMS_GET_COMMAND_TYPE_NORMAL:
                free_get_response_normal(&(*ppCosemApduGetResponse)->pCosemApduGetResponseNormal);
                break;
            default:
                break;
        }
        free(*ppCosemApduGetResponse);
        *ppCosemApduGetResponse = NULL;
    }
}

COSEM_APDU_GET_RESPONSE_NORMAL *convert_data_to_get_response_normal(gxByteBuffer *pByteBuffer, int32_t *pErrorCode)
{
    COSEM_APDU_GET_RESPONSE_NORMAL *pCosemApduGetResponseNormal =
            (COSEM_APDU_GET_RESPONSE_NORMAL *) calloc(1, sizeof(COSEM_APDU_GET_RESPONSE_NORMAL));

    // Invoke id and priority
    bb_getUInt8(pByteBuffer, &pCosemApduGetResponseNormal->invokeIdAndPriority);

    // result
    pCosemApduGetResponseNormal->pResult = (GET_DATA_RESULT *) calloc(1, sizeof(GET_DATA_RESULT));
    bb_getUInt8(pByteBuffer, &pCosemApduGetResponseNormal->resultType);
    if (pCosemApduGetResponseNormal->resultType == 0)    // Data
    {
        var_init(&pCosemApduGetResponseNormal->pResult->data);
        gxDataInfo gxDataInfo;
        di_init(&gxDataInfo);
        int ret = dlms_getData(pByteBuffer, &gxDataInfo, &pCosemApduGetResponseNormal->pResult->data);
        if (ret != 0)
        {
            if (pErrorCode != NULL)
            {
                *pErrorCode = (DLMS_ERROR_CODE) ret;
            }
        }
    }
    else    // IMPLICIT Data-Access-Result
    {

    }

    return pCosemApduGetResponseNormal;
}

COSEM_APDU_GET_RESPONSE *convert_data_to_get_response(gxByteBuffer *pByteBuffer, int32_t *pErrorCode)
{
    if (pByteBuffer == NULL || pByteBuffer->size == 0)
    {
        if (pErrorCode != NULL)
        {
            *pErrorCode = DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
        return NULL;
    }

    COSEM_APDU_GET_RESPONSE *pGetResponse = (COSEM_APDU_GET_RESPONSE *) calloc(1, sizeof(COSEM_APDU_GET_RESPONSE));
    // Get Response Type
    unsigned char getResponseType = 0;
    bb_getUInt8(pByteBuffer, &getResponseType);
    if (getResponseType == 1)
    {
        pGetResponse->dlmsGetCommandType = (DLMS_GET_COMMAND_TYPE) getResponseType;
        pGetResponse->pCosemApduGetResponseNormal = convert_data_to_get_response_normal(pByteBuffer, pErrorCode);
    }
    else if (getResponseType == 2)
    {

    }
    else if (getResponseType == 2)
    {

    }
    else
    {
        if (pErrorCode != NULL)
        {
            *pErrorCode = DLMS_ERROR_CODE_FALSE;
        }
        free_get_response(&pGetResponse);
        return NULL;
    }

    if (pErrorCode != NULL)
    {
        *pErrorCode = DLMS_ERROR_CODE_OK;
    }
    return pGetResponse;
}

unsigned char *convert_get_response_normal_to_data(COSEM_APDU_GET_RESPONSE_NORMAL *pCosemApduGetResponseNormal,
                                                   int32_t *pLengthData, int32_t *pErrorCode)
{
    if (pCosemApduGetResponseNormal == NULL || pLengthData == NULL)
    {
        if (pErrorCode != NULL)
        {
            *pErrorCode = DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
        return NULL;
    }

    gxByteBuffer byteBuffer;
    bb_init(&byteBuffer);

    // Add invoke id and priority
    bb_setUInt8(&byteBuffer, pCosemApduGetResponseNormal->invokeIdAndPriority);

    // Add result type and result
    bb_setUInt8(&byteBuffer, pCosemApduGetResponseNormal->resultType);
    if (pCosemApduGetResponseNormal->resultType == 0)
    {
        var_getBytes(&pCosemApduGetResponseNormal->pResult->data, &byteBuffer);
    }
    else    // IMPLICIT Data-Access-Result
    {

    }

    // convert to pointer of unsigned char
    *pLengthData = (int32_t) byteBuffer.size;
    unsigned char *pData = (unsigned char *) calloc(*pLengthData, sizeof(unsigned char));
    bb_get(&byteBuffer, pData, byteBuffer.size);

    bb_clear(&byteBuffer);
    return pData;
}

unsigned char *convert_get_response_to_data(COSEM_APDU_GET_RESPONSE *pCosemApduGetResponse,
                                            int32_t *pLengthData, int32_t *pErrorCode)
{
    if (pCosemApduGetResponse == NULL || pLengthData == NULL)
    {
        if (pErrorCode != NULL)
        {
            *pErrorCode = DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
        return NULL;
    }

    gxByteBuffer byteBuffer;
    bb_init(&byteBuffer);

    // Add get response type
    bb_setUInt8(&byteBuffer, pCosemApduGetResponse->dlmsGetCommandType);

    // Add pdu
    int32_t lengthPdu = 0;
    unsigned char *pPdu = NULL;
    if (pCosemApduGetResponse->dlmsGetCommandType == DLMS_GET_COMMAND_TYPE_NORMAL)
    {
        pPdu = convert_get_response_normal_to_data(pCosemApduGetResponse->pCosemApduGetResponseNormal,
                                                   &lengthPdu, pErrorCode);
    }
    else if (pCosemApduGetResponse->dlmsGetCommandType == DLMS_GET_COMMAND_TYPE_NEXT_DATA_BLOCK)
    {

    }
    else if (pCosemApduGetResponse->dlmsGetCommandType == DLMS_GET_COMMAND_TYPE_WITH_LIST)
    {

    }
    else
    {

    }
    if (pPdu == NULL)
    {
        if (pErrorCode != NULL)
        {
            *pErrorCode = DLMS_ERROR_CODE_FALSE;
        }
        bb_clear(&byteBuffer);
        return NULL;
    }
    bb_set(&byteBuffer, pPdu, lengthPdu);
    free(pPdu);
    pPdu = NULL;

    // convert to pointer of unsigned char
    *pLengthData = (int32_t) byteBuffer.size;
    unsigned char *pData = (unsigned char *) calloc(*pLengthData, sizeof(unsigned char));
    bb_get(&byteBuffer, pData, byteBuffer.size);

    bb_clear(&byteBuffer);
    return pData;
}