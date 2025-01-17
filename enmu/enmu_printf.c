#include <stdio.h>

typedef enum
{
    DLPC34XX_ST_ONE_BIT_MONO = 0x0,/**< 1 Bit Mono */
    DLPC34XX_ST_ONE_BIT_RGB = 0x1,  /**< 1 Bit RGB */
    DLPC34XX_ST_EIGHT_BIT_MONO = 0x2, /**< 8 Bit Mono */
    DLPC34XX_ST_EIGHT_BIT_RGB = 0x3,  /**< 8 Bit RGB */
} DLPC34XX_SequenceType_e;

const char* getSequenceTypeName(DLPC34XX_SequenceType_e sequenceType) {
    switch (sequenceType) {
        case DLPC34XX_ST_ONE_BIT_MONO:
            return "1 Bit Mono";
        case DLPC34XX_ST_ONE_BIT_RGB:
            return "1 Bit RGB";
        case DLPC34XX_ST_EIGHT_BIT_MONO:
            return "8 Bit Mono";
        case DLPC34XX_ST_EIGHT_BIT_RGB:
            return "8 Bit RGB";
        default:
            return "Unknown Sequence Type";
    }
}

void printSequenceType(DLPC34XX_SequenceType_e sequenceType) {
    printf("%s\n", getSequenceTypeName(sequenceType));
}

int main() {
    DLPC34XX_SequenceType_e type = DLPC34XX_ST_EIGHT_BIT_RGB;
    printSequenceType(type);
    return 0;
}
