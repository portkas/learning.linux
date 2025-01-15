#include <cuda_runtime.h>
#include <stdio.h>

// 在每个线程中打印当前线程的 threadIdx、blockIdx、blockDim 和 gridDim 信息
__global__ void checkIndex(){
    printf( "threadIdx:(%d, %d, %d) blockIdx:(%d, %d, %d) blockDim:(%d, %d, %d) gridDim:(%d, %d, %d)\n", 
            threadIdx.x, threadIdx.y, threadIdx.z, 
            blockIdx.x, blockIdx.y, blockIdx.z,
            blockDim.x, blockDim.y, blockDim.z,
            gridDim.x, gridDim.y, gridDim.z);
}

int main(){
    // 定义数据元素总数（程序需要处理的数据元素）
    // 将数据分成多个块，每个块处理一定数量的元素
    int nElem = 6;

    // 定义块的尺寸（一维）
    dim3 block(3);

    // 基于块和数据的大小计算网格尺寸（一维）
    // 每个块可以处理block.x个元素，计算总共需要多少个块来处理所有元素
    // 加block.x-1的目的是为了确保所有数据元素都能被处理，即使数据元素数不是块大小的整数倍
    // 如果 nElem 能被 block.x 整除，那么 nElem / block.x 就是正确的块数
    // 如果 nElem 不能被 block.x 整除，那么 nElem / block.x 会少计算一个块
    // 通过加上 block.x - 1，确保即使有余数，也能正确计算出足够的块数
    dim3 grid( (nElem+block.x-1)/block.x );

    // 主机端程序，用来检查网格和块维度
    printf("grid.x %d grid.y %d grid.z %d\n", grid.x, grid.y, grid.z);
    printf("block.x %d block.y %d block.z %d\n", block.x, block.y, block.z);
    checkIndex <<<grid, block>>>();
    cudaDeviceReset();
    return 0;
}

/*
$ nvcc -arch=sm_80 checkDimension.cu -o check
$ ./check 
grid.x 2 grid.y 1 grid.z 1
block.x 3 block.y 1 block.z 1
threadIdx:(0, 0, 0) blockIdx:(1, 0, 0) blockDim:(3, 1, 1) gridDim:(2, 1, 1)
threadIdx:(1, 0, 0) blockIdx:(1, 0, 0) blockDim:(3, 1, 1) gridDim:(2, 1, 1)
threadIdx:(2, 0, 0) blockIdx:(1, 0, 0) blockDim:(3, 1, 1) gridDim:(2, 1, 1)
threadIdx:(0, 0, 0) blockIdx:(0, 0, 0) blockDim:(3, 1, 1) gridDim:(2, 1, 1)
threadIdx:(1, 0, 0) blockIdx:(0, 0, 0) blockDim:(3, 1, 1) gridDim:(2, 1, 1)
threadIdx:(2, 0, 0) blockIdx:(0, 0, 0) blockDim:(3, 1, 1) gridDim:(2, 1, 1)
*/