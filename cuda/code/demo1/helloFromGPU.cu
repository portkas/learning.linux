#include <stdio.h>

// __global__修饰符告诉编译器这个函数将会从GPU中调用，在GPU上执行
__global__ void helloFromGPU(){
    printf("Hello World from GPU!\n");
}

int main(){
    printf("Hello World from CPU!\n");
    // 启动内核函数；
    // 三重尖括号意味着从主线程到设备端代码的调用；
    // 一个内核函数通过一组线程来执行，所有线程执行相同的代码；
    // 有十个线程被调用；
    helloFromGPU <<<1, 10>>>();
    // 显式地释放和清空当前进程中与当前设备有关的所有资源；
    cudaDeviceReset();
    return 0;
}

// $ nvcc -arch sm_80 helloFromGPU.cu -o hello
// GeForce RTX 4070 是基于 NVIDIA 的 Ada Lovelace 架构
// -arch sm_80使编译器为Ada lovelace架构生成设备代码；