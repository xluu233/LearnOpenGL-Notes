#pragma once


#include <glad/glad.h> // ����glad����ȡ���еı���OpenGLͷ�ļ�
#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <math.h>

#include "camera.hpp"
#include "stb_image.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/types.h>

#include <string>
#include <vector>

using std::vector;
using std::string;

static unsigned int gl_screenWidth = 1200;
static unsigned int gl_screenHeight = 800;

