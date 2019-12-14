#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

#include "prime.h"

#define NUM_THREADS 4

typedef struct
{
	long long int number;
	long long int start;
	long long int end;
} thread_data;

bool is_prime = true;

void *check_prime_thread(void *arg)
{
	thread_data *td = (thread_data *)arg;

	for (; td->start <= td->end; (td->start) += 6)
	{
		if (is_prime == false)
			pthread_exit(NULL);

		if (td->number % (td->start) == 0 || td->number % ((td->start) + 2) == 0)
			is_prime = false;
	}
	pthread_exit(NULL);
}

bool prime_multithreaded(long long int p)
{
	if (p <= 3)
		return true;
	if (p % 2 == 0 || p % 3 == 0)
		return false;

	long long int start = 5;
	long long int upper_bound = (long long int)sqrt(p);
	int thread_running = 0;
	long long int steps = upper_bound / NUM_THREADS;
	if (steps == 0)
		steps = 1;
	is_prime = true;

	pthread_t tid[NUM_THREADS];
	thread_data td[NUM_THREADS];

	for (int i = 0; i < NUM_THREADS; i++)
	{
		if (start >= upper_bound)
			break;
		td[i].number = p;
		td[i].start = start;

		if (steps == 1 || i == NUM_THREADS - 1)
			start = upper_bound + 1;
		else
			start += steps;

		td[i].end = start - 1;

		if (pthread_create(&tid[i], NULL, check_prime_thread, (void *)&td[i]) != 0)
		{
			printf("Thread creation failed");
			exit(1);
		}
		thread_running++;
	}

	if (thread_running > 0)
	{
		for (int i = 0; i < thread_running; i++)
			pthread_join(tid[i], NULL);

		if (is_prime == false)
			return false;
	}

	return true;
	pthread_exit(NULL);
}