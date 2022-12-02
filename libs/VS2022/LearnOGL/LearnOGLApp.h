#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

namespace OGL
{
	class LearnOGLApp
	{
	public:
		LearnOGLApp();
		~LearnOGLApp();

		virtual bool Init();

		virtual void SetUp();

		virtual void Render(double dt);

		virtual void ShutDown();
		
		virtual void WindowSizeCallback(GLFWwindow* window, int width, int height);

		void Run(LearnOGLApp* app);

		void WindowHint();
	public:
		struct AppInfo
		{
			std::string title;
			int windowWidth;
			int windowHeight;
			int majorVersion;
			int minorVersion;
		};

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