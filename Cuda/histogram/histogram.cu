
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <cuda.h>

const unsigned int MAX_BINS=4096;
const unsigned int SATURATION=256;

//wrapper function launches thathistogram kernel,
void histogram_wrapper(const unsigned int * input, const unsigned int data_size, unsigned int * histogram, cudaEvent_t start, cudaEvent_t stop);

//checks CUDA function calls for errors
inline cudaError_t checkCudaError(cudaError_t result);

//initializes input data
void init(unsigned int * input, const unsigned int data_size);

//histogram function
void histogram_function(const unsigned int * input, const unsigned int data_size, unsigned int * histogram);

//histogram kernel
__global__
void histogram_kernel(const unsigned int * input, const unsigned int data_size, unsigned int * histogram)
{
	extern __shared__ unsigned int local_histogram[];
	unsigned int th = threadIdx.x + blockIdx.x*blockDim.x;
	unsigned int stride = gridDim.x * blockDim.x;

	// initializing local_histogram
	for (unsigned int i=threadIdx.x; i < MAX_BINS; i += blockDim.x)
	{
		local_histogram[i] = 0;
	}

	__syncthreads();

	// filling local histogram
	for (unsigned int i=th; i < data_size; i += stride)
	{
		atomicAdd(&local_histogram[input[i]], 1);
	}

	__syncthreads();

	//updating global histogram
	for (unsigned int i=threadIdx.x; i < MAX_BINS; i += blockDim.x)
	{
		atomicAdd(&histogram[i], local_histogram[i]);
	}

}

//saturation kernel
__global__
void saturation(unsigned int * histogram)
{
	int tid = threadIdx.x + blockIdx.x * blockDim.x;
	int stride = blockDim.x * gridDim.x;

	for (int i=tid; i < MAX_BINS; i+=stride)
	{
		if (histogram[i]>SATURATION)
		{
			histogram[i] = SATURATION;
		}
	}
}


int main(int argc, char * argv[])
{
	unsigned int data_size;
	if (argc != 2)
	{
		fprintf(stderr, "Call to program should look like: %s <size of input data>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	else
	{
		data_size = (unsigned int)atoi(argv[1]);
	}

	//Host memory allocation
	unsigned int * h_input = (unsigned int *)malloc(data_size * sizeof(unsigned int));
	unsigned int * h_histogram = (unsigned int *)calloc(MAX_BINS, sizeof(unsigned int));

	if (!h_input || !h_histogram)
	{
		fprintf(stderr, "Memory allocation error.\n");
		exit(EXIT_FAILURE);
	}

	//Device memory allocation
	unsigned int * d_input;
	checkCudaError(cudaMalloc(&d_input, data_size*sizeof(unsigned int)));	
	
	unsigned int * d_histogram;
	checkCudaError(cudaMalloc(&d_histogram, MAX_BINS*sizeof(unsigned int)));

	// Creating events for timing histogram kernel
	cudaEvent_t start, stop;
	checkCudaError(cudaEventCreate(&start));
	checkCudaError(cudaEventCreate(&stop));

	// Coping memory from host to device
	checkCudaError(cudaMemcpy(d_input, h_input, data_size*sizeof(unsigned int), cudaMemcpyHostToDevice));
	checkCudaError(cudaMemcpy(d_histogram, h_histogram, MAX_BINS*sizeof(unsigned int), cudaMemcpyHostToDevice));

	histogram_wrapper(d_input, data_size, d_histogram, start, stop);

	// Coping memory from device to host
	checkCudaError(cudaMemcpy(h_input, d_input, data_size*sizeof(unsigned int), cudaMemcpyDeviceToHost));
	checkCudaError(cudaMemcpy(h_histogram, d_histogram, MAX_BINS*sizeof(unsigned int), cudaMemcpyDeviceToHost));
	
	unsigned int * h_histogram2 = (unsigned int *)calloc(MAX_BINS, sizeof(int));
	histogram_function(h_input, data_size, h_histogram2);
	

	for (int i=0; i < MAX_BINS; i++)
	{
		if (h_histogram[i] != h_histogram2[i])
		{
			printf("Histogram results do not match!\n");
			exit(EXIT_FAILURE);
		}
	}

	printf("Everything is fine!\n");

	

	return 0;
}

void histogram_wrapper(const unsigned int * input, const unsigned int data_size, unsigned int * histogram, cudaEvent_t start, cudaEvent_t stop)
{
	int deviceId;
	checkCudaError(cudaGetDevice(&deviceId));

	cudaDeviceProp prop;
	cudaGetDeviceProperties(&prop, deviceId);

	printf("\nDevice name: %s\n", prop.name);
	printf("Shared memory per block: %d\n", prop.sharedMemPerBlock);
	printf("Threads per block: %d\n", prop.maxThreadsPerBlock);
	printf("Number of SMs: %d\n", prop.multiProcessorCount);
	printf("Shared memory per SM: %d\n\n", prop.sharedMemPerMultiprocessor);

	checkCudaError(cudaEventRecord(start));
	histogram_kernel<<<prop.multiProcessorCount, prop.maxThreadsPerBlock, MAX_BINS*sizeof(unsigned int)>>>(input, data_size, histogram);
	checkCudaError(cudaEventRecord(stop));
	checkCudaError(cudaDeviceSynchronize());

	checkCudaError(cudaEventSynchronize(stop));
	float time = 0;
	checkCudaError(cudaEventElapsedTime(&time, start, stop));

	printf("Kernel was executed in %f miliseconds\n", time);

	//Saturation
	saturation<<<16, 256>>>(histogram); //pre set for 4096 bins

	checkCudaError(cudaDeviceSynchronize());
}

inline cudaError_t checkCudaError(cudaError_t result)
{
        if (result != cudaSuccess)
        {
                fprintf(stderr, "CUDA Error: %s\n", cudaGetErrorString(result));
                assert(result == cudaSuccess);
        }
        return result;
}

void init(unsigned int * input, const unsigned int data_size)
{
	for (unsigned int i=0; i < data_size; i++)
	{
		input[i] = (unsigned int)rand()%MAX_BINS;
	}
}

void histogram_function(const unsigned int * input, const unsigned int data_size, unsigned int * histogram)
{
	double start, stop;
	
	start = clock();
	for (unsigned int i=0; i < data_size; i++)
	{
		histogram[input[i]]++;
	}
	stop = clock();

	printf("Function was executed in %lf miliseconds\n",1000.0* (stop-start)/(double)CLOCKS_PER_SEC);

	//Saturation
	for (int i=0; i < MAX_BINS; i++)
	{
		if (histogram[i] > SATURATION)
		{
			histogram[i] = SATURATION;
		}
	}
}
