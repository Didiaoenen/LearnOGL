#include "LearnOGLTools.h"

namespace OGL
{
	LearnOGLTools* LearnOGLTools::mInstance = nullptr;

	OGL::LearnOGLTools::LearnOGLTools()
	{
	}

	OGL::LearnOGLTools::~LearnOGLTools()
	{
	}

	LearnOGLTools* OGL::LearnOGLTools::Instance()
	{
		if (!mInstance)
		{
			mInstance = new LearnOGLTools();
		}
		return mInstance;
	}

	LearnOGLBatch LearnOGLTools::MakePlane(GLfloat radius)
	{
		LearnOGLBatch batch;

		batch.Begin(GL_TRIANGLES, 6);
		{
			batch.Vertex3f(radius, 0, radius);
			batch.Normal3f(0.0f, 1.0f, 0.0f);
			batch.TexCoord2f(1.0f, 1.0f);
			batch.Next();

			batch.Vertex3f(radius, 0, -radius);
			batch.Normal3f(0.0f, 1.0f, 0.0f);
			batch.TexCoord2f(1.0f, 0.0f);
			batch.Next();

			batch.Vertex3f(-radius, 0, -radius);
			batch.Normal3f(0.0f, 1.0f, 0.0f);
			batch.TexCoord2f(0.0f, 0.0f);
			batch.Next();

			batch.Vertex3f(radius, 0, radius);
			batch.Normal3f(0.0f, 1.0f, 0.0f);
			batch.TexCoord2f(1.0f, 1.0f);
			batch.Next();

			batch.Vertex3f(-radius, 0, -radius);
			batch.Normal3f(0.0f, 1.0f, 0.0f);
			batch.TexCoord2f(0.0f, 0.0f);
			batch.Next();

			batch.Vertex3f(-radius, 0, radius);
			batch.Normal3f(0.0f, 1.0f, 0.0f);
			batch.TexCoord2f(0.0f, 1.0f);
		}
		batch.End();

		return batch;
	}

    LearnOGLBatch LearnOGLTools::MakeQuad(GLfloat radius)
    {
        LearnOGLBatch batch;

        batch.Begin(GL_TRIANGLES, 6);
        {
            batch.Vertex3f(radius, radius, 0);
            batch.Normal3f(0.0f, 1.0f, 0.0f);
            batch.TexCoord2f(1.0f, 1.0f);
            batch.Next();

            batch.Vertex3f(radius, -radius, 0);
            batch.Normal3f(0.0f, 1.0f, 0.0f);
            batch.TexCoord2f(1.0f, 0.0f);
            batch.Next();

            batch.Vertex3f(-radius, -radius, 0);
            batch.Normal3f(0.0f, 1.0f, 0.0f);
            batch.TexCoord2f(0.0f, 0.0f);
            batch.Next();

            batch.Vertex3f(radius, radius, 0);
            batch.Normal3f(0.0f, 1.0f, 0.0f);
            batch.TexCoord2f(1.0f, 1.0f);
            batch.Next();

            batch.Vertex3f(-radius, -radius, 0);
            batch.Normal3f(0.0f, 1.0f, 0.0f);
            batch.TexCoord2f(0.0f, 0.0f);
            batch.Next();

            batch.Vertex3f(-radius, radius, 0);
            batch.Normal3f(0.0f, 1.0f, 0.0f);
            batch.TexCoord2f(0.0f, 1.0f);
        }
        batch.End();

        return batch;
    }

    LearnOGLBatch LearnOGLTools::MakeCube(GLfloat radius)
    {
        LearnOGLBatch batch;

        batch.Begin(GL_TRIANGLES, 36);
        {
            // Top of cube
            batch.Vertex3f(radius, radius, radius);
            batch.Normal3f(0.0f, 1.0f, 0.0f);
            batch.TexCoord2f(1.0f, 1.0f);
            batch.Next();

            batch.Vertex3f(radius, radius, -radius);
            batch.Normal3f(0.0f, 1.0f, 0.0f);
            batch.TexCoord2f(1.0f, 0.0f);
            batch.Next();

            batch.Vertex3f(-radius, radius, -radius);
            batch.Normal3f(0.0f, 1.0f, 0.0f);
            batch.TexCoord2f(0.0f, 0.0f);
            batch.Next();

            batch.Vertex3f(radius, radius, radius);
            batch.Normal3f(0.0f, 1.0f, 0.0f);
            batch.TexCoord2f(1.0f, 1.0f);
            batch.Next();

            batch.Vertex3f(-radius, radius, -radius);
            batch.Normal3f(0.0f, 1.0f, 0.0f);
            batch.TexCoord2f(0.0f, 0.0f);
            batch.Next();

            batch.Vertex3f(-radius, radius, radius);
            batch.Normal3f(0.0f, 1.0f, 0.0f);
            batch.TexCoord2f(0.0f, 1.0f);
            batch.Next();

            // Bottom of cube
            batch.Vertex3f(-radius, -radius, -radius);
            batch.Normal3f(0.0f, -1.0f, 0.0f);
            batch.TexCoord2f(0.0f, 0.0f);
            batch.Next();

            batch.Vertex3f(radius, -radius, -radius);
            batch.Normal3f(0.0f, -1.0f, 0.0f);
            batch.TexCoord2f(1.0f, 0.0f);
            batch.Next();

            batch.Vertex3f(radius, -radius, radius);
            batch.Normal3f(0.0f, -1.0f, 0.0f);
            batch.TexCoord2f(1.0f, 1.0f);
            batch.Next();

            batch.Vertex3f(-radius, -radius, radius);
            batch.Normal3f(0.0f, -1.0f, 0.0f);
            batch.TexCoord2f(0.0f, 1.0f);
            batch.Next();

            batch.Vertex3f(-radius, -radius, -radius);
            batch.Normal3f(0.0f, -1.0f, 0.0f);
            batch.TexCoord2f(0.0f, 0.0f);
            batch.Next();

            batch.Vertex3f(radius, -radius, radius);
            batch.Normal3f(0.0f, -1.0f, 0.0f);
            batch.TexCoord2f(1.0f, 1.0f);
            batch.Next();

            // Left side of cube
            batch.Vertex3f(-radius, radius, radius);
            batch.Normal3f(-1.0f, 0.0f, 0.0f);
            batch.TexCoord2f(1.0f, 1.0f);
            batch.Next();

            batch.Vertex3f(-radius, radius, -radius);
            batch.Normal3f(-1.0f, 0.0f, 0.0f);
            batch.TexCoord2f(1.0f, 0.0f);
            batch.Next();

            batch.Vertex3f(-radius, -radius, -radius);
            batch.Normal3f(-1.0f, 0.0f, 0.0f);
            batch.TexCoord2f(0.0f, 0.0f);
            batch.Next();

            batch.Vertex3f(-radius, radius, radius);
            batch.Normal3f(-1.0f, 0.0f, 0.0f);
            batch.TexCoord2f(1.0f, 1.0f);
            batch.Next();

            batch.Vertex3f(-radius, -radius, -radius);
            batch.Normal3f(-1.0f, 0.0f, 0.0f);
            batch.TexCoord2f(0.0f, 0.0f);
            batch.Next();

            batch.Vertex3f(-radius, -radius, radius);
            batch.Normal3f(-1.0f, 0.0f, 0.0f);
            batch.TexCoord2f(0.0f, 1.0f);
            batch.Next();

            // Right side of cube
            batch.Vertex3f(radius, -radius, -radius);
            batch.Normal3f(1.0f, 0.0f, 0.0f);
            batch.TexCoord2f(0.0f, 0.0f);
            batch.Next();

            batch.Vertex3f(radius, radius, -radius);
            batch.Normal3f(1.0f, 0.0f, 0.0f);
            batch.TexCoord2f(1.0f, 0.0f);
            batch.Next();

            batch.Vertex3f(radius, radius, radius);
            batch.Normal3f(1.0f, 0.0f, 0.0f);
            batch.TexCoord2f(1.0f, 1.0f);
            batch.Next();

            batch.Vertex3f(radius, radius, radius);
            batch.Normal3f(1.0f, 0.0f, 0.0f);
            batch.TexCoord2f(1.0f, 1.0f);
            batch.Next();

            batch.Vertex3f(radius, -radius, radius);
            batch.Normal3f(1.0f, 0.0f, 0.0f);
            batch.TexCoord2f(0.0f, 1.0f);
            batch.Next();

            batch.Vertex3f(radius, -radius, -radius);
            batch.Normal3f(1.0f, 0.0f, 0.0f);
            batch.TexCoord2f(0.0f, 0.0f);
            batch.Next();

            // Front and Back
            // Front
            batch.Vertex3f(radius, -radius, radius);
            batch.Normal3f(0.0f, 0.0f, 1.0f);
            batch.TexCoord2f(1.0f, 0.0f);
            batch.Next();

            batch.Vertex3f(radius, radius, radius);
            batch.Normal3f(0.0f, 0.0f, 1.0f);
            batch.TexCoord2f(1.0f, 1.0f);
            batch.Next();

            batch.Vertex3f(-radius, radius, radius);
            batch.Normal3f(0.0f, 0.0f, 1.0f);
            batch.TexCoord2f(0.0f, 1.0f);
            batch.Next();

            batch.Vertex3f(-radius, radius, radius);
            batch.Normal3f(0.0f, 0.0f, 1.0f);
            batch.TexCoord2f(0.0f, 1.0f);
            batch.Next();

            batch.Vertex3f(-radius, -radius, radius);
            batch.Normal3f(0.0f, 0.0f, 1.0f);
            batch.TexCoord2f(0.0f, 0.0f);
            batch.Next();

            batch.Vertex3f(radius, -radius, radius);
            batch.Normal3f(0.0f, 0.0f, 1.0f);
            batch.TexCoord2f(1.0f, 0.0f);
            batch.Next();

            // Back
            batch.Vertex3f(radius, -radius, -radius);
            batch.Normal3f(0.0f, 0.0f, -1.0f);
            batch.TexCoord2f(1.0f, 0.0f);
            batch.Next();

            batch.Vertex3f(-radius, -radius, -radius);
            batch.Normal3f(0.0f, 0.0f, -1.0f);
            batch.TexCoord2f(0.0f, 0.0f);
            batch.Next();

            batch.Vertex3f(-radius, radius, -radius);
            batch.Normal3f(0.0f, 0.0f, -1.0f);
            batch.TexCoord2f(0.0f, 1.0f);
            batch.Next();

            batch.Vertex3f(-radius, radius, -radius);
            batch.Normal3f(0.0f, 0.0f, -1.0f);
            batch.TexCoord2f(0.0f, 1.0f);
            batch.Next();

            batch.Vertex3f(radius, radius, -radius);
            batch.Normal3f(0.0f, 0.0f, -1.0f);
            batch.TexCoord2f(1.0f, 1.0f);
            batch.Next();

            batch.Vertex3f(radius, -radius, -radius);
            batch.Normal3f(0.0f, 0.0f, -1.0f);
            batch.TexCoord2f(1.0f, 0.0f);
        }
        batch.End();

        return batch;
    }
}