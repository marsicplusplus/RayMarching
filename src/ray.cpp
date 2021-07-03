#include "ray.hpp"
#include <limits>

Ray::Ray(Vec3 d, Vec3 o) : dir{d}, orig{o} {}

Vec3 Ray::march(World& world, const float minDistance, const float maxDistance) const {
	float t = 0.0f;
	const int maxSteps = 128;

	for(int i = 0; i < maxSteps; i++){
		Vec3 at = orig+dir*t;
		float minSDF = world.mapWorld(at);
		if(minSDF < minDistance){ 
			Vec3 normal = calcNormal(at, world);
			float ao = 1 - float(i) / (maxSteps-1);
			return ao*world.calcLights(at, normal);
		}
		t += minSDF;
		if(t > maxDistance) break;
	}
	float interp = 0.5*(dir.y + 1.0);
	return (1.0f - interp) * Vec3(0.30, 0.36, 0.60) + interp * Vec3(0.5f, 0.7f, 1.0f);
}

Vec3 Ray::calcNormal(Vec3 &at, World& world) const{
	float epsilon = 0.0001f;
	Vec3 normal(
			world.mapWorld(at + Vec3(epsilon, 0.0f, 0.0f)) - world.mapWorld(at - Vec3(epsilon, 0.0f, 0.0)),
			world.mapWorld(at + Vec3(0.0f, epsilon, 0.0f)) - world.mapWorld(at - Vec3(0.0f, epsilon, 0.0)),
			world.mapWorld(at + Vec3(0.0f, 0.0f, epsilon)) - world.mapWorld(at - Vec3(0.0f, 0.0f, epsilon)));
	return normal.normalize();
}
