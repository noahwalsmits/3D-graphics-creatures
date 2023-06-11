#define BOOST_TEST_MODULE modelTests
#include <boost/test/included/unit_test.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include <graphics/models/model-loader/ModelLoader.h>

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

struct OpenglFixture {
	OpenglFixture()
	{
		if (!glfwInit())
			throw "Could not initialize glwf";
		GLFWwindow* window = glfwCreateWindow(200, 100, "Unit tests", NULL, NULL);
		if (!window)
		{
			glfwTerminate();
			throw "Could not initialize glwf";
		}
		glfwMakeContextCurrent(window);

		tigl::init();
	}

	~OpenglFixture()
	{
		glfwTerminate();
	}
};

BOOST_FIXTURE_TEST_CASE(modelLoaderMissingModel, OpenglFixture)
{
	ModelLoader modelLoader = ModelLoader();
	try 
	{
		modelLoader.loadModel("does_not_exist.obj");
		BOOST_TEST(false, "loading invalid model did not throw an exception");
	}
	catch (std::exception exception)
	{
		
	}
}

//TODO load model twice and check if meshgroups are equal