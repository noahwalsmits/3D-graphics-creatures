#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <graphics/OrbitalCamera.h>
#include <graphics/models/model-loader/ModelLoader.h>
#include <graphics/models/model-loader/ObjParser.h>
using tigl::Vertex;

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

GLFWwindow* window;
Camera* camera;
int screenWidth, screenHeight;
double lastTime;
double lastMouseX = 0.0;
double lastMouseY = 0.0;

std::vector<Model> models;

void init();
void update();
void draw();
void exit();

int main(void)
{
	if (!glfwInit())
		throw "Could not initialize glwf";
	window = glfwCreateWindow(1400, 800, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		throw "Could not initialize glwf";
	}
	glfwMakeContextCurrent(window);

	tigl::init();

	init();

	while (!glfwWindowShouldClose(window))
	{
		update();
		draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	exit();
	glfwTerminate();

	return 0;
}


void init()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.3f, 0.4f, 0.6f, 1.0f);

	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			if (key == GLFW_KEY_ESCAPE)
				glfwSetWindowShouldClose(window, true);
		});

	lastTime = glfwGetTime();

	//setup mouse movement
	glfwGetWindowSize(window, &screenWidth, &screenHeight);
	lastMouseX = screenWidth / 2;
	lastMouseY = screenHeight / 2;
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	camera = new OrbitalCamera(glm::vec3(0.0f, 0.0f, 0.0f));

	/*TEST CODE*/
	//tigl::shader->enableColor(true);
	tigl::shader->enableTexture(true);
	models.push_back(Model("Egg 1/kart_YS_b.obj", glm::vec3(-1.0f, 0.0f, 0.0f)));
	models.push_back(Model("Egg 1/kart_YS_b.obj", glm::vec3(0.0f, 0.0f, 0.0f)));
	models.push_back(Model("Egg 1/kart_YS_b.obj", glm::vec3(1.0f, 0.0f, 0.0f)));
}


void update()
{
	double time = glfwGetTime();
	double deltaTime = time - lastTime;
	lastTime = time;

	camera->pollKeys(window, deltaTime);

	//poll mouse position
	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);
	camera->mouseMoved(mouseX - lastMouseX, mouseY - lastMouseY);
	lastMouseX = mouseX;
	lastMouseY = mouseY;
}

void draw()
{
	glfwGetWindowSize(window, &screenWidth, &screenHeight);
	glViewport(0, 0, screenWidth, screenHeight);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 projectionMatrix = glm::perspective(glm::radians(80.0f), screenWidth / (float)screenHeight, 0.01f, 100.0f);
	glm::mat4 viewMatrix = camera->getViewMatrix();

	tigl::shader.get()->setProjectionMatrix(projectionMatrix);
	tigl::shader.get()->setViewMatrix(viewMatrix);
	//model matrix is set by each model before drawing

	for (const Model& model : models)
	{
		model.draw(*tigl::shader);
	}
}

void exit()
{
	delete camera;
}