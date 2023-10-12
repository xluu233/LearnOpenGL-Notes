#include <iostream>
#include <glad/glad.h>
#include <glfw3.h>
#include <windows.h>
#include "gl_window.h"
#include "gl_light_color.h"
#include <string>

GLFWwindow* glfWindow;

int initOpenGL()
{
	//��ʼ��glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//��ʼ������
	glfWindow = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
	if (glfWindow == nullptr)
	{
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent(glfWindow);

	//��ʼ��glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "glad failed to init" << std::endl;
		return -1;
	}

	return 0;
}


int main()
{
	std::cout << "hello world" << std::endl;
	int res = initOpenGL();
	if (res == -1)
	{
		return -1;
	}

	//���ڲ���
	gl_window win_test(glfWindow);
	//win_test.createWindow();
	//win_test.createTriangle();
	//win_test.createTwoTriangle();
	//win_test.testShader();
	//win_test.testTextpures();
	win_test.testTextpures2();
	//win_test.testMatrix();
	//win_test.test3DBoxs();
	//win_test.testCamera();

	//gl_light_color lightColor(glfWindow);
	//lightColor.createLightSource2();
	//std::string path("..//resource//nanosuit//nanosuit.obj");
	//lightColor.loadModel(path);



	//ɾ��glf��Դ
	glfwTerminate();
	return 0;
}
