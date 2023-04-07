//
// Created by 720 on 2023/3/25.
//

#include "../include/requestCosemApdu.h"
#include <stdio.h>
#include <stdlib.h>

static void free_get_request_normal(COSEM_APDU_GET_REQUEST_NORMAL **ppGetRequestNormal)
{
    if (*ppGetRequestNormal == NULL)
    {
        return;
    }

    free((*ppGetRequestNormal)->pCosemAttributeDescriptor);
    (*ppGetRequestNormal)->pCosemAttributeDescriptor = NULL;

    /*!
     * @todo free Selective Access Descriptor
     */

    free(*ppGetRequestNormal);
    *ppGetRequestNormal = NULL;
}

void free_get_request(COSEM_APDU_GET_REQUEST **ppGetRequest)
{
    if (*ppGetRequest == NULL)
    {
        return;
    }

    switch ((*ppGetRequest)->dlmsGetCommandType)
    {
        case 1:
            free_get_request_normal(&(*ppGetRequest)->pGetRequestNormal);
            break;
        default:
            break;
    }

    free(*ppGetRequest);
    *ppGetRequest = NULL;
}

COSEM_APDU_GET_REQUEST_NORMAL *convert_data_to_get_request_normal(gxByteBuffer *pByteBuffer, int32_t *pErrorCode)
{
    COSEM_APDU_GET_REQUEST_NORMAL *pCosemApduGetRequestNormal =
            (COSEM_APDU_GET_REQUEST_NORMAL *) calloc(1, sizeof(COSEM_APDU_GET_REQUEST_NORMAL));

    // Invoke id and priority
    bb_getUInt8(pByteBuffer, &pCosemApduGetRequestNormal->invokeIdAndPriority);

    // Cosem attribute descriptor
    pCosemApduGetRequestNormal->pCosemAttributeDescriptor =
            (COSEM_ATTRIBUTE_DESCRIPTOR *) calloc(1, sizeof(COSEM_ATTRIBUTE_DESCRIPTOR));
    uint16_t classID = 0;
    bb_getUInt16(pByteBuffer, &classID);
    pCosemApduGetRequestNormal->pCosemAttributeDescriptor->classID = classID;
    unsigned char ch = 0;
    for (int i = 0; i < 6; ++i)
    {
        bb_getUInt8(pByteBuffer, &ch);
        pCosemApduGetRequestNormal->pCosemAttributeDescriptor->instanceID[i] = ch;
    }
    bb_getInt8(pByteBuffer, &pCosemApduGetRequestNormal->pCosemAttributeDescriptor->attributeID);

    // Selective access descriptor
    bb_getUInt8(pByteBuffer, &pCosemApduGetRequestNormal->isUseAccessSelector);

    return pCosemApduGetRequestNormal;
}

COSEM_APDU_GET_REQUEST_NEXT *convert_data_to_get_request_next(gxByteBuffer *pByteBuffer, int32_t *pErrorCode)
{
    COSEM_APDU_GET_REQUEST_NEXT *pCosemApduGetRequestNext =
            (COSEM_APDU_GET_REQUEST_NEXT *) calloc(1, sizeof(COSEM_APDU_GET_REQUEST_NEXT));

    return pCosemApduGetRequestNext;
}

COSEM_APDU_GET_REQUEST_WITH_LIST *convert_data_to_get_request_with_list(gxByteBuffer *pByteBuffer, int32_t *pErrorCode)
{
    COSEM_APDU_GET_REQUEST_WITH_LIST *pCosemApduGetRequestWithList =
            (COSEM_APDU_GET_REQUEST_WITH_LIST *) calloc(1, sizeof(COSEM_APDU_GET_REQUEST_WITH_LIST));

    return pCosemApduGetRequestWithList;
}

COSEM_APDU_GET_REQUEST *convert_data_to_get_request(gxByteBuffer *pByteBuffer, int32_t *pErrorCode)
{
    if (pByteBuffer == NULL || pByteBuffer->size == 0)
    {
        if (pErrorCode != NULL)
        {
            *pErrorCode = DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
        return NULL;
    }

    COSEM_APDU_GET_REQUEST *pGetRequest = (COSEM_APDU_GET_REQUEST *) calloc(1, sizeof(COSEM_APDU_GET_REQUEST));
    // Get request type
    unsigned char getRequestType = 0;
    bb_getUInt8(pByteBuffer, &getRequestType);
    if (getRequestType == 1)
    {
        pGetRequest->dlmsGetCommandType = (DLMS_GET_COMMAND_TYPE) getRequestType;
        pGetRequest->pGetRequestNormal = convert_data_to_get_request_normal(pByteBuffer, pErrorCode);
    }
    else if (getRequestType == 2)
    {
        pGetRequest->dlmsGetCommandType = (DLMS_GET_COMMAND_TYPE) getRequestType;
        pGetRequest->pGetRequestNext = convert_data_to_get_request_next(pByteBuffer, pErrorCode);
    }
    else if (getRequestType == 3)
    {
        pGetRequest->dlmsGetCommandType = (DLMS_GET_COMMAND_TYPE) getRequestType;
    }
    else
    {
        if (pErrorCode != NULL)
        {
            *pErrorCode = DLMS_ERROR_CODE_FALSE;
        }
        free_get_request(&pGetRequest);
        return NULL;
    }

    if (pErrorCode != NULL)
    {
        *pErrorCode = DLMS_ERROR_CODE_OK;
    }
    return pGetRequest;
}

unsigned char *convert_get_request_normal_to_data(COSEM_APDU_GET_REQUEST_NORMAL *pCosemApduGetRequestNormal,
                                                  int32_t *pLengthData, int32_t *pErrorCode)
{
    if (pCosemApduGetRequestNormal == NULL || pLengthData == NULL)
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
    bb_setUInt8(&byteBuffer, pCosemApduGetRequestNormal->invokeIdAndPriority);

    // Add cosem attribute descriptor
    bb_setUInt16(&byteBuffer, pCosemApduGetRequestNormal->pCosemAttributeDescriptor->classID);
    for (int i = 0; i < 6; ++i)
    {
        bb_setUInt8(&byteBuffer, pCosemApduGetRequestNormal->pCosemAttributeDescriptor->instanceID[i]);
    }
    bb_setInt8(&byteBuffer, pCosemApduGetRequestNormal->pCosemAttributeDescriptor->attributeID);

    // Add selective access descriptor
    bb_setUInt8(&byteBuffer, pCosemApduGetRequestNormal->isUseAccessSelector);

    // convert to pointer of unsigned char
    *pLengthData = (int32_t) byteBuffer.size;
    unsigned char *pData = (unsigned char *) calloc(*pLengthData, sizeof(unsigned char));
    bb_get(&byteBuffer, pData, byteBuffer.size);

    bb_clear(&byteBuffer);
    return pData;
}

unsigned char *convert_get_request_to_data(COSEM_APDU_GET_REQUEST *pCosemApduGetRequest,
                                           int32_t *pLengthData, int32_t *pErrorCode)
{
    if (pCosemApduGetRequest == NULL || pLengthData == NULL)
    {
        if (pErrorCode != NULL)
        {
            *pErrorCode = DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
        return NULL;
    }

    gxByteBuffer byteBuffer;
    bb_init(&byteBuffer);

    // Add get request type
    bb_setUInt8(&byteBuffer, pCosemApduGetRequest->dlmsGetCommandType);

    // Add pPdu
    int32_t lengthPdu = 0;
    unsigned char *pPdu = convert_get_request_normal_to_data(pCosemApduGetRequest->pGetRequestNormal, &lengthPdu,
                                                             pErrorCode);
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

void mutate_get_request(COSEM_APDU_GET_REQUEST *pCosemApduGetRequest,
                        MUTATE_POSITION mutatePosition, int32_t *pErrorCode)
{
    if (pCosemApduGetRequest == NULL)
    {
        if (pErrorCode != NULL)
        {
            *pErrorCode = DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
    }

    srandom((unsigned int) time(NULL));
    if (mutatePosition == MUTATE_POSITION_GET_INVOKE_ID_AND_PRIORITY)
    {
        unsigned char newInvokeIDAndPriority = random() % (0xFF + 1);
        pCosemApduGetRequest->pGetRequestNormal->invokeIdAndPriority = newInvokeIDAndPriority;
    }
    else if (mutatePosition == MUTATE_POSITION_GET_ATTRIBUTE_CLASS_ID)
    {
        uint16_t newClassID = random() % (0xFFFF + 1);
        pCosemApduGetRequest->pGetRequestNormal->pCosemAttributeDescriptor->classID = newClassID;
    }
    else if (mutatePosition == MUTATE_POSITION_GET_ATTRIBUTE_INSTANCE_ID)
    {
        for (int i = 0; i < 6; ++i)
        {
            unsigned char ch = random() % (0xFF + 1);
            pCosemApduGetRequest->pGetRequestNormal->pCosemAttributeDescriptor->instanceID[i] = ch;
        }
    }
    else if (mutatePosition == MUTATE_POSITION_GET_ATTRIBUTE_ATTRIBUTE_ID)
    {
        char newAttributeID = (char) (random() % (0xFF + 1));
        pCosemApduGetRequest->pGetRequestNormal->pCosemAttributeDescriptor->attributeID = newAttributeID;
    }
    else
    {
        if (pErrorCode != NULL)
        {
            *pErrorCode = DLMS_ERROR_CODE_FALSE;
        }
    }
}

COSEM_APDU_SET_REQUEST *handle_set_request(gxByteBuffer *pByteBuffer, int32_t *pErrorCode)
{
    if (pByteBuffer == NULL || pByteBuffer->size == 0)
    {
        if (pErrorCode != NULL)
        {
            *pErrorCode = DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
        return NULL;
    }

    COSEM_APDU_SET_REQUEST *pSETRequest = (COSEM_APDU_SET_REQUEST *) calloc(1, sizeof(COSEM_APDU_SET_REQUEST));

    // SET request type
    unsigned char setRequestType = 0;
    if (setRequestType == 1)
    {
        pSETRequest->setRequestType = (DLMS_SET_COMMAND_TYPE) setRequestType;
    }
    else if (setRequestType == 2)
    {
        pSETRequest->setRequestType = (DLMS_SET_COMMAND_TYPE) setRequestType;
    }
    else if (setRequestType == 3)
    {
        pSETRequest->setRequestType = (DLMS_SET_COMMAND_TYPE) setRequestType;
    }
    else
    {
        if (pErrorCode != NULL)
        {
            *pErrorCode = DLMS_ERROR_CODE_FALSE;
        }
        return NULL;
    }

    if (pErrorCode != NULL)
    {
        *pErrorCode = DLMS_ERROR_CODE_OK;
    }
    return pSETRequest;
}