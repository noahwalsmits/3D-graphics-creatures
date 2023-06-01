#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>
#include <graphics/model-loader/ModelLoader.h>
using tigl::Vertex;

#include <iostream>
#include <graphics/OrbitalCamera.h>

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

GLFWwindow* window;
Camera* camera;
int screenWidth, screenHeight;
double lastTime;
double lastMouseX = 0.0;
double lastMouseY = 0.0;

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

    camera = new OrbitalCamera(glm::vec3(0.0f, 0.0f, 0.0f));

    int i = 10;
    int* iptr = &i;
    //std::shared_ptr<int> smart_ptr(iptr); //crashes because the original value is deleted
    std::shared_ptr<int> smart_ptr = std::make_shared<int>(10);
    std::shared_ptr<int> smart_ptr2 = smart_ptr;
    std::cout << "value: " << *smart_ptr.get() << ", uses: " << smart_ptr.use_count() << std::endl;
    std::cout << "value: " << *smart_ptr2.get() << ", uses: " << smart_ptr2.use_count() << std::endl;
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
    glClearColor(0.3f, 0.4f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 projectionMatrix = glm::perspective(glm::radians(80.0f), screenWidth / (float)screenHeight, 0.01f, 100.0f);
    glm::mat4 viewMatrix = camera->getViewMatrix();
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

    tigl::shader.get()->setProjectionMatrix(projectionMatrix);
    tigl::shader.get()->setViewMatrix(viewMatrix);
    tigl::shader.get()->setModelMatrix(modelMatrix);

    tigl::begin(GL_TRIANGLES);
    tigl::addVertex(tigl::Vertex::PC(glm::vec3(-1, 0, 0), glm::vec4(1, 0, 0, 1)));
    tigl::addVertex(tigl::Vertex::PC(glm::vec3(1, 0, 0), glm::vec4(0, 1, 0, 1)));
    tigl::addVertex(tigl::Vertex::PC(glm::vec3(0, 1, 0), glm::vec4(0, 0, 1, 1)));
    tigl::end();
}

void exit()
{
    delete camera;
}