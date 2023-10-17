#pragma once
#ifndef GL_LIGHT_COLOR_H
#define GL_LIGHT_COLOR_H

#include "glhelper.h"
#include "model.h"
#include "camera.hpp"
#include "shader.h"
#include <string>


class gl_light_color
{
private:
	GLFWwindow* window;

	//camera
	//Camera camera;
	//Camera camera;

	//lighting
	glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.0f);

	//物体颜色和光照颜色
	glm::vec3 cubeColor = glm::vec3(1.0f, 0.5f, 0.31f);
	glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);


	//float deltaTime{ 0.0f };
	//float lastFrame{ 0.0f };

	//处理键盘事件
	//void processInput(GLFWwindow* window);

public:
	gl_light_color(GLFWwindow* window)
	{
		this->window = window;
		glViewport(0, 0, gl_screenWidth, gl_screenHeight);

		camera.Front = glm::vec3(0.0f, 0.0f, -3.0f);

		glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
			gl_screenWidth = width;
			gl_screenHeight = height;
			std::cout << "size changed, width:" << width << " height:" << height << std::endl;
			glViewport(0, 0, width, height);
		});
	};

	void createLightSource();

	void createLightSource2();


};

#endif