#ifndef __RAY_HPP__
#define __RAY_HPP__

#include "vec.hpp"
#include "hittable.hpp"
#include <vector>
#include "world.hpp"

class Ray {
	public:
		Vec3 dir;
		Vec3 orig;

	public:
		Ray(Vec3 d, Vec3 o);
		Vec3 march(World& world, const float minDistance, const float maxDistance) const;
		Vec3 calcNormal(Vec3& at, World& world) const;
};

#endif
