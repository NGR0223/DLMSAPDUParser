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
    MUTATE_POSITION_GET_INVOKE_ID_AND_PRIORITY = 0,
    MUTATE_POSITION_GET_ATTRIBUTE_CLASS_ID = 1,
    MUTATE_POSITION_GET_ATTRIBUTE_INSTANCE_ID = 2,
    MUTATE_POSITION_GET_ATTRIBUTE_ATTRIBUTE_ID = 3,
} MUTATE_POSITION;

#endif //DLMSAPDUPARSER_BASE_H
