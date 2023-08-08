#include "OGL_Application.h"

using namespace OGL;
using namespace std;

OGL_Application* OGL_Application::mApp = nullptr;

bool OGL_Application::Initialize()
{
	info.title = "Default Window";
	info.majorVersion = 4;
	info.minorVersion = 3;
	info.windowWidth = 960;
	info.windowHeight = 720;

	mSceneManager = new SceneManager();
	
	//
	mGraphicManager = new OpenGLGraphicsManager();
	mPipelineStateManager = new OpenGLPipelineStateManager();
	RegisterRuntimeModule(mGraphicManager);
	RegisterRuntimeModule(mPipelineStateManager);

    return true;
}

void OGL_Application::Finalize()
{
}

void OGL_Application::Setup()
{
	mApp = this;

	//
	mSceneManager->LoadScene("../../../resources/objects/ttest.blend");
}

void OGL_Application::Update(double dt)
{
	//BaseApplication::Tick();
}

void OGL_Application::Input()
{
}

void OGL_Application::Run()
{
	if (!WindowHint())
	{
		cout << "Faild to create GLFW window" << endl;
		return;
	}

	if (!InitGLAD())
	{
		cout << "Failed to initialize GLAD" << endl;
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

		glfwSwapBuffers(mWindow);
		glfwPollEvents();

		running = !glfwWindowShouldClose(mWindow);
	} while (running);

	Finalize();

	glfwDestroyWindow(mWindow);
	glfwTerminate();
}

void OGL_Application::WindowSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void OGL_Application::MouseCallback(GLFWwindow* window, double xpos, double ypos)
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

	//mCamera->ProcessMouseMovement(xoffset, yoffset);
}

void OGL_Application::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	//mCamera->ProcessMouseScroll(yoffset);
}

void* OGL_Application::GetMainWindowHandler()
{
	return mWindow;
}

void OGL_Application::ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		//mCamera->ProcessKeyboard(CameraMovement::Forward, mDT);
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		//mCamera->ProcessKeyboard(CameraMovement::Backward, mDT);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		//mCamera->ProcessKeyboard(CameraMovement::Left, mDT);
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		//mCamera->ProcessKeyboard(CameraMovement::Right, mDT);
	}

	Input();
}

void OGL_Application::GLFWWindowSizeCallback(GLFWwindow* window, int width, int height)
{
	if (mApp)
	{
		mApp->WindowSizeCallback(window, width, height);
	}
}

void OGL_Application::GLFWWindowScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (mApp)
	{
		mApp->ScrollCallback(window, xoffset, yoffset);
	}
}

void OGL_Application::GLFWWindowMouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	if (mApp)
	{
		mApp->MouseCallback(window, xpos, ypos);
	}
}

bool OGL_Application::InitGLAD()
{
	return gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

bool OGL_Application::WindowHint()
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

	glfwSetWindowSizeCallback(mWindow, OGL_Application::GLFWWindowSizeCallback);

	glfwSetScrollCallback(mWindow, OGL_Application::GLFWWindowScrollCallback);
	glfwSetCursorPosCallback(mWindow, OGL_Application::GLFWWindowMouseCallback);

	glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	return true;
}