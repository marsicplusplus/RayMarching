#ifndef __GPU_RENDER_HPP__
#define __GPU_RENDER_HPP__

#include "camera.hpp"
#include "utils.hpp"
#include "vec.hpp"
#include <vector>
#include "world.hpp"
#include "CPURenderer/job_system.hpp"

struct RenderJob : public IJob {
	public:
		RenderJob(std::vector<Vec3> &fb, int pixel, Vec3 xy, World &world, Options &opts) : fb(fb), pixel(pixel), xy(xy), world(world), opts(opts) {};
		~RenderJob() {}

		void start() {
			renderPixel();
		}
		
	private:
		void renderPixel();
		std::vector<Vec3> &fb;
		int pixel;
		Vec3 xy;
		World &world;
		Options &opts;
};

class CPURenderer {
	public:
		CPURenderer(Options &opts, World &world);
		void render();

	private:
		Options &opts;
		std::vector<Vec3> frameBuffer;
		World &world;
		float scale, ratio;
		JobManager jobsManager;
};

#endif
