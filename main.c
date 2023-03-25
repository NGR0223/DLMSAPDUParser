#include <stdio.h>
#include "parser/include/parser.h"

unsigned char GetRequestNormal[21] = {0x00, 0x01, 0x00, 0x11, 0x00,
                                      0x01, 0x00, 0x0D, 0xC0, 0x01,
                                      0xC1, 0x00, 0x08, 0x00, 0x00,
                                      0x01, 0x00, 0x00, 0xFF, 0x02,
                                      0x00};

int main()
{
    convert_data_to_DLMS_APDU(GetRequestNormal, 21, NULL);
}
