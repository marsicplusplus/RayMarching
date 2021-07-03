#include "cpu_renderer.hpp"
#include "ray.hpp"
#include <thread>
#include <iostream>
#include <fstream>

void RenderJob::renderPixel() {
	Vec3 colors(0.0f);
	for(int k = 0; k < opts.samplings; k++){
		float off = -0.4f + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(0.8f)));
		float x = (2 * (xy.x + 0.5+off) / (float) opts.imgW - 1) * opts.ratio * opts.scale;
		float y = (1 - 2 * (xy.y + 0.5+off) / (float) opts.imgH) * opts.scale;

		Vec3 rayOrig = Vec3(x, y, -1.0f);
		Vec3 dir = rayOrig - world.camera.pos;
		dir.normalize();
		Ray ray(rayOrig, dir);
		colors = colors + ray.march(world, opts.minDist, opts.maxDist);
	}
	colors /= opts.samplings;
	fb[pixel] = colors;
}

CPURenderer::CPURenderer(Options &opt, World &world) : opts(opt), world(world), jobsManager(std::thread::hardware_concurrency(), 1){
	frameBuffer.reserve(opts.imgW * opts.imgH);
}

void CPURenderer::render() {
	for(int f = 0; f < opts.frames; f++){
		jobsManager.init();
		std::cout << "Rendering " << f << "/" << opts.frames << std::endl;
		int pixel = 0;
		for(int j = 0; j < opts.imgH; ++j){
			for(int i = 0; i < opts.imgW; ++i){
				std::shared_ptr<RenderJob> job = std::make_shared<RenderJob>(frameBuffer, pixel++, Vec3(i, j, 0), world, opts);
				jobsManager.submit(job);
			}
		}

		jobsManager.join();

		char tmpName[128];
		sprintf(tmpName, "%s%d.ppm", opts.filename.c_str(), f);
		std::ofstream ofs(tmpName); 
		ofs << "P3\n" << opts.imgW << " " << opts.imgH << "\n255\n";
		for(int i = 0; i < opts.imgH * opts.imgW; ++i) {
			ofs << static_cast<int>(255.999f * frameBuffer[i].x) << ' '
				<< static_cast<int>(255.999f * frameBuffer[i].y) << ' '
				<< static_cast<int>(255.999f * frameBuffer[i].z) << '\n';
		}
		ofs.close();

		world.update();
	}
}
