#pragma once

#include "LearnOGLModel.h"
#include "LearnOGLCamera.h"
#include "LearnOGLCommand.h"

#include <vector>

namespace OGL
{
	class LearnOGLContext
	{
	public:
		LearnOGLContext();
		~LearnOGLContext();

		void ExecuteCommand(LearnOGLCommand* command);
		void DrawRenderers();
		void DrawSkybox(LearnOGLCamera* camera);

		void AddRenderer(LearnOGLModel* renderer);

	public:
	
	private:
		std::vector<LearnOGLModel*> mRenderers;

	};
}