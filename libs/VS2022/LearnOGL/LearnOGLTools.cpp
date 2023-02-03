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

    LearnOGLBatch LearnOGLTools::MakeQuad(GLfloat radius, bool tangent/* = false*/, bool bitangent/* = false*/)
    {
        LearnOGLBatch batch;

        batch.Begin(GL_TRIANGLES, 6);
        {
            glm::vec3 pos1(-radius,  radius, 0.0f);
            glm::vec3 pos2(-radius, -radius, 0.0f);
            glm::vec3 pos3( radius, -radius, 0.0f);
            glm::vec3 pos4( radius,  radius, 0.0f);

            glm::vec2 uv1(0.0f, 1.0f);
            glm::vec2 uv2(0.0f, 0.0f);
            glm::vec2 uv3(1.0f, 0.0f);
            glm::vec2 uv4(1.0f, 1.0f);

            glm::vec3 nm(0.0f, 0.0f, 1.0f);

            //
            glm::vec3 edge1 = pos2 - pos1;
            glm::vec3 edge2 = pos3 - pos1;
            glm::vec2 deltaUV1 = uv2 - uv1;
            glm::vec2 deltaUV2 = uv3 - uv1;

            float f1 = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

            glm::vec3 tangent1, bitangent1;

            tangent1.x = f1 * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
            tangent1.y = f1 * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
            tangent1.z = f1 * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);

            bitangent1.x = f1 * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
            bitangent1.y = f1 * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
            bitangent1.z = f1 * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);

            //
            glm::vec3 edge3 = pos3 - pos1;
            glm::vec3 edge4 = pos4 - pos1;
            glm::vec2 deltaUV3 = uv3 - uv1;
            glm::vec2 deltaUV4 = uv4 - uv1;

            float f2 = 1.0f / (deltaUV3.x * deltaUV4.y - deltaUV4.x * deltaUV3.y);

            glm::vec3 tangent2, bitangent2;

            tangent2.x = f2 * (deltaUV4.y * edge3.x - deltaUV3.y * edge4.x);
            tangent2.y = f2 * (deltaUV4.y * edge3.y - deltaUV3.y * edge4.y);
            tangent2.z = f2 * (deltaUV4.y * edge3.z - deltaUV3.y * edge4.z);

            bitangent2.x = f2 * (-deltaUV4.x * edge3.x + deltaUV3.x * edge4.x);
            bitangent2.y = f2 * (-deltaUV4.x * edge3.y + deltaUV3.x * edge4.y);
            bitangent2.z = f2 * (-deltaUV4.x * edge3.z + deltaUV3.x * edge4.z);

            batch.Vertex3fv(pos1);
            batch.Normal3fv(nm);
            batch.TexCoord2fv(uv1);
            if (tangent)
            {
                batch.Tangent3fv(tangent1);
            }
            if (bitangent)
            {
                batch.Bitangent3fv(bitangent1);
            }
            batch.Next();

            batch.Vertex3fv(pos2);
            batch.Normal3fv(nm);
            batch.TexCoord2fv(uv2);
            if (tangent)
            {
                batch.Tangent3fv(tangent1);
            }
            if (bitangent)
            {
                batch.Bitangent3fv(bitangent1);
            }
            batch.Next();

            batch.Vertex3fv(pos3);
            batch.Normal3fv(nm);
            batch.TexCoord2fv(uv3);
            if (tangent)
            {
                batch.Tangent3fv(tangent1);
            }
            if (bitangent)
            {
                batch.Bitangent3fv(bitangent1);
            }
            batch.Next();

            batch.Vertex3fv(pos1);
            batch.Normal3fv(nm);
            batch.TexCoord2fv(uv1);
            if (tangent)
            {
                batch.Tangent3fv(tangent2);
            }
            if (bitangent)
            {
                batch.Bitangent3fv(bitangent2);
            }
            batch.Next();

            batch.Vertex3fv(pos3);
            batch.Normal3fv(nm);
            batch.TexCoord2fv(uv3);
            if (tangent)
            {
                batch.Tangent3fv(tangent2);
            }
            if (bitangent)
            {
                batch.Bitangent3fv(bitangent2);
            }
            batch.Next();

            batch.Vertex3fv(pos4);
            batch.Normal3fv(nm);
            batch.TexCoord2fv(uv4);
            if (tangent)
            {
                batch.Tangent3fv(tangent2);
            }
            if (bitangent)
            {
                batch.Bitangent3fv(bitangent2);
            }
        }
        batch.End();

        return batch;
    }

    LearnOGLTriangleBatch LearnOGLTools::MakeSphere(GLfloat radius, GLint slices, GLint stacks)
    {
        LearnOGLTriangleBatch batch;

        GLfloat drho = glm::pi<GLfloat>() / (GLfloat)stacks;
        GLfloat dtheta = glm::two_pi<GLfloat>() / (GLfloat)slices;
        GLfloat ds = 1.0f / (GLfloat)slices;
        GLfloat dt = 1.0f / (GLfloat)stacks;
        GLfloat t = 1.0f;
        GLfloat s = 0.0f;

        batch.BeginMesh(slices * stacks * 6);
        for (uint32_t i = 0; i < stacks; i++)
        {
            GLfloat rho = (GLfloat)i * drho;
            GLfloat srho = (GLfloat)(sin(rho));
            GLfloat crho = (GLfloat)(cos(rho));
            GLfloat srhodrho = (GLfloat)(sin(rho + drho));
            GLfloat crhodrho = (GLfloat)(cos(rho + drho));

            s = 0.0f;
            glm::vec3 vertex[4];
            glm::vec3 normal[4];
            glm::vec2 texcoords[4];

            for (uint32_t j = 0; j < slices; j++)
            {
                GLfloat theta = (j == slices) ? 0.0f : j * dtheta;
                GLfloat stheta = (GLfloat)(-sin(theta));
                GLfloat ctheta = (GLfloat)(cos(theta));

                GLfloat x = stheta * srho;
                GLfloat y = ctheta * srho;
                GLfloat z = crho;

                texcoords[0].s = s;
                texcoords[0].t = t;
                normal[0].x = x;
                normal[0].y = y;
                normal[0].z = z;
                vertex[0].x = x * radius;
                vertex[0].y = y * radius;
                vertex[0].z = z * radius;

                x = stheta * srhodrho;
                y = ctheta * srhodrho;
                z = crhodrho;

                texcoords[1].s = s;
                texcoords[1].t = t - dt;
                normal[1].x = x;
                normal[1].y = y;
                normal[1].z = z;
                vertex[1].x = x * radius;
                vertex[1].y = y * radius;
                vertex[1].z = z * radius;


                theta = ((j + 1) == slices) ? 0.0f : (j + 1) * dtheta;
                stheta = (GLfloat)(-sin(theta));
                ctheta = (GLfloat)(cos(theta));

                x = stheta * srho;
                y = ctheta * srho;
                z = crho;

                s += ds;
                texcoords[2].s = s;
                texcoords[2].t = t;
                normal[2].x = x;
                normal[2].y = y;
                normal[2].z = z;
                vertex[2].x = x * radius;
                vertex[2].y = y * radius;
                vertex[2].z = z * radius;

                //
                x = stheta * srhodrho;
                y = ctheta * srhodrho;
                z = crhodrho;

                texcoords[3].s = s;
                texcoords[3].t = t - dt;
                normal[3].x = x;
                normal[3].y = y;
                normal[3].z = z;
                vertex[3].x = x * radius;
                vertex[3].y = y * radius;
                vertex[3].z = z * radius;

                batch.AddTriangle(vertex, normal, texcoords);

                vertex[0] = vertex[1];
                normal[0] = normal[1];
                texcoords[0] = texcoords[1];

                vertex[1] = vertex[3];
                normal[1] = normal[3];
                texcoords[1] = texcoords[3];

                batch.AddTriangle(vertex, normal, texcoords);
            }
            t -= dt;
        }
        batch.End();

        return batch;
    }

    LearnOGLTexture* LearnOGLTools::MakeRandomNoiseTex(GLuint width, GLuint height)
    {
        std::uniform_real_distribution<GLfloat> randomFloats(0.0, 1.0);
        std::default_random_engine generator;
        std::vector<glm::vec3> ssaoNoise;
        for (uint32_t i = 0; i < 16; i++)
        {
            glm::vec3 noise(randomFloats(generator) * 2.0 - 1.0, randomFloats(generator) * 2.0 - 1.0, 0.0f);
            ssaoNoise.push_back(noise);
        }
        return new LearnOGLTexture(width, height, &ssaoNoise[0]);
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