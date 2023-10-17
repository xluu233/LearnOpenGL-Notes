#pragma once

#include <glad/glad.h> // 包含glad来获取所有的必须OpenGL头文件
#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "stb_image.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/types.h>

#include <string>
#include <vector>
#include <iostream>
#include <math.h>


#include "camera.hpp"
#include "model.h"
#include "shader.h"

extern GLFWwindow* glfWindow;

using std::vector;
using std::string;


extern float mixValue;

extern unsigned int gl_screenWidth;
extern unsigned int gl_screenHeight;

extern float lastX;
extern float lastY;

extern bool firstMouse;
extern float deltaTime;	// time between current frame and last frame
extern float lastFrame;


extern float yaw;
extern float pitch;
extern float fov;
extern glm::vec3 cameraPos;
extern glm::vec3 cameraFront;
extern glm::vec3 cameraUp;
extern Camera camera;

unsigned int loadTexture(char const* path);
unsigned int loadCubemap(vector<std::string> faces);

//回调函数，用于监听窗口大小改变
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);


void mouse_callback2(GLFWwindow* window, double xposIn, double yposIn);
void scroll_callback2(GLFWwindow* window, double xoffset, double yoffset);
