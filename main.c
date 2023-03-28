#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser/include/parser.h"

unsigned char GetRequestNormal[15] = {0x00, 0x0D, 0xC0, 0x01, 0xC1,
                                      0x00, 0x08, 0x00, 0x00, 0x01,
                                      0x00, 0x00, 0xFF, 0x02, 0x00};

int main()
{
    xDLMS_APDU *xDlmsApdu = convert_data_to_xDLMS_APDU(GetRequestNormal, 15, NULL);
    if (xDlmsApdu != NULL)
    {
        int32_t lengthData = 0;
        unsigned char *data = convert_xDLMS_APDU_to_data(xDlmsApdu, &lengthData, NULL);
        if (data != NULL)
        {
            int ret = memcmp(GetRequestNormal, data, 15);
            if (ret == 0)
            {
                printf("True\n");
            }
            else
            {
                printf("False\n");
            }
            free(data);
            data = NULL;
        }
    }

    free_xDLMS_APDU(&xDlmsApdu);
    return 0;
}
