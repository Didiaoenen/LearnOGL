#include "LearnOGLApp.h"

#include <iostream>
#include <functional>

namespace OGL
{
	LearnOGLApp* LearnOGLApp::mApp = nullptr;
	
	LearnOGLApp::LearnOGLApp()
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

		mCamera = new LearnOGLCamera();
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

	void LearnOGLApp::Input()
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
			double time = glfwGetTime();
			mDT = time - mLastTime;
			mLastTime = time;
			
			ProcessInput(mWindow);

			Update(time);

			Render(mContext);

			glfwSwapBuffers(mWindow);
			glfwPollEvents();

			running = !glfwWindowShouldClose(mWindow);
		} while (running);

		ShutDown();

		glfwDestroyWindow(mWindow);
		glfwTerminate();
	}

	void LearnOGLApp::WindowSizeCallback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	void LearnOGLApp::MouseCallback(GLFWwindow* window, double xpos, double ypos)
	{
		if (mFirstMouse)
		{
			mLastX = xpos;
			mLastY = ypos;
			mFirstMouse = false;
		}

		double xoffset = xpos - mLastX;
		double yoffset = ypos - mLastY;

		mLastX = xpos;
		mLastY = ypos;

		mCamera->ProcessMouseMovement(xoffset, yoffset);
	}

	void LearnOGLApp::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
	{
		mCamera->ProcessMouseScroll(yoffset);
	}

	void LearnOGLApp::ProcessInput(GLFWwindow* window)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			mCamera->ProcessKeyboard(CameraMovement::Forward, mDT);
		}

		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			mCamera->ProcessKeyboard(CameraMovement::Backward, mDT);
		}

		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			mCamera->ProcessKeyboard(CameraMovement::Left, mDT);
		}

		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			mCamera->ProcessKeyboard(CameraMovement::Right, mDT);
		}

		Input();
	}

	void LearnOGLApp::GLFWWindowSizeCallback(GLFWwindow* window, int width, int height)
	{
		if (mApp)
		{
			mApp->WindowSizeCallback(window, width, height);
		}
	}

	void LearnOGLApp::GLFWWindowScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
	{
		if (mApp)
		{
			mApp->ScrollCallback(window, xoffset, yoffset);
		}
	}

	void LearnOGLApp::GLFWWindowMouseCallback(GLFWwindow* window, double xpos, double ypos)
	{
		if (mApp)
		{
			mApp->MouseCallback(window, xpos, ypos);
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
		
		glfwSetScrollCallback(mWindow, LearnOGLApp::GLFWWindowScrollCallback);
		glfwSetCursorPosCallback(mWindow, LearnOGLApp::GLFWWindowMouseCallback);

		glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		return true;
	}
}