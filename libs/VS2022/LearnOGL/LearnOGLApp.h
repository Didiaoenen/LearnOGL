#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "LearnOGLDefine.h"
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
		
		virtual void WindowSizeCallback(GLFWwindow* window, int width, int height);

		void Run(LearnOGLApp* app);

		bool InitGLAD();

		bool WindowHint();

	public:

	protected:
		AppInfo info;
		CameraType mCameraType;
		PersProjInfo mPersInfo;
		OrthoProjInfo mOrthoInfo;

		static LearnOGLApp* mApp;

		LearnOGLContext* mContext;

		GLFWwindow* mWindow;

		static void GLFWWindowSizeCallback(GLFWwindow* window, int width, int height);
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