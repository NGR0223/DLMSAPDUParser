//
// Created by 720 on 2023/3/25.
//

#include <stdlib.h>
#include "../include/parser.h"

xDLMS_APDU *convert_data_to_DLMS_APDU(unsigned char *data, int32_t lengthData, int32_t *pErrorCode)
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
    gxByteBuffer *pByteBuffer = (gxByteBuffer *) calloc(1, sizeof(gxByteBuffer));
    bb_attach(pByteBuffer, data, lengthData, 2 * lengthData);

    return NULL;
}