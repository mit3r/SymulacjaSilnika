#include "EngineObject.h"

EngineObject::EngineObject()
{
	this->model = Model("engine.obj");
}

void EngineObject::setup(glm::mat4 V, glm::mat4 P)
{
	for (Part p : parts) {
		this->getMesh(p.id)->setMatrixV(V);
		this->getMesh(p.id)->setMatrixP(P);
	}

	for (int i = 0; i < 4; i++) {
		auto c = this->cylinder[i];

		this->getMesh(c.crank)->setMatrixS(parts[c.crank].S);
		this->getMesh(c.crankBearing)->setMatrixS(parts[c.crankBearing].S);

		this->getMesh(c.rod)->setMatrixS(parts[c.rod].S);
		this->getMesh(c.piston)->setMatrixS(parts[c.piston].S);

		this->getMesh(c.intakeValve1)->setMatrixS(parts[c.intakeValve1].S);
		this->getMesh(c.intakeValve2)->setMatrixS(parts[c.intakeValve2].S);
		this->getMesh(c.exhaustValve1)->setMatrixS(parts[c.exhaustValve1].S);
		this->getMesh(c.exhaustValve2)->setMatrixS(parts[c.exhaustValve2].S);
	}
}

Mesh* EngineObject::getMesh(EngineParts partId)
{
	return this->model.getMeshByName(parts[partId].name);
}

void EngineObject::drawPiston(float t, glm::mat4 M, ShaderProgram* sp, int index, float x, float y)
{
	auto cyl = this->cylinder[index];


	// Wa³ korbowy
	glm::mat4 ROT = glm::rotate(glm::mat4(1), t, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 crank = glm::mat4(M * ROT);
	//glm::mat4 crank = glm::mat4(M);

	// Korbowód
	//float i = 4.01;
	//float a = 1.47;

	float i = 3.933;
	float a = 1.393;

	float k = atan2(
		glm::sqrt(i * i - a * a * glm::sin(t) * glm::sin(t)), -a * glm::sin(t));
	glm::mat4 crank2rod = glm::translate(glm::mat4(1), cyl.crank2Rod);
	//glm::mat4 crank2rod = glm::translate(glm::mat4(1), glm::vec3(x, y, 0)); // TESTING
	glm::mat4 work = glm::rotate(glm::mat4(1.0), k + cyl.rodAngle, glm::vec3(0, 0, 1));

	glm::mat4 rod = glm::mat4(crank * crank2rod * glm::inverse(ROT) * work);
	//glm::mat4 rod = glm::mat4(crank * crank2rod * work); // TESTING


	// T³ok
	//glm::mat4 rod2Piston = glm::translate(glm::mat4(1), glm::vec3(x, y, 0)); // TESTING
	glm::mat4 rod2Piston = glm::translate(glm::mat4(1.0), cyl.rod2Piston);
	glm::mat4 pistonAngle = glm::rotate(glm::mat4(1.0), glm::radians(110.f) + cyl.pistonAngle, glm::vec3(0.0f, 0.0f, 1.0f));

	//glm::mat4 piston = glm::mat4(M * ROT);
	//getMesh(cyl.piston)->setMatrixS(glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0))); // TESTING
	glm::mat4 piston = glm::mat4(rod * rod2Piston * glm::inverse(work) * pistonAngle);

	Mesh* mesh;

	mesh = getMesh(this->cylinder[index].crankBearing);
	mesh->setMatrixM(crank);
	mesh->draw(sp);

	mesh = getMesh(this->cylinder[index].crank);
	mesh->setMatrixM(crank);
	mesh->draw(sp);

	mesh = getMesh(this->cylinder[index].piston);
	mesh->setMatrixM(piston);
	mesh->draw(sp);

	mesh = getMesh(this->cylinder[index].rod);
	mesh->setMatrixM(rod);
	mesh->draw(sp);


}

void EngineObject::drawValves(float rotation, glm::mat4 M, ShaderProgram* sp, int cylinder)
{
	glm::mat4 M_vi1 = glm::mat4(M);
	glm::mat4 M_vi2 = glm::mat4(M);
	glm::mat4 M_ve1 = glm::mat4(M);
	glm::mat4 M_ve2 = glm::mat4(M);

	Mesh* mesh = getMesh(this->cylinder[cylinder].intakeValve1);
	mesh->setMatrixM(M_vi1);
	mesh->draw(sp);

	mesh = getMesh(this->cylinder[cylinder].intakeValve2);
	mesh->setMatrixM(M_vi2);
	mesh->draw(sp);

	mesh = getMesh(this->cylinder[cylinder].exhaustValve1);
	mesh->setMatrixM(M_ve1);
	mesh->draw(sp);

	mesh = getMesh(this->cylinder[cylinder].exhaustValve2);
	mesh->setMatrixM(M_ve2);
	mesh->draw(sp);
}
