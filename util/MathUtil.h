#pragma once
#define LERP(amount,min,max) (((1-amount)*min + amount*max))
#define CLAMP(amount,min,max) ((amount>=max?max:(amount<min?min:amount)))
#define MAX(a,b) (a>b?a:b)
#define MIN(a,b) (a<b?a:b)

#define SWAP(a,b) auto temp = a; a = b; b = temp

#define PI 3.14159265359
#define DEG_TO_RAD_FACTOR 0.01745329251

//Below is from https://stackoverflow.com/questions/6942273/how-to-get-a-random-element-from-a-c-container
template <typename I>
inline I random_element(I begin, I end)
{
	const unsigned long n = std::distance(begin, end);
	const unsigned long divisor = (RAND_MAX + 1) / n;

	unsigned long k;
	do { k = std::rand() / divisor; } while (k >= n);

	std::advance(begin, k);
	return begin;
}