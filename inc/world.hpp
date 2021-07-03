#ifndef __WORLD_HPP__
#define __WORLD_HPP__

#include "camera.hpp"
#include "hittable.hpp"
#include <vector>

typedef struct {
	Vec3 pos;
	Vec3 color;
} Light;


class World {
	public:
		std::vector<HittablePtr> hittables;
		std::vector<Light> lights;
		Camera camera;
		float dispFactor;

	public:
		World();
		float mapWorld(Vec3 v) const;
		Vec3 calcLights(Vec3 &v, Vec3 &normal) const;
		void update();
};

#endif
