//
// Created by 720 on 2023/3/25.
//

#include <stdlib.h>
#include "../include/parser.h"

static void free_cosem_apdu(COSEM_APDU **ppCosemApdu, DLMS_COMMAND apduType)
{
    if (*ppCosemApdu == NULL)
    {
        return;
    }

    switch (apduType)
    {
        case DLMS_COMMAND_GET_REQUEST:
            free_get_request(&(*ppCosemApdu)->pGetRequest);
            break;
        default:
            break;
    }

    free(*ppCosemApdu);
    *ppCosemApdu = NULL;
}

void free_xDLMS_APDU(xDLMS_APDU **ppXDlmsApdu)
{
    if (*ppXDlmsApdu == NULL)
    {
        return;
    }

    free_cosem_apdu(&(*ppXDlmsApdu)->pCosemApdu, (*ppXDlmsApdu)->apduType);

    free(*ppXDlmsApdu);
    *ppXDlmsApdu = NULL;
}

xDLMS_APDU *convert_data_to_xDLMS_APDU(unsigned char *data, int32_t lengthData, int32_t *pErrorCode)
{
    if (data == NULL || lengthData == 0)
    {
        if (pErrorCode != NULL)
        {
            *pErrorCode = DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
        return NULL;
    }

    // Convert data to gxByteBuffer
    gxByteBuffer byteBuffer;
    bb_init(&byteBuffer);
    bb_attach(&byteBuffer, data, lengthData, 2 * lengthData);

//    // Version
//    uint16_t version = 0;
//    int ret = bb_getUInt16(&byteBuffer, &version);
//
//    // Source address
//    uint16_t sourceAddress = 0;
//    ret = bb_getUInt16(&byteBuffer, &sourceAddress);
//
//    // Target address
//    uint16_t targetAddress = 0;
//    ret = bb_getUInt16(&byteBuffer, &targetAddress);

    xDLMS_APDU *xDlmsApdu = (xDLMS_APDU *) calloc(1, sizeof(xDLMS_APDU));
    // APDU length
    int ret = bb_getUInt16(&byteBuffer, &xDlmsApdu->apduLength);
    if (ret != 0 || xDlmsApdu->apduLength + 2 != lengthData)
    {
        if (pErrorCode != NULL)
        {
            *pErrorCode = DLMS_ERROR_CODE_FALSE;
        }
        free_xDLMS_APDU(&xDlmsApdu);
        return NULL;
    }

    // Command type
    unsigned char commandType = 0;
    ret = bb_getUInt8(&byteBuffer, &commandType);
    if (ret != 0 || commandType < 192 || commandType > 200)
    {
        if (pErrorCode != NULL)
        {
            *pErrorCode = DLMS_ERROR_CODE_FALSE;
        }
        free_xDLMS_APDU(&xDlmsApdu);
        return NULL;
    }
    xDlmsApdu->apduType = (DLMS_COMMAND) commandType;

    // APDU
    COSEM_APDU_GET_REQUEST *cosemApduGetRequest = convert_data_to_get_request(&byteBuffer, NULL);
    xDlmsApdu->pCosemApdu = (COSEM_APDU *) calloc(1, sizeof(COSEM_APDU));
    xDlmsApdu->pCosemApdu->pGetRequest = cosemApduGetRequest;

    return xDlmsApdu;
}


unsigned char *convert_xDLMS_APDU_to_data(xDLMS_APDU *xDlmsApdu, int32_t *pLengthData, int32_t *pErrorCode)
{
    if (xDlmsApdu == NULL || pLengthData == NULL)
    {
        if (pErrorCode != NULL)
        {
            *pErrorCode = DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
        return NULL;
    }

    gxByteBuffer byteBuffer;
    bb_init(&byteBuffer);
    // Add length
    bb_setUInt16(&byteBuffer, xDlmsApdu->apduLength);

    // Add command type
    bb_setUInt8(&byteBuffer, xDlmsApdu->apduType);

    // Add cosem apdu
    int32_t lengthPdu = 0;
    unsigned char *pdu = NULL;
    switch (xDlmsApdu->apduType)
    {
        case 192:
            pdu = convert_get_request_to_data(xDlmsApdu->pCosemApdu->pGetRequest, &lengthPdu, pErrorCode);
            break;
        default:
            break;
    }
    bb_set(&byteBuffer, pdu, lengthPdu);
    free(pdu);
    pdu = NULL;

    *pLengthData = xDlmsApdu->apduLength + 2;
    unsigned char *data = (unsigned char *) calloc(*pLengthData, sizeof(unsigned char));
    bb_get(&byteBuffer, data, byteBuffer.size);

    bb_clear(&byteBuffer);

    return data;
}