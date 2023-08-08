#include "OpenGLPipelineStateCommonBaseManager.h"

#include <string>
#include <vector>
#include <iostream>

#include "CBuffer.h"
#include "AssetLoader.h"

using namespace OGL;
using namespace std;

static void OutputShaderErrorMessage(unsigned int shaderId, const char* shaderFilename) 
{
    int logSize;
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logSize);

    logSize++;

    char* infoLog = new char[logSize];
    if (!infoLog) 
    {
        return;
    }

    glGetShaderInfoLog(shaderId, logSize, NULL, infoLog);


    for (int i = 0; i < logSize; i++) 
    {
        cerr << infoLog[i];
    }

    cerr << "Error compiling shader." << shaderFilename << endl;

    return;
}

static void OutputLinkerErrorMessage(unsigned int programId) 
{
    int logSize;
    glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &logSize);

    logSize++;

    char* infoLog = new char[logSize];
    glGetProgramInfoLog(programId, logSize, nullptr, infoLog);


    for (int i = 0; i < logSize; i++) 
    {
        cerr << infoLog[i];
    }

    cerr << "Error compiling linker." << endl;
}

static bool LoadShaderFromFile(const char* filename, const GLenum shaderType, GLuint& shader) 
{
    string cbufferShaderBuffer;
    string commonShaderBuffer;
    string shaderBuffer;
    int status;

    AssetLoader assetLoader;
    shaderBuffer = assetLoader.SyncOpenAndReadTextFileToString(filename);
    if (shaderBuffer.empty()) 
    {
        return false;
    }

    shaderBuffer = cbufferShaderBuffer + commonShaderBuffer + shaderBuffer;

    shader = glCreateShader(shaderType);

    const char* str = shaderBuffer.c_str();
    glShaderSource(shader, 1, &str, nullptr);

    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status != 1) 
    {
        OutputShaderErrorMessage(shader, filename);
        return false;
    }

    return true;
}

static bool LoadShaderProgram(const vector<pair<GLenum, string>>& source, GLuint& shaderProgram)
{
    int status;

    shaderProgram = glCreateProgram();

    for (auto it = source.cbegin(); it != source.cend(); it++) 
    {
        if (!it->second.empty())
        {
            GLuint shader;
            status = LoadShaderFromFile((SHADER_ROOT + it->second + SHADER_SUFFIX).c_str(), it->first, shader);
            if (!status) 
            {
                return false;
            }

            glAttachShader(shaderProgram, shader);
            glDeleteShader(shader);
        }
    }

    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
    if (status != 1) 
    {
        OutputLinkerErrorMessage(shaderProgram);
        return false;
    }

    return true;
}

bool OpenGLPipelineStateCommonBaseManager::InitializePipelineState(PipelineState** pipelineState)
{
    bool result;
    OpenGLPipelineState* pipeState = new OpenGLPipelineState(**pipelineState);

    vector<pair<GLenum, string>> list;

    if (!(*pipelineState)->vertexShaderName.empty()) 
    {
        list.emplace_back(GL_VERTEX_SHADER, (*pipelineState)->vertexShaderName);
    }

    if (!(*pipelineState)->fragmentShaderName.empty())
    {
        list.emplace_back(GL_FRAGMENT_SHADER, (*pipelineState)->fragmentShaderName);
    }

    if (!(*pipelineState)->geometryShaderName.empty())
    {
        list.emplace_back(GL_GEOMETRY_SHADER, (*pipelineState)->geometryShaderName);
    }

    result = LoadShaderProgram(list, pipeState->shaderProgram);

    *pipelineState = pipeState;

    return result;
}

void OpenGLPipelineStateCommonBaseManager::DestroyPipelineState(PipelineState& pipelineState)
{
}