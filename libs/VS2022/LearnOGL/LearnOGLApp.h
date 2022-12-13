#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

namespace OGL
{
	struct PersProjInfo
	{
		float fov;
		float width;
		float height;
		float zNear;
		float zFar;
	};

	struct OrthoProjInfo
	{
		float right;
		float left;
		float bottom;
		float top;
		float zNear;
		float zFar;
	};

	struct AppInfo
	{
		std::string title;
		int windowWidth;
		int windowHeight;
		int majorVersion;
		int minorVersion;
	};

	class LearnOGLApp
	{
	public:
		LearnOGLApp();
		virtual ~LearnOGLApp();

		virtual bool Init();

		virtual void Setup();

		virtual void Render(double dt);

		virtual void ShutDown();
		
		virtual void WindowSizeCallback(GLFWwindow* window, int width, int height);

		void Run(LearnOGLApp* app);

		bool InitGLAD();

		bool WindowHint();

	public:

	protected:
		AppInfo info;

		static LearnOGLApp* oglApp;

		GLFWwindow* window;

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