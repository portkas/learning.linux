#include <stdio.h>
#include <stdint.h>

uint8_t s_ReadBuffer[256];  // 读缓冲区
uint16_t s_ReadBufferIndex = 0;  // 读缓冲区索引

uint8_t* DLPC_COMMON_UnpackBytes(int32_t Length)
{
    uint16_t CurReadBufferIndex = s_ReadBufferIndex;
    s_ReadBufferIndex += Length;

    return &s_ReadBuffer[CurReadBufferIndex];
}

int main() {
    // 填充读缓冲区作为示例
    for (int i = 0; i < 10; i++) {
        s_ReadBuffer[i] = (uint8_t)i;
    }

    // 提取5个字节
    uint8_t* data = DLPC_COMMON_UnpackBytes(5);

    // 打印提取的数据
    for (int i = 0; i < 5; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");

    return 0;
}
