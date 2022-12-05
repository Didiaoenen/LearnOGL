#include "LearnOGLApp.h"

#include <iostream>
#include <functional>

namespace OGL
{
	LearnOGLApp* LearnOGLApp::oglApp = nullptr;
	
	LearnOGLApp::LearnOGLApp()
	{
		info.title = "Default Window";
		info.majorVersion = 3;
		info.minorVersion = 3;
		info.windowWidth = 1280;
		info.windowHeight = 720;
	}

	LearnOGLApp::~LearnOGLApp()
	{
	}

	bool LearnOGLApp::Init()
	{
		return true;
	}

	void LearnOGLApp::Setup()
	{
	}

	void LearnOGLApp::Render(double dt)
	{
	}

	void LearnOGLApp::ShutDown()
	{
	}

	void LearnOGLApp::Run(LearnOGLApp* app)
	{
		oglApp = app;

		if (!WindowHint())
		{
			std::cout << "Faild to create GLFW window" << std::endl;
			return;
		}

		if (!InitGLAD())
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return;
		}

		Setup();

		bool running = true;

		do
		{
			Render(glfwGetTime());

			glfwSwapBuffers(window);
			glfwPollEvents();

		} while (running);

		ShutDown();

		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void LearnOGLApp::WindowSizeCallback(GLFWwindow* window, int width, int height)
	{
	}

	void LearnOGLApp::GLFWWindowSizeCallback(GLFWwindow* window, int width, int height)
	{
		if (oglApp)
		{
			oglApp->WindowSizeCallback(window, width, height);
		}
	}

	bool LearnOGLApp::InitGLAD()
	{
		return gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	}

	bool LearnOGLApp::WindowHint()
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, info.majorVersion);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, info.minorVersion);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		window = glfwCreateWindow(info.windowWidth, info.windowHeight, info.title.c_str(), nullptr, nullptr);
		if (!window)
		{
			return false;
		}
		glfwMakeContextCurrent(window);

		glfwSetWindowSizeCallback(window, LearnOGLApp::GLFWWindowSizeCallback);
		
		return true;
	}
}