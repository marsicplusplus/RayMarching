#ifndef __SPHERE_HPP__
#define __SPHERE_HPP__

#include "hittable.hpp"

class Sphere : public Hittable {
	public:
		Vec3 center;
		float radius;
		Vec3 dispFactor;

	public:
		Sphere(Vec3 c, float r) : Hittable(SPHERE), center(c), radius(r), dispFactor{0.0f} {}
		Sphere(Vec3 c, float r, Vec3 disp) : Hittable(SPHERE), center(c), radius(r), dispFactor(disp){}
		virtual float SDF (Vec3 p) const {
			Vec3 tmp = p - center;
			float disp = sin(dispFactor.x*p.x)*sin(dispFactor.y*p.y)*sin(dispFactor.z*p.z);
			return (tmp.length() - radius) + disp;
		}
};

#endif
