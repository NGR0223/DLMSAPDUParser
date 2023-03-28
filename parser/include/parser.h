//
// Created by 720 on 2023/3/25.
//

#ifndef DLMSAPDUPARSER_PARSER_H
#define DLMSAPDUPARSER_PARSER_H

#include "getRequest.h"
#include "setRequest.h"

typedef union
{
    COSEM_APDU_GET_REQUEST *pGetRequest;
    COSEM_APDU_SET_REQUEST *pSetRequest;
} COSEM_APDU;

typedef struct
{
    uint16_t apduLength;
    DLMS_COMMAND apduType;
    COSEM_APDU *pCosemApdu;
} xDLMS_APDU;


void free_xDLMS_APDU(xDLMS_APDU **ppXDlmsApdu);

xDLMS_APDU *convert_data_to_xDLMS_APDU(unsigned char *data, int32_t lengthData, int32_t *pErrorCode);

unsigned char *convert_xDLMS_APDU_to_data(xDLMS_APDU *xDlmsApdu, int32_t *pLengthData, int32_t *pErrorCode);

void mutate_xDLMS_APDU(xDLMS_APDU *xDlmsApdu, MUTATE_POSITION mutatePosition, int32_t *pErrorCode);

#endif //DLMSAPDUPARSER_PARSER_H
