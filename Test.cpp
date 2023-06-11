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
	std::ofstream outputFile("testresults.txt"); //clear results file
	outputFile << "1. loading missing model: ";

	ModelLoader modelLoader = ModelLoader();
	try 
	{
		modelLoader.loadModel("does_not_exist.obj");
		BOOST_TEST(false, "loading invalid model did not throw an exception");
		outputFile << "FAILED" << std::endl;
	}
	catch (std::exception exception)
	{
		outputFile << "PASSED" << std::endl;
	}
}

BOOST_FIXTURE_TEST_CASE(modelLoaderMultipleModelsOfSamePath, OpenglFixture)
{
	ModelLoader modelLoader = ModelLoader();
	std::shared_ptr<MeshGroup> group1 = modelLoader.loadModel("apple/Apple.obj");
	std::shared_ptr<MeshGroup> group2 = modelLoader.loadModel("apple/Apple.obj");
	BOOST_CHECK_EQUAL(group1, group2, "loading the same model twice did not return the same MeshGroup");

	std::shared_ptr<MeshGroup> group3 = modelLoader.loadModel("orange/Orange.obj");
	BOOST_CHECK_NE(group1, group3, "loading a different model returned the same MeshGroup");

	std::ofstream outputFile("testresults.txt", std::fstream::app);
	outputFile << "2. loading models of same path: ";
	if (group1 == group2 && group1 != group3)
	{
		outputFile << "PASSED" << std::endl;
	}
	else
	{
		outputFile << "FAILED" << std::endl;
	}
}
