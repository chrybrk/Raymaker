#include "Utils.h"

Color GetRandomColor() {
    return (Color){ 
			(unsigned char)GetRandomValue(0, 255), 
			(unsigned char)GetRandomValue(0, 255), 
			(unsigned char)GetRandomValue(0, 255), 255 
		};
}

Color LerpColor(Color start, Color end, float t) {
    Color result;
    result.r = (unsigned char)roundf(start.r + t * (end.r - start.r));
    result.g = (unsigned char)roundf(start.g + t * (end.g - start.g));
    result.b = (unsigned char)roundf(start.b + t * (end.b - start.b));
    result.a = 255; // Alpha remains constant
    return result;
}
