#include <cuda_runtime.h>
#include <stdio.h>

#define CHECK(call)                                                         \
{                                                                           \
    const cudaError_t error = call;                                         \
    if (error != cudaSuccess) {                                             \
        printf("Error: %s:%d, ", __FILE__, __LINE__);                       \
        printf("code: %d, reason: %s\n", error, cudaGetErrorString(error)); \
        exit(1);                                                            \
    }                                                                       \
}

int main() {
    int deviceCount;
    CHECK(cudaGetDeviceCount(&deviceCount));

    if (deviceCount == 0) {
        printf("There are no available CUDA devices.\n");
    } else {
        printf("There are %d available CUDA devices:\n", deviceCount);
        for (int i = 0; i < deviceCount; i++) {
            cudaDeviceProp deviceProp;
            CHECK(cudaGetDeviceProperties(&deviceProp, i));
            printf("Device %d: %s\n", i, deviceProp.name);
        }
    }

    return 0;
}

/*
$ nvcc cudaDeviceCount.cu -o device
$ ./device 
There are 1 available CUDA devices:
Device 0: NVIDIA GeForce RTX 4070 Laptop GPU
*/