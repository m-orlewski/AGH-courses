#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>
#include <time.h>
#include <assert.h>

float reduction_wrapper(float * input, unsigned int data_size);

inline cudaError_t checkCudaError(cudaError_t result);

float sumHost(const float * input, unsigned int data_size);

void init(float * input, unsigned int data_size);

__global__
void sumReduction(const float * input, int data_size, float * partial_sums)
{
	extern __shared__ float partSum[];
	
	int block_size = blockDim.x;
	int th = threadIdx.x;
	int start = 2 * blockIdx.x * block_size;

// Original shared memory initialization
	if (th+start < data_size)
		partSum[th] = input[start+th];
	else
		partSum[th] = 0;

	if (th+start+block_size < data_size)
		partSum[th+block_size] = input[start+th+block_size];
	else
		partSum[th+block_size] = 0;	

/*
//2nd shared memory optimization
	if (th+start < data_size)
	{
		if (th+start+block_size < data_size)
			partSum[th] = input[start+th] + input[start+th+block_size];
		else
			partSum[th] = input[start+th];
	}
	else
	{
		partSum[th] = 0;
	}
*/

//Original loop
	for (int stride=1; stride <= blockDim.x; stride *=2)
	{
		__syncthreads();
		if (th % stride == 0)
			partSum[2*th] += partSum[2*th + stride];
	}


/*
//1st loop optimization
	for (int i=block_size; i > 0; i /= 2)
	{
		__syncthreads();
		if (th < i)
			partSum[th] += partSum[th + i];
	}
/*

/*
//2nd loop optimization
	for (int i=block_size/2; i > 0; i /= 2)
	{
		__syncthreads();
		if (th < i)
			partSum[th] += partSum[th + i];
	}
*/
	
	__syncthreads();
	if (th == 0)
	{
		partial_sums[blockIdx.x] = partSum[0];
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

	float * h_input = (float *)malloc(data_size * sizeof(float));
	if (h_input == NULL)
	{
		fprintf(stderr, "Unable to allocate memory for input array.\n");
		exit(EXIT_FAILURE);
	}

	init(h_input, data_size);

	float * d_input;
	checkCudaError(cudaMalloc(&d_input, data_size * sizeof(float)));
	checkCudaError(cudaMemcpy(d_input, h_input, data_size * sizeof(float), cudaMemcpyHostToDevice));

	float device_sum = reduction_wrapper(d_input, data_size);
	float host_sum = sumHost(h_input, data_size);

	if (device_sum == host_sum)
	{
		printf("Results are correct! (%f == %f)\n", device_sum, host_sum);
	}
	else
	{
		printf("Something went wrong! (%f != %f)\n", device_sum, host_sum);
	}

	cudaFree(d_input);
	free(h_input);

	return 0;
}

float reduction_wrapper(float * input, unsigned int data_size)
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

	int numOfThreads = prop.maxThreadsPerBlock;

	while (2 * numOfThreads * sizeof(float) > prop.sharedMemPerBlock)//to not excess our shared memory limit
	{
		numOfThreads -= 32;//to fully use warps
	}
	
	int partial_sums = data_size/(numOfThreads * 2); 

	if (data_size % (numOfThreads * 2))
	{
		partial_sums++;
	}

	int numOfBlocks = partial_sums; // each block will calculate one partial sum
	
	float * h_output = (float *)calloc(partial_sums, sizeof(float));
	if (h_output == NULL)
	{
		fprintf(stderr, "Unable to allocate memory for partial sums array.\n");
		exit(EXIT_FAILURE);
	}

	float * d_output;
	checkCudaError(cudaMalloc(&d_output, partial_sums * sizeof(float)));
	checkCudaError(cudaMemcpy(d_output, h_output, partial_sums * sizeof(float), cudaMemcpyHostToDevice));

	cudaEvent_t start, stop;
	checkCudaError(cudaEventCreate(&start));
	checkCudaError(cudaEventCreate(&stop));

	checkCudaError(cudaEventRecord(start));

	sumReduction<<<numOfBlocks, numOfThreads, 2*numOfThreads*sizeof(float)>>>(input, data_size, d_output);
	checkCudaError(cudaDeviceSynchronize());

	checkCudaError(cudaMemcpy(h_output, d_output, partial_sums * sizeof(float), cudaMemcpyDeviceToHost));

	float sum = 0;
	for (int i=0; i < partial_sums; i++)
	{	
		sum += h_output[i];
	}
	checkCudaError(cudaEventRecord(stop));

	float time = 0;
	checkCudaError(cudaEventElapsedTime(&time, start, stop));

	printf("Sum on GPU was calculated in %f miliseconds\n", time);

	cudaFree(d_output);
	free(h_output);

	return sum;
}

inline cudaError_t checkCudaError(cudaError_t result)
{
	if (result != cudaSuccess)
	{
		fprintf(stderr, "Cuda Error: %s\n", cudaGetErrorString(result));
		assert(result == cudaSuccess);
	}
	return result;
}

float sumHost(const float * input, unsigned int data_size)
{
	clock_t start, stop;

	start = clock();	

	float sum = 0;
	for (unsigned int i=0; i < data_size; i++)
		sum += input[i];

	stop = clock();

	printf("Sum on CPU was calculated in %f miliseconds\n", 1000 * (double)(stop - start)/(double)CLOCKS_PER_SEC);

	return sum;
}

void init(float * input, unsigned int data_size)
{
	for (unsigned int i=0; i < data_size; i++)
	{
		input[i] = (float)(rand() % 2);
	}	
} 
