#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <graphics/camera/OrbitalCamera.h>
#include <graphics/models/model-loader/ModelLoader.h>
#include <graphics/models/model-loader/ObjParser.h>
#include <graphics/entities/Entity.h>
#include <graphics/entities/Cucumber.h>
using tigl::Vertex;

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

GLFWwindow* window;
int screenWidth, screenHeight;
double lastTime;
double lastMouseX = 0.0;
double lastMouseY = 0.0;

const Camera* camera;
std::vector<Controllable*> controllables;
std::vector<Entity*> gameEntities;
std::vector<Model*> sceneryModels;

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

	//set up rendering correctly
	glEnable(GL_DEPTH_TEST);
	tigl::shader->enableTexture(true);

	//set up fog
	glm::vec3 backgroundcolor = glm::vec3(0.3f, 0.4f, 0.6f);
	tigl::shader->enableFog(true);
	tigl::shader->setFogExp2(0.1f);
	tigl::shader->setFogColor(backgroundcolor);
	glClearColor(backgroundcolor.r, backgroundcolor.g, backgroundcolor.b, 1.0f);

	//set up lighting
	tigl::shader->enableLighting(true);
	tigl::shader->setLightCount(1);
	tigl::shader->setLightDirectional(0, true);
	tigl::shader->setLightPosition(0, glm::vec3(0.0f, 1.0f, 0.0f));

	tigl::shader->setLightAmbient(0, glm::vec3(0.3f, 0.3f, 0.3f));
	tigl::shader->setLightDiffuse(0, glm::vec3(0.6f, 0.6f, 0.6f));
	tigl::shader->setLightSpecular(0, glm::vec3(0.6f, 0.6f, 0.6f));
	
	//create scenery
	Model* floor = new Model("kitchenfloor/kitchenfloor.obj", glm::vec3(0.0f, 0.0f, 0.0f));
	floor->scale = 100.0f;
	sceneryModels.push_back(floor);

	//create entities
	Cucumber* player = new Cucumber(glm::vec3(0.0f, 0.0f, 0.0f));
	gameEntities.push_back(player);
	controllables.push_back(player);
	camera = &player->getCamera();

	//set up controllables
	//OrbitalCamera* orbitalCamera = new OrbitalCamera(glm::vec3(0.0f, 0.0f, 0.0f));
	//camera = orbitalCamera;
	//controllables.push_back(orbitalCamera);

	/*TEST CODE*/
	//tigl::shader->enableColor(true);
	sceneryModels.push_back(new Model("Egg 1/kart_YS_b.obj", glm::vec3(-1.0f, 0.0f, 0.0f)));
	sceneryModels.push_back(new Model("scarecrow/scarecrow.obj", glm::vec3(0.0f, -6.0f, 0.0f)));
	sceneryModels.push_back(new Model("Egg 1/kart_YS_b.obj", glm::vec3(1.0f, 0.0f, 0.0f)));
}


void update()
{
	double time = glfwGetTime();
	double deltaTime = time - lastTime;
	lastTime = time;

	for (Entity* entity : gameEntities)
	{
		entity->update(deltaTime);
	}

	//poll mouse position and keys
	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);
	for (Controllable* controllable : controllables)
	{
		controllable->mouseMoved(mouseX - lastMouseX, mouseY - lastMouseY);
		controllable->pollKeyboard(window);
	}
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

	for (const Model* model : sceneryModels)
	{
		model->draw(*tigl::shader);
	}
	for (const Entity* entity : gameEntities)
	{
		entity->draw(*tigl::shader);
	}
}

void exit()
{
	delete camera;

	for (const Model* model : sceneryModels)
	{
		delete model;
	}
	for (const Entity* entity : gameEntities)
	{
		delete entity;
	}
}