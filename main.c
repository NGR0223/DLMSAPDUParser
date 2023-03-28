#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser/include/parser.h"

unsigned char GetRequestNormal[15] = {0x00, 0x0D, 0xC0, 0x01, 0xC1,
                                      0x00, 0x08, 0x00, 0x00, 0x01,
                                      0x00, 0x00, 0xFF, 0x02, 0x00};

void print_hex_data(const unsigned char *pData, int32_t lengthData)
{
    for (int i = 0; i < lengthData; ++i)
    {
        printf("%02x ", *(pData + i));
    }
    printf("\n");
}

void test()
{
    printf("Original Data:");
    print_hex_data(GetRequestNormal, 15);
    xDLMS_APDU *xDlmsApdu = convert_data_to_xDLMS_APDU(GetRequestNormal, 15, NULL);
    int32_t lengthData = 0;
    if (xDlmsApdu != NULL)
    {
        unsigned char *pData = convert_xDLMS_APDU_to_data(xDlmsApdu, &lengthData, NULL);
        if (pData != NULL)
        {
            int ret = memcmp(GetRequestNormal, pData, 15);
            if (ret == 0)
            {
                printf("No mutate Data:");
                print_hex_data(pData, 15);
            }
            else
            {
                printf("False\n");
            }
            free(pData);
            pData = NULL;
        }
    }

    mutate_xDLMS_APDU(xDlmsApdu, 0, NULL);
    unsigned char *pData = convert_xDLMS_APDU_to_data(xDlmsApdu, &lengthData, NULL);
    printf("Mutate 0 Data:");
    print_hex_data(pData, 15);

    mutate_xDLMS_APDU(xDlmsApdu, 1, NULL);
    pData = convert_xDLMS_APDU_to_data(xDlmsApdu, &lengthData, NULL);
    printf("Mutate 1 Data:");
    print_hex_data(pData, 15);

    mutate_xDLMS_APDU(xDlmsApdu, 2, NULL);
    pData = convert_xDLMS_APDU_to_data(xDlmsApdu, &lengthData, NULL);
    printf("Mutate 2 Data:");
    print_hex_data(pData, 15);

    mutate_xDLMS_APDU(xDlmsApdu, 3, NULL);
    pData = convert_xDLMS_APDU_to_data(xDlmsApdu, &lengthData, NULL);
    printf("Mutate 3 Data:");
    print_hex_data(pData, 15);

    free_xDLMS_APDU(&xDlmsApdu);
}

int main()
{
    test();

    return 0;
}
