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


//����
struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 Texcoords;

	glm::vec3 Tangent;
	glm::vec3 Bitangent;
};


//����
struct Texture
{
	unsigned int id;	//����id
	std::string type;	//�������ԣ�������������ͼ�����Ǿ������ͼ
	aiString path;		// ���Ǵ��������·������������������бȽ�
};


class Mesh
{
public:
	//��������
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

	void Draw(Shader _shader);

private:
	/*  ��Ⱦ����  */
	unsigned int VAO, VBO, EBO;
	/*  ����  */
	void setupMesh();
};

