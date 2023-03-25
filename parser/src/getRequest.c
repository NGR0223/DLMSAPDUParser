//
// Created by 720 on 2023/3/25.
//

#include "../include/getRequest.h"
#include <stdio.h>
#include <stdlib.h>

static void free_get_request(COSEM_APDU_GET_REQUEST **ppGetRequest)
{

}

COSEM_APDU_GET_REQUEST *handle_get_request(gxByteBuffer *pByteBuffer, int32_t *pErrorCode)
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
    unsigned char tmpUnChar = 0;
    bb_getUInt8(pByteBuffer, &tmpUnChar);
    if (tmpUnChar > 3 || tmpUnChar == 0)
    {
        pGetRequest->getRequestType = (DLMS_GET_COMMAND_TYPE) tmpUnChar;
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
