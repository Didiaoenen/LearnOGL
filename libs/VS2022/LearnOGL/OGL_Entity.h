#pragma once

#include <entt/entt.hpp>

#include "Scene.h"
#include "RefCounts.h"
#include "OGL_Component.h"

namespace OGL
{
class OGL_Entity : public RefCounts
{
public:
	OGL_Entity();
	OGL_Entity(entt::entity handle, Scene* scene);
	OGL_Entity(const OGL_Entity& other);
	virtual ~OGL_Entity() = default;

	template<typename T, typename... Args>
	T& AddComponent(Args&&... args)
	{
		return mScene->mRegistry.emplace<T>(mEntityHandle, std::forward<Args>(args)...);
	}

	template<typename T>
	T& GetComponent()
	{
		return mScene->mRegistry.get<T>(mEntityHandle);
	}

	template<typename T>
	bool HasComponent()
	{
		return mScene->mRegistry.any_of<T>(mEntityHandle);
	}

	template<typename T>
	void RemoveComponent()
	{
		mScene->mRegistry.remove<T>(mEntityHandle);
	}

	operator bool() const { return mEntityHandle != entt::null; }
	operator uint32_t() const { return (uint32_t)mEntityHandle; }
	operator entt::entity() const { return mEntityHandle; }

	OGL_UUID GetUUID();
	const std::string& GetName();

protected:
	bool Init()
	{
		AddComponent<OGL_IDComponent>(OGL_UUID());
		return true;
	}

public:
	Scene* mScene{ nullptr };
	entt::entity mEntityHandle{ entt::null };
};
}

