#pragma once

#include <glm/ext.hpp>
#include <glad/glad.h>

using namespace glm;

namespace OGL
{
#ifdef ALIGN
#undef ALIGN
#endif

#define ALIGN(x, a) (((x) + ((a)-1)) & ~((a)-1))

#define MAX_LIGHTS 100

enum LightType 
{
    UNDEFINED,
    DIRECTIONAL,
    POINT,
    SPOT,
    AMBIENT,
    AREA,
};

enum class DepthTest
{
    NONE,
    LESS = GL_LESS,
    EQUAL,
    LEQUAL,
    GREATER,
    NOTEQUAL,
    GEQUAL,
    ALWAYS,
};

enum class StencilTest
{
    NONE
};

enum class CullFace 
{ 
    NONE, 
    FRONT = GL_FRONT, 
    BACK 
};

enum class DrawFlag
{ 
    NONE, 
    SHADOW, 
    DEBUG_DRAW 
};

enum class CompressedFormat : uint16_t 
{
    NONE,
    DXT1,
    DXT2,
    DXT3,
    DXT4,
    DXT5,
    DXT10,
    BC1,
    BC1A,
    BC2,
    BC3,
    BC4,
    BC5,
    BC6H,
    BC7,
    PVRTC,
    ETC,
    ASTC_4x4,
    ASTC_5x4,
    ASTC_5x5,
    ASTC_6x5,
    ASTC_6x6,
    ASTC_8x5,
    ASTC_8x6,
    ASTC_8x8,
    ASTC_10x5,
    ASTC_10x6,
    ASTC_10x8,
    ASTC_10x10,
    ASTC_12x10,
    ASTC_12x12,
    ASTC_3x3x3,
    ASTC_4x3x3,
    ASTC_4x4x3,
    ASTC_4x4x4,
    ASTC_5x4x4,
    ASTC_5x5x4,
    ASTC_5x5x5,
    ASTC_6x5x5,
    ASTC_6x6x5,
    ASTC_6x6x6,
    UNKNOWN
};

enum class PixelFormat : uint16_t 
{
    UNKNOWN,
    R8,
    RG8,
    RGB8,
    RGBA8,
    DEPTH,
};

enum class ImageDataType : uint16_t
{
    UNKNOWN,
    BYTE,
    UNSIGNED_BYTE,
};


enum class ImageDataFormat : uint16_t
{
    UNKNOWN,
    RED,
    RGB,
    RGBA
};

struct _Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
    glm::vec4 color;
	glm::vec2 texcoord;
	glm::vec3 tangent;
	glm::vec3 bitangent;
};

enum class _VertAttrib
{
    Position,
    Normal,
    Color,
    TexCoord,
    Tangent,
    Bitangent,
};

enum  class PrimitiveType : uint16_t
{
    NONE = 0,
    POINT = 1 << 0,
    LINE = 1 << 1,
    TRIANGLE = 1 << 2,
    POLYGON = 1 << 3,
};

struct Light 
{
    glm::vec4 lightPosition;                   // 16 bytes
    glm::vec4 lightDirection;                  // 16 bytes
	//LightType lightType;                      // 4 bytes
	//int lightCastShadow;                      // 4 bytes
	//int lightShadowMapIndex;                  // 4 bytes
	//float lightIntensity;                     // 4 bytes
	//glm::mat4 lightViewMatrix;               // 64 bytes
	//glm::mat4 lightProjectionMatrix;         // 64 bytes
	//glm::vec2 lightSize;                       // 8 bytes
	//glm::vec4 lightColor;                      // 16 bytes
};

using TextureHandler = intptr_t;
using TextureFormat = intptr_t;

struct PerBatchConstants
{
	glm::mat4 modelMatrix;  // 64 bytes
};

struct TextureBase
{
	TextureHandler handler = 0;
	TextureFormat format = 0;
    PixelFormat pixelFormat;

	uint32_t width = 0;
	uint32_t height = 0;
	uint32_t mips = 1;
	uint32_t samples = 1;
};

struct TextureArrayBase : virtual TextureBase
{
	uint32_t size = 0;
};

struct TextureCube : virtual TextureBase
{

};

struct TextureCubeArray : TextureCube, TextureArrayBase
{

};

struct Texture2D : virtual TextureBase
{

};

struct Texture2DArray : Texture2D, TextureArrayBase
{

};

struct LightInfo
{
    Light lights[MAX_LIGHTS];
};

struct PerFrameConstants
{
	vec4 camPos;
	mat4 viewMatrix;
	mat4 projectionMatrix;
	int32_t numLights;
	int32_t clipSpaceType;
};

struct ShadowMapConstants 
{
    int32_t light_index;          // 4 bytes
    float shadowmap_layer_index;  // 4 bytes
    float near_plane;             // 4 bytes
    float far_plane;              // 4 bytes
};

struct GlobalTexture
{
    TextureCubeArray skybox;
};

struct FrameTextures
{
	Texture2DArray shadowMap;
	Texture2DArray globalShadowMap;
	TextureCubeArray cubeShadowMap;
};

struct MaterialTexture
{
    Texture2D diffuseMap;
    Texture2D specularMap;
    Texture2D ambientMap;
    Texture2D emissiveMap;
    Texture2D normalMap;
    Texture2D maskMap;
};

const size_t kSizeLightInfo = ALIGN(sizeof(LightInfo), 256);
const size_t kSizePerFrameConstantBuffer = ALIGN(sizeof(PerFrameConstants), 256);
const size_t kSizePerBatchConstantBuffer = ALIGN(sizeof(PerBatchConstants), 256);

}
