#include "gpu_renderer.hpp"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

GPURenderer::GPURenderer(Options &opt) : opts(opt) {
	if(!glfwInit()){
		std::cerr << "ERROR: cannot start GLFW3\n";
		exit(1);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD\n";
		glfwTerminate();
		exit(1);
	}
	
	compute.loadShader("compute.glsl", GL_COMPUTE_SHADER);
	compute.compileShaders();

	frameBuffer.reserve(opts.imgW * opts.imgH);

	glGenBuffers(1, &ssboFb);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssboFb);
	glBufferData(GL_SHADER_STORAGE_BUFFER, opts.imgW * opts.imgH * 3 * sizeof(float), GLDYNA);
}

void GPURenderer::render() {
	compute.use();
	glDispatchCompute(opts.imgW, opts.imgH, 1);
}
