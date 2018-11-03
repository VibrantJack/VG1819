#pragma once
#define LERP(amount,min,max) (((1-amount)*min + amount*max))
#define CLAMP(amount,min,max) ((amount>=max?max:(amount<min?min:amount)))