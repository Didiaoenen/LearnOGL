#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../LearnOGL/LearnOGLApp.h"

#include <iostream>

class shadow_mapping_depth : public OGL::LearnOGLApp
{
public:
	virtual bool Init() override
	{

	}

	virtual void Setup() override
	{
		glEnable(GL_DEPTH_TEST);


	}

	virtual void Render(double dt) override
	{

	}

	virtual void ShutDown() override
	{

	}

private:

};

DECLARE_MAIN(shadow_mapping_depth)