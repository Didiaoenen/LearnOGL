#include "LearnOGLTriangleBatch.h"

namespace OGL
{
    LearnOGLTriangleBatch::LearnOGLTriangleBatch()
    {
    }

    LearnOGLTriangleBatch::~LearnOGLTriangleBatch()
    {
    }

    void LearnOGLTriangleBatch::BeginMesh(GLuint indexes)
	{
        mMaxIndexes = indexes;

        mIndexes = new GLushort[mMaxIndexes];
        mVerts = new glm::vec3[mMaxIndexes];
        mNorms = new glm::vec3[mMaxIndexes];
        mTexCoords = new glm::vec2[mMaxIndexes];
	}

    void LearnOGLTriangleBatch::AddTriangle(glm::vec3 verts[], glm::vec3 norms[], glm::vec2 texcoords[])
    {
        const  float e = 0.00001f;

        glm::normalize(norms[0]);
        glm::normalize(norms[1]);
        glm::normalize(norms[2]);

        for (GLuint iVertex = 0; iVertex < 3; iVertex++)
        {
            GLuint iMatch = 0;
            for (iMatch = 0; iMatch < mNumVerts; iMatch++)
            {
                if (VecCloseEnough(mVerts[iMatch].x, verts[iVertex].x, e) &&
                    VecCloseEnough(mVerts[iMatch].y, verts[iVertex].y, e) &&
                    VecCloseEnough(mVerts[iMatch].z, verts[iVertex].z, e) &&

                    VecCloseEnough(mNorms[iMatch].x, norms[iVertex].x, e) &&
                    VecCloseEnough(mNorms[iMatch].y, norms[iVertex].y, e) &&
                    VecCloseEnough(mNorms[iMatch].z, norms[iVertex].z, e) &&

                    VecCloseEnough(mTexCoords[iMatch].s, texcoords[iVertex].s, e) &&
                    VecCloseEnough(mTexCoords[iMatch].t, texcoords[iVertex].t, e))
                {
                    mIndexes[mNumIndexes] = iMatch;
                    mNumIndexes++;
                    break;
                }
            }

            if (iMatch == mNumVerts && mNumVerts < mMaxIndexes && mNumIndexes < mMaxIndexes)
            {
                mVerts[mNumVerts] = verts[iVertex];
                mNorms[mNumVerts] = norms[iVertex];
                mTexCoords[mNumVerts] = texcoords[iVertex];

                mIndexes[mNumIndexes] = mNumVerts;
                mNumIndexes++;
                mNumVerts++;
            }
        }
    }

    void LearnOGLTriangleBatch::End()
    {
        glGenVertexArrays(1, &mVAO);
        glBindVertexArray(mVAO);

        glGenBuffers(4, mVBO);

        glBindBuffer(GL_ARRAY_BUFFER, mVBO[VERTEX_DATA]);
        glEnableVertexAttribArray((GLuint)VertAttrib::Position);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * mNumVerts * 3, mVerts, GL_STATIC_DRAW);
        glVertexAttribPointer((GLuint)VertAttrib::Position, 3, GL_FLOAT, GL_FALSE, 0, 0);

        glBindBuffer(GL_ARRAY_BUFFER, mVBO[NORMAL_DATA]);
        glEnableVertexAttribArray((GLuint)VertAttrib::Normal);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * mNumVerts * 3, mNorms, GL_STATIC_DRAW);
        glVertexAttribPointer((GLuint)VertAttrib::Normal, 3, GL_FLOAT, GL_FALSE, 0, 0);

        glBindBuffer(GL_ARRAY_BUFFER, mVBO[TEXTURE_DATA]);
        glEnableVertexAttribArray((GLuint)VertAttrib::TexCoord);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * mNumVerts * 2, mTexCoords, GL_STATIC_DRAW);
        glVertexAttribPointer((GLuint)VertAttrib::TexCoord, 2, GL_FLOAT, GL_FALSE, 0, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVBO[INDEX_DATA]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * mNumIndexes, mIndexes, GL_STATIC_DRAW);

        glBindVertexArray(0);

        mBatchDone = true;
    }

    void LearnOGLTriangleBatch::Draw()
    {
        if (!mBatchDone)
        {
            return;
        }

        mMaterial->Draw();

        glBindVertexArray(mVAO);
        glDrawElements(GL_TRIANGLES, mNumIndexes, GL_UNSIGNED_SHORT, 0);
        glBindVertexArray(0);
    }

}
