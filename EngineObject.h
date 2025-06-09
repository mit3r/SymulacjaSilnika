#pragma once
#include "Mesh.h"
#include <Model.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "constants.h"

enum EngineParts {
	valve_cover,
	head,
	oil_pan,
	block,
	rod_piston_4_003,
	rod_piston_4_002,
	rod_piston_4_001,
	crank_gears,
	crank_pulley,
	cyl4_exh_vlv1,
	cyl4_exh_vlv2,
	cyl4_int_vlv1,
	cyl4_int_vlv2,
	cyl1_int_vlv2,
	cyl1_int_vlv1,
	cyl1_exh_vlv2,
	cyl1_vlv_exh1,
	cyl2_exh_vlv1,
	cyl3_exh_vlv1,
	cyl3_exh_vlv2,
	cyl2_exh_vlv2,
	cyl3_int_vlv2,
	cyl2_int_vlv1,
	cyl3_int_vlv1,
	piston_2,
	piston_3,
	piston_1,
	cyl2_int_vlv2,
	crank_1_bearing,
	crank_1,
	crank_2_bearing,
	crank_2,
	crank_3,
	crank_3_bearing,
	crank_4_bearing,
	piston_4,
	rod_piston_4,
	crank_4,
	exhaust,
	intake,
	air_filter,
	Font,
	cam_int,
	cam_gears_exh,
	cam_pulley_exh,
	cam_cyl3_int2,
	cam_cyl2_int1,
	cam_cyl1_int2,
	cam_cyl1_int1,
	cam_cyl3_int1,
	cam_cyl4_int1,
	cam_cyl2_int2,
	cam_cyl4_int2,
	cam_exh,
	cam_gears_int,
	cam_pulley_int,
	cam_cyl4_exh2,
	cam_cyl3_exh2,
	cam_cyl_2_exh2,
	cam_cyl4_exh1,
	cam_cyl3_exh1,
	cam_cyl2_exh1,
	cam_cyl1_exh1,
	cam_cyl1_exh2,
};

struct Part {
	EngineParts id;
	std::string name;
	glm::mat4 S;
};

const struct Part parts[] = {
	{valve_cover, "valve_cover", glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0))},
	{head, "head", glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0))},
	{oil_pan, "oil_pan", glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0))},
	{block, "block", glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0))},
	{rod_piston_4_003, "rod_piston_4.003", glm::translate(glm::mat4(1.f), glm::vec3(-1.298, 1.11, 0))},
	{rod_piston_4_002, "rod_piston_4.002", glm::translate(glm::mat4(1.f), glm::vec3(1.293, 1.961, 0))},
	{rod_piston_4_001, "rod_piston_4.001", glm::translate(glm::mat4(1.f), glm::vec3(1.293, 1.961, 0))},
	{crank_gears, "crank_gears", glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0))},
	{crank_pulley, "crank_pulley", glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0))},
	{cyl4_exh_vlv1, "cyl4_exh_vlv1", glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0))},
	{cyl4_exh_vlv2, "cyl4_exh_vlv2", glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0))},
	{cyl4_int_vlv1, "cyl4_int_vlv1", glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0))},
	{cyl4_int_vlv2, "cyl4_int_vlv2", glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0))},
	{cyl1_int_vlv2, "cyl1_int_vlv2", glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0))},
	{cyl1_int_vlv1, "cyl1_int_vlv1", glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0))},
	{cyl1_exh_vlv2, "cyl1_exh_vlv2", glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0))},
	{cyl1_vlv_exh1, "cyl1_vlv_exh1", glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0))},
	{cyl2_exh_vlv1, "cyl2_exh_vlv1", glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0))},
	{cyl3_exh_vlv1, "cyl3_exh_vlv1", glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0))},
	{cyl3_exh_vlv2, "cyl3_exh_vlv2", glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0))},
	{cyl2_exh_vlv2, "cyl2_exh_vlv2", glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0))},
	{cyl3_int_vlv2, "cyl3_int_vlv2", glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0))},
	{cyl2_int_vlv1, "cyl2_int_vlv1", glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0))},
	{cyl3_int_vlv1, "cyl3_int_vlv1", glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0))},
	{piston_2, "piston_2", glm::translate(glm::mat4(1.f), glm::vec3(-0.013659, -1.776093, 0))},
	{piston_3, "piston_3", glm::translate(glm::mat4(1.f), glm::vec3(-0.013659, -1.776093, 0))},
	{piston_1, "piston_1", glm::translate(glm::mat4(1.f), glm::vec3(0, -2.6, 0))},
	{cyl2_int_vlv2, "cyl2_int_vlv2", glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0))},
	{crank_1_bearing, "crank_1_bearing", glm::translate(glm::mat4(1.f), glm::vec3(0.07f, 1.68f, 0.f))},
	{crank_1, "crank_1", glm::translate(glm::mat4(1.f), glm::vec3(0.07, 1.68, 0))},
	{crank_2_bearing, "crank_2_bearing", glm::translate(glm::mat4(1.f), glm::vec3(-0.023, 1.58, 0))},
	{crank_2, "crank_2", glm::translate(glm::mat4(1.f), glm::vec3(-0.023, 1.58, 0))},
	{crank_3, "crank_3", glm::translate(glm::mat4(1.f), glm::vec3(0.07f, 1.68f, 0.f))},
	{crank_3_bearing, "crank_3_bearing", glm::translate(glm::mat4(1.f), glm::vec3(0.07f, 1.68f, 0.f))},
	{crank_4_bearing, "crank_4_bearing", glm::translate(glm::mat4(1.f), glm::vec3(0.07f, 1.68f, 0.f))},
	{piston_4, "piston_4", glm::translate(glm::mat4(1.f), glm::vec3(0, -2.6, 0))},
	{rod_piston_4, "rod_piston_4", glm::translate(glm::mat4(1.f), glm::vec3(-1.298, 1.11, 0))},
	{crank_4, "crank_4", glm::translate(glm::mat4(1.f), glm::vec3(0.07f, 1.68f, 0.f))},
	{exhaust, "exhaust", glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0))},
	{intake, "intake", glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0))},
	{air_filter, "air_filter", glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0))},
	{Font, "Font", glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0))},
	{cam_int, "cam_int", glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0))},
	{cam_gears_exh, "cam_gears_exh", glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0))},
	{cam_pulley_exh, "cam_pulley_exh", glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0))},
	{cam_cyl3_int2, "cam_cyl3_int2", glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0))},
	{cam_cyl2_int1, "cam_cyl2_int1", glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0))},
	{cam_cyl1_int2, "cam_cyl1_int2", glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0))},
	{cam_cyl1_int1, "cam_cyl1_int1", glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0))},
	{cam_cyl3_int1, "cam_cyl3_int1", glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0))},
	{cam_cyl4_int1, "cam_cyl4_int1", glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0))},
	{cam_cyl2_int2, "cam_cyl2_int2", glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0))},
	{cam_cyl4_int2, "cam_cyl4_int2", glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0))},
	{cam_exh, "cam_exh", glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0))},
	{cam_gears_int, "cam_gears_int", glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0))},
	{cam_pulley_int, "cam_pulley_int", glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0))},
	{cam_cyl4_exh2, "cam_cyl4_exh2", glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0))},
	{cam_cyl3_exh2, "cam_cyl3_exh2", glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0))},
	{cam_cyl_2_exh2, "cam_cyl_2_exh2", glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0))},
	{cam_cyl4_exh1, "cam_cyl4_exh1", glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0))},
	{cam_cyl3_exh1, "cam_cyl3_exh1", glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0))},
	{cam_cyl2_exh1, "cam_cyl2_exh1", glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0))},
	{cam_cyl1_exh1, "cam_cyl1_exh1", glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0))},
	{cam_cyl1_exh2, "cam_cyl1_exh2", glm::translate(glm::mat4(1.f), glm::vec3(0, 0, 0))},
};

struct Cylinder {
	EngineParts intakeValve1;
	EngineParts intakeValve2;
	EngineParts exhaustValve1;
	EngineParts exhaustValve2;
	EngineParts piston;
	EngineParts rod;
	EngineParts crankBearing;
	EngineParts crank;
	glm::vec3 crank2Rod;
	glm::vec3 rod2Piston;
	float rodAngle;
	float pistonAngle;
};

class EngineObject
{
	const Cylinder cylinder[4] = {
		{
			cyl1_int_vlv1,
			cyl1_int_vlv2,
			cyl1_vlv_exh1,
			cyl1_exh_vlv2,
			piston_1,
			rod_piston_4_003,
			crank_1_bearing,
			crank_1,
			glm::vec3(1.35, 0.58, 0),
			glm::vec3(-1.494, 3.777, 0),
			glm::radians(-3.f),
			glm::radians(0.f),
		},
		{
			cyl2_int_vlv1,
			cyl2_int_vlv2,
			cyl2_exh_vlv1,
			cyl2_exh_vlv2,
			piston_2,
			rod_piston_4_002,
			crank_2_bearing,
			crank_2,
			glm::vec3(-1.315, -0.46, 0),
			glm::vec3(1.31, 3.708, 0),
			glm::radians(220.f),
			glm::radians(180.f),
		},
		{
			cyl3_int_vlv1,
			cyl3_int_vlv2,
			cyl3_exh_vlv1,
			cyl3_exh_vlv2,
			piston_3,
			rod_piston_4_001,
			crank_3_bearing,
			crank_3,
			glm::vec3(-1.315, -0.46, 0),
			glm::vec3(1.31, 3.708, 0),
			glm::radians(220.f),
			glm::radians(180.f)
		},
		{
			cyl4_int_vlv1,
			cyl4_int_vlv2,
			cyl4_exh_vlv1,
			cyl4_exh_vlv2,
			piston_4,
			rod_piston_4,
			crank_4_bearing,
			crank_4,
			glm::vec3(1.35, 0.58, 0),
			glm::vec3(-1.494, 3.777, 0),
			glm::radians(-3.f),
			glm::radians(0.f)
		}
	};

public:
	EngineObject();
	void setup(glm::mat4 V, glm::mat4 P);
	Mesh* getMesh(EngineParts part);

	void drawPiston(float rotation, glm::mat4 M, ShaderProgram* sp, int cylinder, float x, float y);
	void drawValves(float rotation, glm::mat4 M, ShaderProgram* sp, int cylinder);

private:
	Model model;
};

