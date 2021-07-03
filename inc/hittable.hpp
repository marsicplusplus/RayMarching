#ifndef __HITTABLE_HPP__
#define __HITTABLE_HPP__

#include <memory>
#include "vec.hpp"

typedef struct {
	Vec3 ka;
	Vec3 kd;
	Vec3 ks;
	float shiny;
} Material;

typedef enum {
	CUBE,
	SPHERE
} type_t;

class Hittable{
	public: 
		Hittable(type_t t) : type(t) {}
		virtual float SDF(Vec3 p) const = 0;
		type_t type;
};

typedef std::unique_ptr<Hittable> HittablePtr;

#endif
