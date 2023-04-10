//
// Created by 720 on 2023/3/25.
//

#ifndef DLMSAPDUPARSER_PARSER_H
#define DLMSAPDUPARSER_PARSER_H

#include "requestCosemApdu.h"
#include "responseCosemApdu.h"

typedef union
{
    COSEM_APDU_GET_REQUEST *pGetRequest;
    COSEM_APDU_SET_REQUEST *pSetRequest;
    COSEM_APDU_GET_RESPONSE *pGetResponse;
    COSEM_APDU_EXCEPTION_RESPONSE *pExceptionResponse;
} COSEM_APDU;

typedef struct
{
    uint16_t apduLength;
    DLMS_COMMAND apduType;
    COSEM_APDU *pCosemApdu;
} xDLMS_APDU;

typedef struct
{
    uint32_t stateCount;
    uint32_t states[];
} STATES;

/*!
 * Free memory
 * @param ppXDlmsApdu a second rank pointer of xDLMS_APDU
 */
void free_xDLMS_APDU(xDLMS_APDU **ppXDlmsApdu);

/*!
 * Convert hex data to an xDLMS_APDU in A-XDR
 * @param data: a DLMS packet in TCP_WRAPPER without version and address
 * @param lengthData: length of data
 * @param pErrorCode: a pointer of error code while something wrong
 * @return a pointer of xDLMS_APDU
 */
xDLMS_APDU *convert_data_to_xDLMS_APDU(unsigned char *data, int32_t lengthData, int32_t *pErrorCode);

/*!
 * Convert an xDLMS_APDU to hex data
 * @param pXDlmsApdu: a pointer of xDLMS_APDU
 * @param pLengthData: length of hex data
 * @param pErrorCode: a pointer of error code while something wrong
 * @return a pointer of hex data
 */
unsigned char *convert_xDLMS_APDU_to_data(xDLMS_APDU *pXDlmsApdu, int32_t *pLengthData, int32_t *pErrorCode);

/*!
 * Mutate an xDLMS_APDU according its type and position of value
 * @param pXDlmsApdu: a pointer of xDLMS_APDU
 * @param mutatePosition: position of value that want to mutate
 * @param pErrorCode: a pointer of error code while something wrong
 */
void mutate_xDLMS_APDU(xDLMS_APDU *pXDlmsApdu, MUTATE_POSITION mutatePosition, int32_t *pErrorCode);

#endif //DLMSAPDUPARSER_PARSER_H
