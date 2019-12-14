#include <stdbool.h>
#include <math.h>

#include "prime.h"

bool prime_singlethreaded(long long int p) {
	if(p<=3) 
		return true;
	if(p%2==0 || p%3==0)
		return false;
	
	long long int i = 5;
	long long int upper_bound = (long long int) sqrt(p);
	for(; i <= upper_bound; i+=6)
	{
		if(p%i==0 || p%(i+2)==0) return false;
	}

	return true;
}
