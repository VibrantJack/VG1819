#pragma once
#define LERP(amount,min,max) (((1-amount)*min + amount*max))
#define CLAMP(amount,min,max) ((amount>=max?max:(amount<min?min:amount)))
#define MAX(a,b) (a>b?a:b)
#define MIN(a,b) (a<b?a:b)

#define SWAP(a,b) auto temp = a; a = b; b = temp

#define PI 3.14159265359
#define DEG_TO_RAD_FACTOR 0.01745329251