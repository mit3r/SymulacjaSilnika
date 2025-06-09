#include "Mesh.h"

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::string& name) {
	this->name = name;
	this->vertexCount = vertices.size();
	this->verticesData = new float[vertexCount * 4];
	for (size_t i = 0; i < vertexCount; ++i) {
		this->verticesData[i * 4] = vertices[i].position.x;
		this->verticesData[i * 4 + 1] = vertices[i].position.y;
		this->verticesData[i * 4 + 2] = vertices[i].position.z;
		this->verticesData[i * 4 + 3] = vertices[i].position.w;
	}

	this->normalsData = new float[vertexCount * 4];
	for (size_t i = 0; i < vertexCount; ++i) {
		this->normalsData[i * 4] = vertices[i].normal.x;
		this->normalsData[i * 4 + 1] = vertices[i].normal.y;
		this->normalsData[i * 4 + 2] = vertices[i].normal.z;
		this->normalsData[i * 4 + 3] = vertices[i].normal.w;
	}

	this->indexesCount = indices.size();
	this->indexesData = new unsigned int[indexesCount];
	for (size_t i = 0; i < indexesCount; ++i) {
		this->indexesData[i] = indices[i];
	}
}

void Mesh::setMatrixS(glm::mat4 matrix)
{
	this->S = matrix;
}

void Mesh::setMatrixM(glm::mat4 matrix)
{
	this->M = matrix * S;
}

void Mesh::setMatrixP(glm::mat4 matrix)
{
	this->P = matrix;
}

void Mesh::setMatrices(glm::mat4 _M, glm::mat4 _V, glm::mat4 _P)
{
	this->M = _M;
	this->V = _V;
	this->P = _P;
}

void Mesh::setMatrixV(glm::mat4 matrix)
{
	this->V = matrix;
}

void Mesh::setTextures(GLuint diffuse, GLuint reflect)
{
	this->texDiffuse = diffuse;
	this->texReflect = reflect;
}


void Mesh::draw(ShaderProgram* sp) {
	glUniformMatrix4fv(sp->u("P"), 1, false, glm::value_ptr(this->P));
	glUniformMatrix4fv(sp->u("V"), 1, false, glm::value_ptr(this->V));
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(this->M));

	glUniform1i(sp->u("textureDiffuse"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texDiffuse);

	glUniform1i(sp->u("textureReflect"), 1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texReflect);

	glEnableVertexAttribArray(sp->a("vertex"));  // Włącz przesyłanie danych do atrybutu vertex
	glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, this->verticesData);

	glEnableVertexAttribArray(sp->a("normal"));  // Włącz przesyłanie danych do atrybutu normal
	glVertexAttribPointer(sp->a("normal"), 4, GL_FLOAT, false, 0, this->normalsData);

	glEnableVertexAttribArray(sp->a("texCoord0"));  // Włącz przesyłanie danych do atrybutu texCoord0
	glVertexAttribPointer(sp->a("texCoord0"), 4, GL_FLOAT, false, 0, this->verticesData);

	glDrawElements(GL_TRIANGLES, this->indexesCount, GL_UNSIGNED_INT, this->indexesData);
	// glDrawArrays(GL_TRIANGLES, 0, this->vertexCount); //Narysuj obiekt

	glDisableVertexAttribArray(sp->a("vertex"));  // Wyłącz przesyłanie danych do atrybutu vertex
	glDisableVertexAttribArray(sp->a("normal"));  // Wyłącz przesyłanie danych do atrybutu normal
}

const std::string& Mesh::getName() {
	return name;
}
