#include "LearnOGLApp.h"

#include <iostream>
#include <functional>

namespace OGL
{
	LearnOGLApp* LearnOGLApp::mApp = nullptr;
	
	LearnOGLApp::LearnOGLApp() :
		info(),
		mCameraType(CameraType::Perspective),
		mPersInfo(),
		mOrthoInfo(),
		mContext(nullptr),
		mWindow(nullptr)
	{
	}

	LearnOGLApp::~LearnOGLApp()
	{
	}

	bool LearnOGLApp::Init()
	{
		info.title = "Default Window";
		info.majorVersion = 3;
		info.minorVersion = 3;
		info.windowWidth = 1280;
		info.windowHeight = 720;

		mContext = new LearnOGLContext();

		return true;
	}

	void LearnOGLApp::Setup()
	{
	}

	void LearnOGLApp::Update(double dt)
	{
	}

	void LearnOGLApp::Render(LearnOGLContext* context)
	{
	}

	void LearnOGLApp::ShutDown()
	{
	}

	void LearnOGLApp::Run(LearnOGLApp* app)
	{
		mApp = app;

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
			Update(glfwGetTime());

			Render(mContext);

			glfwSwapBuffers(mWindow);
			glfwPollEvents();

		} while (running);

		ShutDown();

		glfwDestroyWindow(mWindow);
		glfwTerminate();
	}

	void LearnOGLApp::WindowSizeCallback(GLFWwindow* window, int width, int height)
	{
	}

	void LearnOGLApp::GLFWWindowSizeCallback(GLFWwindow* window, int width, int height)
	{
		if (mApp)
		{
			mApp->WindowSizeCallback(window, width, height);
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

		mWindow = glfwCreateWindow(info.windowWidth, info.windowHeight, info.title.c_str(), nullptr, nullptr);
		if (!mWindow)
		{
			return false;
		}
		glfwMakeContextCurrent(mWindow);

		glfwSetWindowSizeCallback(mWindow, LearnOGLApp::GLFWWindowSizeCallback);
		
		return true;
	}
}