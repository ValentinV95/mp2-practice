#include "math.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

void zeros(double * mas, long long int size)
{
	memset(mas, 0, sizeof(double) * size);
}

void generated_vector(double * v, long long int size)
{
	for (long long int i = 0; i < size; i++)
	{
		v[i] = ((double)rand()) / RAND_MAX;	
	}
}

void generated_sparce_matrix(double * matrix, long long int size)
{
	for (long long int i = 0; i < size; i++)
	{
		for (long long int j = 0; j < size * 0.01; j++)
		{
			int index = rand() % size;
			matrix[i * size + index] += ((double)rand()) / RAND_MAX;
		}
	}
}

void mul_matrix_vector(double * matrix, double * x, long long int n, double * res)
{
	for (long long int i = 0; i < n; i++)
	{
		res[i] = 0.0;
		for (long long int j = 0; j < n; j++)
		{
			res[i] += matrix[i * n + j] * x[j];
		}
	}
}

double diff_vectors(double * a, double * b, int size)
{
	double diff = 0.0;
	for (int i = 0; i < size; i++)
	{
		diff += fabs(a[i] - b[i]);
	}
	return diff;
}

int main(int argc, char * argv[])
 {
	if (argc < 2)
	{
		printf("Not found arguments\n");
		return 1;
	}
	long long int n = atoi(argv[1]);
	double * dense_matrix = new double[n * n];
	double * x = new double[n];
	double * res1 = new double[n];
	double * res2 = new double[n];

	zeros(dense_matrix, n * n);
	zeros(x, n);
	zeros(res1, n);
	zeros(res2, n);

	generated_vector(x, n);
	generated_sparce_matrix(dense_matrix, n);

	//den -> csr

	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	mul_matrix_vector(dense_matrix, x, n, res1);
	high_resolution_clock::time_point t2 = high_resolution_clock::now();

	high_resolution_clock::time_point t3 = high_resolution_clock::now();
	//mul_matrix_vector csr -> res2
	high_resolution_clock::time_point t4 = high_resolution_clock::now();

	double diff = diff_vectors(res1, res2, n);

	auto duration_dense = duration_cast<microseconds>(t2 - t1).count();
	auto duration_csr = duration_cast<microseconds>(t4 - t3).count();

	cout << "Time dense matrix:" << duration_dense << endl;
	cout << "Time sparse matrix:" << duration_csr << endl;
	cout << "Diff result:" << diff << endl;

    return 0;
}

