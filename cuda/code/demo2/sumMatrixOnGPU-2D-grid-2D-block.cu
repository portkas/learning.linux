#include <cuda_runtime.h>
#include <stdio.h>
#include <sys/time.h>

#define CHECK(call)                                                         \
{                                                                           \
    const cudaError_t error = call;                                         \
    if (error != cudaSuccess) {                                             \
        printf("Error: %s:%d, ", __FILE__, __LINE__);                       \
        printf("code: %d, reason: %s\n", error, cudaGetErrorString(error)); \
        exit(1);                                                            \
    }                                                                       \
}

void initialData(float *ip, const int size)
{
    int i;

    for(i = 0; i < size; i++)
    {
        ip[i] = (float)(rand() & 0xFF) / 10.0f;
    }

    return;
}

void sumMatrixOnHost(float *A, float *B, float *C, const int nx,
                     const int ny)
{
    float *ia = A;
    float *ib = B;
    float *ic = C;

    for(int iy = 0; iy < ny; iy++){
        for(int ix = 0; ix < nx; ix++){
            ic[ix] = ia[ix] + ib[ix];
        }

        ia += nx;
        ib += nx;
        ic += nx;
    }

    return;
}

__global__ void sumMatrixOnGPU2D(float *MatA, float *MatB, float *MatC, 
                                 int nx, int ny)
{
    unsigned int ix = threadIdx.x + blockIdx.x * blockDim.x;
    unsigned int iy = threadIdx.y + blockIdx.y * blockDim.y;
    unsigned int idx = iy * nx + ix;
    if(ix<nx && iy<ny){
        MatC[idx] = MatA[idx] + MatB[idx];
    }
}

void checkResult(float *hostRef, float *gpuRef, const int N)
{
    double epsilon = 1.0E-8;
    bool match = 1;

    for (int i = 0; i < N; i++)
    {
        if (abs(hostRef[i] - gpuRef[i]) > epsilon)
        {
            match = 0;
            printf("host %f gpu %f\n", hostRef[i], gpuRef[i]);
            break;
        }
    }

    if (match)
        printf("Arrays match.\n\n");
    else
        printf("Arrays do not match.\n\n");
}

inline double seconds()
{
    struct timeval tp;
    struct timezone tzp;
    int i = gettimeofday(&tp, &tzp);
    return ((double)tp.tv_sec + (double)tp.tv_usec * 1.e-6);
}

int main(int argc, char **argv){
    printf("%s Starting...\n", argv[0]);
    // set up device
    int dev = 0;
    cudaDeviceProp deviceProp;
    CHECK(cudaGetDeviceProperties(&deviceProp, dev));
    printf("Using Device %d: %s\n", dev, deviceProp.name);
    CHECK(cudaSetDevice(dev));

    // set up data size of matrix
    int nx = 1 << 14;
    int ny = 1 << 14;
    int nxy = nx*ny;
    int nBytes = nxy * sizeof(float);

    // malloc host memory
    float *h_A, *h_B, *hostRef, *gpuRef;
    h_A = (float *)malloc(nBytes);
    h_B = (float *)malloc(nBytes);
    hostRef = (float *)malloc(nBytes);
    gpuRef = (float *)malloc(nBytes);

    // initialize data at host side
    double iStart = seconds();
    initialData(h_A, nxy);
    initialData(h_B, nxy);
    double iElaps = seconds() - iStart;
    printf("Matrix initialization elapsed %f sec\n", iElaps);
    memset(hostRef, 0, nBytes);
    memset(gpuRef, 0, nBytes);

    // add matrix at host side
    iStart = seconds();
    sumMatrixOnHost(h_A, h_B, hostRef, nx, ny);
    iElaps = seconds() - iStart;
    printf("sumMatrixOnHost elapsed %f sec\n", iElaps);

    // malloc device global memory
    float *d_MatA, *d_MatB, *d_MatC;
    CHECK(cudaMalloc((void **)&d_MatA, nBytes));
    CHECK(cudaMalloc((void **)&d_MatB, nBytes));
    CHECK(cudaMalloc((void **)&d_MatC, nBytes));

    // transfer data from host to device
    CHECK(cudaMemcpy(d_MatA, h_A, nBytes, cudaMemcpyHostToDevice));
    CHECK(cudaMemcpy(d_MatB, h_B, nBytes, cudaMemcpyHostToDevice));

    // invoke kernel at host sude
    int dimx = 32;
    int dimy = 16;
    dim3 block(dimx, dimy);
    dim3 grid((nx + block.x - 1)/block.x, (ny + block.y -1)/block.y);

    iStart = seconds();
    sumMatrixOnGPU2D<<<grid, block>>>(d_MatA, d_MatB, d_MatC, nx, ny);
    CHECK(cudaDeviceSynchronize());
    iElaps = seconds() - iStart;
    printf( "sumMatrixOnGPU2D <<<(%d,%d), (%d,%d)>>> elapsed %f sec\n", 
            grid.x, grid.y,
            block.x, block.y, iElaps);

    // check kernel error
    CHECK(cudaGetLastError());

    // copy kernel result back to host side
    CHECK(cudaMemcpy(gpuRef, d_MatC, nBytes, cudaMemcpyDeviceToHost));

    // check device result
    checkResult(hostRef, gpuRef, nxy);

    // free device global memory
    CHECK(cudaFree(d_MatA));
    CHECK(cudaFree(d_MatB));
    CHECK(cudaFree(d_MatC));

    // free host memory
    free(h_A);
    free(h_B);
    free(hostRef);
    free(gpuRef);

    // reset device
    CHECK(cudaDeviceReset());

    return (0);
}