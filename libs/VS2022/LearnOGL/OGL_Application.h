#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>
#include <functional>

#include "BaseApplication.h"
#include "OpenGLGraphicsManager.h"
#include "OpenGLPipelineStateManager.h"
#include "SceneManager.h"

#include "LearnOGLDefine.h"

namespace OGL
{
class OGL_Application : public BaseApplication
{
public:
	OGL_Application() = default;
	virtual ~OGL_Application() override = default;

	virtual bool Initialize();
	virtual void Finalize();
		
	virtual void Setup();

	virtual void Update(double dt);

	virtual void Input();

	virtual void WindowSizeCallback(GLFWwindow* window, int width, int height);
	virtual void MouseCallback(GLFWwindow* window, double xpos, double ypos);
	virtual void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

	virtual void* GetMainWindowHandler() override;

	void Run();

	bool InitGLAD();

	bool WindowHint();

	void ProcessInput(GLFWwindow* window);

protected:
	AppInfo info{};

	static OGL_Application* mApp;

	GLFWwindow* mWindow{ nullptr };

	double mDT{ 0 };
	double mLastTime{ 0 };

	static void GLFWWindowSizeCallback(GLFWwindow* window, int width, int height);

	static void GLFWWindowMouseCallback(GLFWwindow* window, double xpos, double ypos);
	static void GLFWWindowScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

private:
	bool mFirstMouse{ true };
	double mLastX{ 0 };
	double mLastY{ 0 };

	GraphicsManager* mGraphicManager;
	PipelineStateManager* mPipelineStateManager;
	SceneManager* mSceneManager;
};

#define DECLARE_MAIN(App)			\
int main()							\
{									\
	App* app = new App();			\
	if (app->Initialize())			\
	{								\
		app->Run();					\
	}								\
	return 0;						\
}
}