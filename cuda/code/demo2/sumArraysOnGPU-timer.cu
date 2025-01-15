#include <cuda_runtime.h>
#include <stdio.h>
#include <sys/time.h>

#define CHECK(call)                                                         \
{                                                                           \
    const cudaError_t error = call;                                         \
    if(error != cudaSuccess){                                               \
        printf("Error: %s:%d, ", __FILE__, __LINE__);                       \
        printf("code:%d, reason: %s\n", error, cudaGetErrorString(error));  \
        exit(1);                                                            \
    }                                                                       \
}                                                                           

void checkResult(float *hostRef, float *gpuRef, const int N){
    double epsilon = 1.0E-8;
    bool match = 1;

    for(int i=0; i<N; i++){
        if(abs(hostRef[i] - gpuRef[i]) > epsilon){
            match = 0;
            printf("Arrays do not match!]n");
            printf("host %5.2f gpu %5.2f at current %d\n", hostRef[i], gpuRef[i], i);
            break;
        }
    }

    if(match){
        printf("Arrays match.\n");
    }

    return;
}

// 初始化数组，生成随机浮点数填充数组ip
void initialData(float *ip, int size)
{
    time_t t;
    srand((unsigned) time(&t));

    for (int i = 0; i < size; i++)
    {
        ip[i] = (float)(rand() & 0xFF) / 10.0f;
    }

    return;
}

void sumArraysOnHost(float *A, float *B, float *C, const int N)
{
    for (int idx = 0; idx < N; idx++)
        C[idx] = A[idx] + B[idx];
}

// 核函数，在GPU上并行计算两个数组的和，每个线程处理一个元素的加法
__global__ void sumArrayOnGPU(float *A, float *B, float *C, const int N){
    // threadIdx 是一个预定义的变量，类型为 uint3，表示当前线程在块中的索引；
    // 在这个核函数中，每个线程处理一个元素的加法，因此 i 被设置为 threadIdx.x
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if(i<N) C[i] = A[i] + B[i];
}

inline double seconds()
{
    struct timeval tp;
    struct timezone tzp;
    int i = gettimeofday(&tp, &tzp);
    return ((double)tp.tv_sec + (double)tp.tv_usec * 1.e-6);
}

int main(int argc, char **argv)
{
    printf("%s Starting...\n", argv[0]);

    // 选择CUDA设备
    int dev = 0;
    cudaDeviceProp deviceProp;
    CHECK(cudaGetDeviceProperties(&deviceProp, dev));
    printf("Using Device %d: %s\n", dev, deviceProp.name);
    CHECK(cudaSetDevice(dev));

    // 定义数组大小
    int nElem = 1 << 24;
    printf("Vector size %d\n", nElem);

    // 申请CPU内存
    size_t nBytes = nElem * sizeof(float);
    float *h_A, *h_B, *hostRef, *gpuRef;
    h_A     = (float *)malloc(nBytes);
    h_B     = (float *)malloc(nBytes);
    hostRef = (float *)malloc(nBytes);
    gpuRef  = (float *)malloc(nBytes);

    // 在CPU端初始化时间
    double iStart, iElaps;
    iStart = seconds();
    initialData(h_A, nElem);
    initialData(h_B, nElem);
    iElaps = seconds() - iStart;
    printf("initialData Time elapsed %f sec\n", iElaps);
    memset(hostRef, 0, nBytes);
    memset(gpuRef,  0, nBytes);

    // CPU端执行数组加法函数
    iStart = seconds();
    sumArraysOnHost(h_A, h_B, hostRef, nElem);
    iElaps = seconds() - iStart;
    printf("sumArraysOnHost Time elapsed %f sec\n", iElaps);

    // GPU端申请全局内存
    float *d_A, *d_B, *d_C;
    CHECK(cudaMalloc((float**)&d_A, nBytes));
    CHECK(cudaMalloc((float**)&d_B, nBytes));
    CHECK(cudaMalloc((float**)&d_C, nBytes));

    // 将输入数据从主机CPU传输到设备GPU
    CHECK(cudaMemcpy(d_A, h_A, nBytes, cudaMemcpyHostToDevice));
    CHECK(cudaMemcpy(d_B, h_B, nBytes, cudaMemcpyHostToDevice));
    CHECK(cudaMemcpy(d_C, gpuRef, nBytes, cudaMemcpyHostToDevice));

    int iLen = 1024;
    dim3 block(iLen);
    dim3 grid((nElem+block.x-1)/block.x);

    iStart = seconds();
    sumArrayOnGPU<<<grid, block>>>(d_A, d_B, d_C, nElem);
    CHECK(cudaDeviceSynchronize());
    iElaps = seconds() - iStart;
    printf( "sumArraysOnGPU <<<  %d, %d  >>>  Time elapsed %f sec\n", 
            grid.x, block.x, iElaps);

    // 检查是否有错误信息
    CHECK(cudaGetLastError());
    CHECK(cudaMemcpy(gpuRef, d_C, nBytes, cudaMemcpyDeviceToHost));
    checkResult(hostRef, gpuRef, nElem);

    CHECK(cudaFree(d_A));
    CHECK(cudaFree(d_B));
    CHECK(cudaFree(d_C));

    free(h_A);
    free(h_B);
    free(hostRef);
    free(gpuRef);

    CHECK(cudaDeviceReset());
    return(0);
}

/*
$ nvcc sumArraysOnGPU-timer.cu -o timer
$ ./timer 
./timer Starting...
Using Device 0: NVIDIA GeForce RTX 4070 Laptop GPU
Vector size 16777216
initialData Time elapsed 0.419008 sec
sumArraysOnHost Time elapsed 0.018562 sec
sumArraysOnGPU <<<  32768, 512  >>>  Time elapsed 0.633475 sec
Arrays match.

$ ./timer 
./timer Starting...
Using Device 0: NVIDIA GeForce RTX 4070 Laptop GPU
Vector size 16777216
initialData Time elapsed 0.407757 sec
sumArraysOnHost Time elapsed 0.016320 sec
sumArraysOnGPU <<<  16384, 1024  >>>  Time elapsed 0.000998 sec
Arrays match.
*/