//
// Created by 720 on 2023/3/25.
//

#ifndef DLMSAPDUPARSER_PARSER_H
#define DLMSAPDUPARSER_PARSER_H

#include "getRequest.h"

typedef union
{
    COSEM_APDU_GET_REQUEST *pGetRequest;
} COSEM_APDU;

typedef struct
{
    uint16_t APDULength;
    DLMS_COMMAND APDUType;
    COSEM_APDU *pCosemAPDU;
} xDLMS_APDU;

xDLMS_APDU *convert_data_to_DLMS_APDU(unsigned char *data, int32_t lengthData, int32_t *pErrorCode);

#endif //DLMSAPDUPARSER_PARSER_H
