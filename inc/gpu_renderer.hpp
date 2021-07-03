#ifndef __GPU_RENDER_HPP__
#define __GPU_RENDER_HPP__

#include "utils.hpp"
#include "shader.hpp"
#include "vec.hpp"
#include <vector>

class GPURenderer {
	public: 

	public:
		GPURenderer(Options &opts);
		void render();

	private:
		Options opts;
		std::vector<Vec3> frameBuffer;
		unsigned int ssboFb;
		Shader compute;
};

#endif
