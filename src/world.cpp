#include <limits>
#include "cube.hpp"
#include "sphere.hpp"
#include "world.hpp"

World::World() {
	hittables.push_back(std::make_unique<Sphere>(Vec3(0.0f, 0.0f, -2.0f), 0.2f));
	hittables.push_back(std::make_unique<Sphere>(Vec3(-0.3f, -0.3f, -1.7f), 0.2f));
	hittables.push_back(std::make_unique<Sphere>(Vec3(0.3f, 0.3f, -1.3f), 0.2f));
	hittables.push_back(std::make_unique<Cube>(Vec3(0.0f, 0.0f, -4.0f), Vec3(0.5, 0.5, 0.5)));
	lights.push_back(Light{Vec3(4.0f, 0.0f, -1.0), Vec3(0.3, 0.3, 0.4)});
	lights.push_back(Light{Vec3(-4.0f, 4.0f, -2.0), Vec3(0.3, 0.3, 0.3)});
	lights.push_back(Light{Vec3(0.0f, 4.0f, 1.0), Vec3(0.3, 0.3, 0.2)});
	lights.push_back(Light{Vec3(0.0f, -2.0f, 1.0), Vec3(0.1, 0.1, 0.1)});
	camera.pos = Vec3(0.0f);
}

float World::mapWorld(Vec3 v) const {
	float minSDF = std::numeric_limits<float>::max();
	for(auto &o : hittables){
		minSDF = std::min(o->SDF(v), minSDF);
	}
	return minSDF;
}

Vec3 World::calcLights(Vec3 &v, Vec3 &normal) const {
	Vec3 ambientColor(0.4f, 0.4f, 0.4f);
	Vec3 ka(0.4f);
	Vec3 color;
	normal.normalize();
	for(auto &l : lights){
		Vec3 lightPos = l.pos-v;
		lightPos.normalize();
		float LN = lightPos.dot(normal);
		float diff = fmax(LN, 0.0f);
		color = color + diff*l.color;
	}
	// Lightness = kambient · cambient + kdiffuse · cdiffuse · (L · N) + kspecular · (RL · V)n · cspecular
	return color + ambientColor * ka;
	//return color;
}

void World::update() {
	for(auto &h : hittables){
		if(h->type == CUBE){
			(dynamic_cast<Cube&>(*h)).center = Vec3(0.1f) + (dynamic_cast<Cube&>(*h)).center;
		}
		if(h->type == SPHERE){
			(dynamic_cast<Sphere&>(*h)).dispFactor= Vec3(0.1f, 0.4f, 0.5f) + (dynamic_cast<Sphere&>(*h)).dispFactor;
		}
	}
}
