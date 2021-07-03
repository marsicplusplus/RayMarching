#include <algorithm>
#include <fstream>
#include "hittable.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "vec.hpp"
#include "mat.hpp"
#include <vector>
#include "world.hpp"
#include "cpu_renderer.hpp"
#include "utils.hpp"

int main() {
	const float minDistance = 0.0001f;
	const float maxDistance = 1000.0f;
	const int imgW = 720;
	const int imgH = 720;
	const float fov = 90.0f;
	float scale = tan(deg2rad(fov * 0.5)); 
	float ratio = imgW / (float)imgH;
	const int samplings = 8;
	Options opt {
		imgW, imgH, fov, samplings, minDistance, maxDistance, scale, ratio, 30*6, "render"
	};

	std::vector<Vec3> frameBuffer(imgH * imgW);

	World world;
	CPURenderer renderer(opt, world);
	renderer.render();
}
