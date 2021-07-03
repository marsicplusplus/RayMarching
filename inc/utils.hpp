#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#include <math.h>
#include <string>

typedef struct {
	int imgW;
	int imgH;
	float fov;
	int samplings;
	float minDist;
	float maxDist;
	float scale;
	float ratio;
	float frames;
	std::string filename;
} Options;

inline float deg2rad(float d){
	return d * 4.0f * atan(1.0)/180.0;
}

#endif
