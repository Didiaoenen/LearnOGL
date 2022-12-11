
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../LearnOGL/LearnOGLApp.h"

#include <iostream>

class shadow_mapping_depth : public OGL::LearnOGLApp
{
public:
	virtual bool Init() override
	{
		return true;
	}

	virtual void Setup() override
	{
		glEnable(GL_DEPTH_TEST);
	}

	virtual void Render(double dt) override
	{
		glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	virtual void ShutDown() override
	{

	}

private:

};

DECLARE_MAIN(shadow_mapping_depth)