#include "EngineObject.h"

EngineObject::EngineObject()
{
	this->model = Model("engine.obj");
}

Mesh* EngineObject::getMesh(EngineParts part)
{
	return this->model.getMeshByName(partsNames[part]);
}
