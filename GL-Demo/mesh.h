#pragma once
#include <string>
#include <vector>
#include "shader.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/types.h>


//顶点
struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 Texcoords;

	glm::vec3 Tangent;
	glm::vec3 Bitangent;
};


//纹理
struct Texture
{
	unsigned int id;	//纹理id
	std::string type;	//纹理属性，比如漫反射贴图或者是镜面光贴图
	aiString path;		// 我们储存纹理的路径用于与其它纹理进行比较
};


class Mesh
{
public:
	//网格数据
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

	void Draw(Shader _shader);

private:
	/*  渲染数据  */
	unsigned int VAO, VBO, EBO;
	/*  函数  */
	void setupMesh();
};

