/*
Niniejszy program jest wolnym oprogramowaniem; możesz go
rozprowadzać dalej i / lub modyfikować na warunkach Powszechnej
Licencji Publicznej GNU, wydanej przez Fundację Wolnego
Oprogramowania - według wersji 2 tej Licencji lub(według twojego
wyboru) którejś z późniejszych wersji.

Niniejszy program rozpowszechniany jest z nadzieją, iż będzie on
użyteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domyślnej
gwarancji PRZYDATNOŚCI HANDLOWEJ albo PRZYDATNOŚCI DO OKREŚLONYCH
ZASTOSOWAŃ.W celu uzyskania bliższych informacji sięgnij do
Powszechnej Licencji Publicznej GNU.

Z pewnością wraz z niniejszym programem otrzymałeś też egzemplarz
Powszechnej Licencji Publicznej GNU(GNU General Public License);
jeśli nie - napisz do Free Software Foundation, Inc., 59 Temple
Place, Fifth Floor, Boston, MA  02110 - 1301  USA
*/

#define GLM_FORCE_RADIANS
#define GLM_FORCE_SWIZZLE

#include <EngineObject.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Model.h"
#include "constants.h"
#include "lodepng.h"
#include "myCube.h"
#include "myTeapot.h"
#include "shaderprogram.h"

float speed_rot_x = 0;
float speed_rot_y = 0;
float speed_trans_x = 0;
float speed_trans_y = 0;
float aspectRatio = 1;

ShaderProgram* sp;

glm::vec4* lights;
glm::vec4* lightsColors;

// Odkomentuj, żeby rysować kostkę
// float* vertices = myCubeVertices;
// float* normals = myCubeNormals;
// float* texCoords = myCubeTexCoords;
// float* colors = myCubeColors;
// int vertexCount = myCubeVertexCount;

// Odkomentuj, żeby rysować czajnik
float* vertices = myTeapotVertices;
float* normals = myTeapotVertexNormals;
float* texCoords = myTeapotTexCoords;
float* colors = myTeapotColors;
int vertexCount = myTeapotVertexCount;

GLuint tex0;
GLuint tex1;  // uchwyt na teksturę

EngineObject engine;

GLuint readTexture(const char* filename) {
	GLuint tex;
	// Wczytanie do pamięci komputera
	std::vector<unsigned char> image;  // Alokuj wektor do wczytania obrazka
	unsigned width, height;            // Zmienne do których wczytamy wymiary obrazka
	// Wczytaj obrazek
	unsigned error = lodepng::decode(image, width, height, filename);
	// Import do pamięci karty graficznej
	glGenTextures(1, &tex);             // Zainicjuj jeden uchwyt
	glBindTexture(GL_TEXTURE_2D, tex);  // Uaktywnij uchwyt
	// Wczytaj obrazek do pamięci KG skojarzonej z uchwytem
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)image.data());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	return tex;
}

// Procedura obsługi błędów
void error_callback(int error, const char* description) {
	fputs(description, stderr);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_LEFT) speed_rot_x = -PI;
		if (key == GLFW_KEY_RIGHT) speed_rot_x = PI;
		if (key == GLFW_KEY_UP) speed_rot_y = PI;
		if (key == GLFW_KEY_DOWN) speed_rot_y = -PI;

		if (key == GLFW_KEY_W) speed_trans_x = -1;
		if (key == GLFW_KEY_S) speed_trans_x = 1;
		if (key == GLFW_KEY_A) speed_trans_y = 1;
		if (key == GLFW_KEY_D) speed_trans_y = -1;
	}
	if (action == GLFW_RELEASE) {
		if (key == GLFW_KEY_LEFT) speed_rot_x = 0;
		if (key == GLFW_KEY_RIGHT) speed_rot_x = 0;
		if (key == GLFW_KEY_UP) speed_rot_y = 0;
		if (key == GLFW_KEY_DOWN) speed_rot_y = 0;

		if (key == GLFW_KEY_W) speed_trans_x = 0;
		if (key == GLFW_KEY_S) speed_trans_x = 0;
		if (key == GLFW_KEY_A) speed_trans_y = 0;
		if (key == GLFW_KEY_D) speed_trans_y = 0;
	}
}

void windowResizeCallback(GLFWwindow* window, int width, int height) {
	if (height == 0) return;
	aspectRatio = (float)width / (float)height;
	glViewport(0, 0, width, height);
}

// Procedura inicjująca
void initOpenGLProgram(GLFWwindow* window) {
	//************Tutaj umieszczaj kod, który należy wykonać raz, na początku programu************
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);
	glfwSetWindowSizeCallback(window, windowResizeCallback);
	glfwSetKeyCallback(window, keyCallback);

	sp = new ShaderProgram("v_simplest.glsl", NULL, "f_simplest.glsl");
	// sp = new ShaderProgram("v_constant.glsl", NULL, "f_constant.glsl");

	tex0 = readTexture("metal.png");
	tex1 = readTexture("metal_spec.png");

	lights = new glm::vec4[2];
	lightsColors = new glm::vec4[2];

	lights[0] = glm::vec4(3.0f, 0.0f, -6.0f, 1.0f);
	lights[1] = glm::vec4(-3.0f, 0.0f, -6.0f, 1.0f);

	lightsColors[0] = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	lightsColors[1] = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);

	glm::mat4 V = glm::lookAt(
		glm::vec3(0, 0, -20),
		glm::vec3(0, 0, 0),
		glm::vec3(0.0f, 1.0f, 0.0f));  // Wylicz macierz widoku

	glm::mat4 P = glm::perspective(50.0f * PI / 180.0f, aspectRatio, 0.01f, 50.0f);  // Wylicz macierz rzutowania


	engine.getMesh(rod_piston_4_003)->setMatrixS(glm::translate(glm::mat4(1.f), glm::vec3(-1.298, 1.11, 0)));

	engine.getMesh(piston_1)->setMatrixS(glm::translate(glm::mat4(1.f), glm::vec3(0, -2.6, 0)));

	engine.getMesh(crank_1_bearing)->setMatrixS(glm::translate(glm::mat4(1.f), glm::vec3(0.07, 1.68, 0)));

	engine.getMesh(crank_1)->setMatrixS(
		glm::translate(glm::mat4(1.f), glm::vec3(0.07, 1.68, 0)));

	for (EngineParts name : {
		piston_1,
			rod_piston_4_003,
			cyl1_int_vlv2,
			cyl1_int_vlv1,
			cyl1_exh_vlv2,
			cyl1_vlv_exh1,
			crank_1,
			crank_1_bearing,
			head,
			block,
	}) {
		Mesh* mesh = engine.getMesh(name);
		mesh->setMatrixV(V);
		mesh->setMatrixP(P);
		mesh->setTextures(tex0, tex1);
	}

	sp->use();  // Aktywacja programu cieniującego
}

// Zwolnienie zasobów zajętych przez program
void freeOpenGLProgram(GLFWwindow* window) {
	//************Tutaj umieszczaj kod, który należy wykonać po zakończeniu pętli głównej************

	delete sp;
}

// Procedura rysująca zawartość sceny
void drawScene(GLFWwindow* window, float angle_const, float rotX, float rotY, float x, float y) {
	//************Tutaj umieszczaj kod rysujący obraz******************l
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUniform4fv(sp->u("lights"), 2, glm::value_ptr(lights[0]));
	glUniform4fv(sp->u("lightsColors"), 2, glm::value_ptr(lightsColors[0]));


	glm::mat4 M = glm::mat4(1.0f);
	M = glm::rotate(M, rotY, glm::vec3(1, 0, 0));
	M = glm::rotate(M, rotX, glm::vec3(0, 1, 0));


	glm::mat4 ALIGN = glm::mat4(1.0f);
	ALIGN = glm::rotate(ALIGN, glm::radians(-110.f), glm::vec3(0.0f, 0.0f, 1.0f));
	ALIGN = glm::translate(ALIGN, glm::vec3(1.577, 0.596, 0.f));

	glm::mat4 ROT = glm::rotate(glm::mat4(1), angle_const, glm::vec3(0.0f, 0.0f, 1.0f));

	glm::mat4 crank = glm::mat4(M * ALIGN * ROT);
	glm::mat4 crank2rod = glm::translate(glm::mat4(1), glm::vec3(1.35, 0.58, 0));


	float i = 4.01;
	float a = 1.47;

	float t = angle_const;
	float k = atan2(
		glm::sqrt(i * i - a * a * glm::sin(t) * glm::sin(t)), -a * glm::sin(t));

	glm::mat4 work = glm::rotate(glm::mat4(1.0), k, glm::vec3(0, 0, 1));

	glm::mat4 rod = glm::mat4(crank * crank2rod * glm::inverse(ROT) * work);
	glm::mat4 rod2Piston = glm::translate(glm::mat4(1.0), glm::vec3(-1.494, 3.777, 0));
	glm::mat4 pistonAngle = glm::rotate(glm::mat4(1.0), glm::radians(110.f), glm::vec3(0.0f, 0.0f, 1.0f));


	glm::mat4 piston = glm::mat4(rod * rod2Piston * glm::inverse(work) * pistonAngle);

	engine.getMesh(piston_1)->setMatrixM(piston);
	engine.getMesh(piston_1)->draw(sp);

	engine.getMesh(rod_piston_4_003)->setMatrixM(rod);
	engine.getMesh(rod_piston_4_003)->draw(sp);
	engine.getMesh(cyl1_int_vlv2)->setMatrixM(M);
	engine.getMesh(cyl1_int_vlv2)->draw(sp);
	engine.getMesh(cyl1_int_vlv1)->setMatrixM(M);
	engine.getMesh(cyl1_int_vlv1)->draw(sp);
	engine.getMesh(cyl1_exh_vlv2)->setMatrixM(M);
	engine.getMesh(cyl1_exh_vlv2)->draw(sp);
	engine.getMesh(cyl1_vlv_exh1)->setMatrixM(M);
	engine.getMesh(cyl1_vlv_exh1)->draw(sp);
	engine.getMesh(crank_1)->setMatrixM(crank);
	engine.getMesh(crank_1)->draw(sp);
	engine.getMesh(crank_1_bearing)->setMatrixM(crank);
	engine.getMesh(crank_1_bearing)->draw(sp);

	//engine.getMesh(head)->setMatrixM(M);
	//engine.getMesh(head)->draw(sp);

	engine.getMesh(block)->setMatrixM(M);
	engine.getMesh(block)->draw(sp);


	// engineModel.drawMeshByName("head", sp);
	glDisableVertexAttribArray(sp->a("texCoord0"));  // Wyłącz przesyłanie danych do atrybutu texCoord0

	glfwSwapBuffers(window);  // Przerzuć tylny bufor na przedni
}

int main(void) {
	GLFWwindow* window;  // Wskaźnik na obiekt reprezentujący okno

	glfwSetErrorCallback(error_callback);  // Zarejestruj procedurę obsługi błędów

	if (!glfwInit()) {  // Zainicjuj bibliotekę GLFW
		fprintf(stderr, "Nie można zainicjować GLFW.\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(500, 500, "OpenGL", NULL, NULL);  // Utwórz okno 500x500 o tytule "OpenGL" i kontekst OpenGL.

	if (!window)  // Jeżeli okna nie udało się utworzyć, to zamknij program
	{
		fprintf(stderr, "Nie można utworzyć okna.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);  // Od tego momentu kontekst okna staje się aktywny i polecenia OpenGL będą dotyczyć właśnie jego.
	glfwSwapInterval(1);             // Czekaj na 1 powrót plamki przed pokazaniem ukrytego bufora

	if (glewInit() != GLEW_OK) {  // Zainicjuj bibliotekę GLEW
		fprintf(stderr, "Nie można zainicjować GLEW.\n");
		exit(EXIT_FAILURE);
	}

	initOpenGLProgram(window);  // Operacje inicjujące

	// Główna pętla
	float rotX = 0;
	float rotY = 0;
	float transX = 0;
	float transY = 0;
	float angle_const = 0;
	glfwSetTime(0);                         // Zeruj timer
	while (!glfwWindowShouldClose(window))  // Tak długo jak okno nie powinno zostać zamknięte
	{
		angle_const += PI * glfwGetTime();
		rotX += speed_rot_x * glfwGetTime();
		rotY += speed_rot_y * glfwGetTime();
		transX += speed_trans_x * glfwGetTime();
		transY += speed_trans_y * glfwGetTime();

		printf("x: %lf, y: %lf, \n", transX, transY);
		glfwSetTime(0);                                              // Zeruj timer
		drawScene(window, angle_const, rotX, rotY, transX, transY);  // Wykonaj procedurę rysującą
		glfwPollEvents();                                            // Wykonaj procedury callback w zalezności od zdarzeń jakie zaszły.
	}

	freeOpenGLProgram(window);

	glfwDestroyWindow(window);  // Usuń kontekst OpenGL i okno
	glfwTerminate();            // Zwolnij zasoby zajęte przez GLFW
	exit(EXIT_SUCCESS);
}
