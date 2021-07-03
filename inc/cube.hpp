#ifndef __CUBE_HPP__
#define __CUBE_HPP__

#include "hittable.hpp"

class Cube : public Hittable {
	public:
		Vec3 center;
		Vec3 size;

	public:
		Cube(Vec3 center, Vec3 size) : Hittable(CUBE), center(center), size(size) {}

		virtual float SDF(Vec3 p) const {
			p = p - center;
			Vec3 q = vabs(p) - size;
			Vec3 tmp = vmax(q,Vec3(0.0));
			return tmp.length() + fmin(fmax(q.x,fmax(q.y,q.z)),0.0);
		}
};

#endif
