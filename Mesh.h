#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>
#include <vector>

#include "Vertex.h"
#include "shaderprogram.h"

class Mesh {
public:
	Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::string& name);
	void setMatrixS(glm::mat4 matrix);
	void setMatrixM(glm::mat4 matrix);
	void setMatrixV(glm::mat4 matrix);
	void setMatrixP(glm::mat4 matrix);
	void setMatrices(glm::mat4 _M, glm::mat4 _V, glm::mat4 _P);
	void setTextures(GLuint diffuse, GLuint reflect);
	void draw(ShaderProgram* sp);
	const std::string& getName();

private:
	std::string name;
	int vertexCount = 0;             // Number of vertices
	float* verticesData = nullptr;   // Pointer to vertex data, if needed
	float* normalsData = nullptr;    // Pointer to normal data, if needed
	float* texCoordsData = nullptr;  // Pointer to texture coordinates data, if needed

	int indexesCount = 0;                 // Number of indices
	unsigned int* indexesData = nullptr;  // Pointer to index data, if needed

	glm::mat4 S = glm::mat4(1.0);
	glm::mat4 M = glm::mat4(1.0);
	glm::mat4 V = glm::mat4(1.0);
	glm::mat4 P = glm::mat4(1.0);

	GLuint texDiffuse = 0;
	GLuint texReflect = 0;


};