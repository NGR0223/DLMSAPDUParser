//
// Created by 720 on 2023/3/25.
//

#ifndef DLMSAPDUPARSER_BASE_H
#define DLMSAPDUPARSER_BASE_H

#include <stdint.h>
#include "../../development/include/bytebuffer.h"
#include "../../development/include/enums.h"
#include "../../development/include/errorcodes.h"
#include "../../development/include/variant.h"

#define InvokeIdAndPriority uint8_t
#define CosemClassID uint16_t
#define CosemObjectInstanceID(X) unsigned char X[6]
#define CosemObjectAttributeID int8_t
#define AccessSelector uint8_t
#define Data dlmsVARIANT

typedef struct
{
    unsigned char *pValue;
    int32_t lengthValue;
} OCTET_STRING;

typedef struct
{
    CosemClassID classID;
    CosemObjectInstanceID(instanceID);
    CosemObjectAttributeID attributeID;
} COSEM_ATTRIBUTE_DESCRIPTOR;

typedef struct
{
    AccessSelector accessSelector;
    Data accessParameters;
} SELECTIVE_ACCESS_DESCRIPTOR;

typedef enum
{
    DATA_ACCESS_RESULT_SUCCESS = 0,
    DATA_ACCESS_RESULT_HARDWARE_FAULT = 1,
    DATA_ACCESS_RESULT_TEMPORARY_FAILURE = 2,
    DATA_ACCESS_RESULT_READ_WRITE_DENIED = 3,
    DATA_ACCESS_RESULT_OBJECT_UNDEFINED = 4,
    DATA_ACCESS_RESULT_OBJECT_CLASS_INCONSISTENT = 9,
    DATA_ACCESS_RESULT_OBJECT_UNAVAILABLE = 11,
    DATA_ACCESS_RESULT_TYPE_UNMATCHED = 12,
    DATA_ACCESS_RESULT_SCOPE_OF_ACCESS_VIOLATED = 13,
    DATA_ACCESS_RESULT_DATA_BLOCK_UNAVAILABLE = 14,
    DATA_ACCESS_RESULT_LONG_GET_ABORTED = 15,
    DATA_ACCESS_RESULT_NO_LONG_GET_IN_PROGRESS = 16,
    DATA_ACCESS_RESULT_LONG_SET_ABORTED = 17,
    DATA_ACCESS_RESULT_NO_LONG_SET_IN_PROGRESS = 18,
    DATA_ACCESS_RESULT_DATA_BLOCK_NUMBER_INVALID = 19,
    DATA_ACCESS_RESULT_OTHER_REASON = 250,
} DATA_ACCESS_RESULT;

typedef union
{
    Data data;
    DATA_ACCESS_RESULT dataAccessResult;
} GET_DATA_RESULT;

typedef struct
{
    char lastBlock; // BOOLEAN
    uint32_t blockNumber;
    union
    {
        OCTET_STRING rawData;   // [0] IMPLICIT OCTET STRING
        DATA_ACCESS_RESULT dataAccessResult;    // [1] IMPLICIT Data-Access-Result
    } result;
} DATABLOCK_G;

typedef enum
{
    MUTATE_POSITION_GET_INVOKE_ID_AND_PRIORITY = 0,
    MUTATE_POSITION_GET_ATTRIBUTE_CLASS_ID = 1,
    MUTATE_POSITION_GET_ATTRIBUTE_INSTANCE_ID = 2,
    MUTATE_POSITION_GET_ATTRIBUTE_ATTRIBUTE_ID = 3,
} MUTATE_POSITION;

typedef enum
{
    STATE_ERROR_SERVICE_NOT_ALLOWED = 1,
    STATE_ERROR_SERVICE_UNKNOWN = 2,
} STATE_ERROR;

typedef struct
{
    uint8_t SERVICE_ERROR_TAG;
    union
    {
        uint8_t SERVICE_ERROR_OPERATION_NOT_POSSIBLE;
        uint8_t SERVICE_ERROR_SERVICE_NOT_SUPPORTED;
        uint8_t SERVICE_ERROR_OTHER_REASON;
        uint8_t SERVICE_ERROR_PDU_TOO_LONG;
        uint8_t SERVICE_ERROR_DECIPHERING_ERROR;
        uint32_t SERVICE_ERROR_INVOCATION_COUNTER_ERROR;
    };
} SERVICE_ERROR;

#endif //DLMSAPDUPARSER_BASE_H
