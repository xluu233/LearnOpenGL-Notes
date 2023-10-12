#pragma once
#ifndef GL_LIGHT_COLOR_H
#define GL_LIGHT_COLOR_H

#include "glhelper.h"
#include "model.h"
#include "camera.hpp"
#include "shader.h"

#include <string>



static int gl_screenWidth = 1200;
static int gl_screenHeight = 800;

class gl_light_color
{
private:
	GLFWwindow* window;


	float deltaTime{ 0.0f };
	float lastFrame{ 0.0f };

	//��������¼�
	void processInput(GLFWwindow* window);

	//C++�����Ա����������Ϊ�ص�������������Ϊÿ����Ա��������Ҫ��һ������ʵ��ȥ��������
	/*void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		screenWidth = width;
		screenHeight = height;
		std::cout << "size changed, width:" << width << " height:" << height << std::endl;
		glViewport(0, 0, width, height);
	};*/


public:
	gl_light_color(GLFWwindow* window)
	{
		this->window = window;
		glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
			gl_screenWidth = width;
			gl_screenHeight = height;
			std::cout << "size changed, width:" << width << " height:" << height << std::endl;
			glViewport(0, 0, width, height);
		});
	};

	void createLightSource();

	void createLightSource2();

	void loadModel(const std::string& path);

};

#endif