#include "OGL_Entity.h"

using namespace OGL;

OGL_Entity::OGL_Entity()
	: mEntityHandle(mRegistry.create())
{
	Init();
}

OGL_Entity::OGL_Entity(entt::entity handle)
	: mEntityHandle(handle)
{

}

OGL_Entity::OGL_Entity(const OGL_Entity& other)
	: OGL_Entity()
{
}

OGL_UUID OGL_Entity::GetUUID()
{
	return GetComponent<OGL_IDComponent>().mID;
}

const std::string& OGL_Entity::GetName()
{
	return GetComponent<OGL_TagComponent>().mTag;
}
