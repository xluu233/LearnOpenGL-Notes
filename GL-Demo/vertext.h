#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


//顶点
struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 Texcoords;

	// tangent
	glm::vec3 Tangent;
	// bitangent
	glm::vec3 Bitangent;
	//bone indexes which will influence this vertex
	int m_BoneIDs[MAX_BONE_INFLUENCE];
	//weights from each bone
	float m_Weights[MAX_BONE_INFLUENCE];
};


//纹理
struct Texture
{
	unsigned int id;	//纹理id
	std::string type;	//纹理属性，比如漫反射贴图或者是镜面光贴图
	aiString path;		// 我们储存纹理的路径用于与其它纹理进行比较
};
