#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "LearnOGLDefine.h"
#include "LearnOGLCamera.h"
#include "LearnOGLContext.h"

#include <string>

namespace OGL
{
	class LearnOGLApp
	{
	public:
		LearnOGLApp();
		virtual ~LearnOGLApp();

		virtual bool Init();

		virtual void Setup();

		virtual void Update(double dt);

		virtual void Render(LearnOGLContext* context);

		virtual void ShutDown();
		
		virtual void Input();

		virtual void WindowSizeCallback(GLFWwindow* window, int width, int height);
		virtual void MouseCallback(GLFWwindow* window, double xpos, double ypos);
		virtual void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

		void Run(LearnOGLApp* app);

		bool InitGLAD();

		bool WindowHint();

		void ProcessInput(GLFWwindow* window);

	public:

	protected:
		AppInfo info{};
		CameraType mCameraType{};
		PersProjInfo mPersInfo{};
		OrthoProjInfo mOrthoInfo{};

		static LearnOGLApp* mApp;

		LearnOGLCamera* mCamera{ nullptr };

		LearnOGLContext* mContext{ nullptr };

		GLFWwindow* mWindow{ nullptr };

		double mDT = 0;
		double mLastTime = 0;

		static void GLFWWindowSizeCallback(GLFWwindow* window, int width, int height);

		static void GLFWWindowMouseCallback(GLFWwindow* window, double xpos, double ypos);
		static void GLFWWindowScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

	private:
		bool mFirstMouse = true;
		double mLastX = 0;
		double mLastY = 0;

	};
}

#define DECLARE_MAIN(App)			\
int main() {						\
	App* app = new App();			\
	if (app->Init()) {				\
		app->Run(app);				\
	}								\
	return 0;						\
}