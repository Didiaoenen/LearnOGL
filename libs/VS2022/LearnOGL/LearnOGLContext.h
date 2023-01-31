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

		void ExecuteCommand(LearnOGLCommand* command, bool clearBack = true);
		void DrawRenderers();
		void DrawSkybox(LearnOGLCamera* camera);

		void AddRenderer(LearnOGLModel* renderer);

	public:
	
	private:
		std::vector<LearnOGLModel*> mRenderers;

	};
}