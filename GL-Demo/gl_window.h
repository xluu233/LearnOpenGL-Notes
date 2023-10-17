#pragma once
#ifndef GL_WINDOWS_H
#define GL_WINDOWS_H


#include <glad/glad.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "stb_image.h"
#include "glhelper.h"


class gl_window
{
private:
	GLFWwindow* window;


public:
	gl_window(GLFWwindow* window);

	void createWindow();

	//������
	void createTriangle();

	//���������
	void createTwoTriangle();

	//��ɫ������
	void testShader();

	//�������
	void testTextpures();
	void testTextpures2();

	//�������
	void testMatrix();

	void test3DBox();

	void test3DBoxs();

	void testCamera();

};
#endif // !GL_WINDOWS_H
