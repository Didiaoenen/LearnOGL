#pragma once

namespace OGL
{
class ISubPass
{
public:
	virtual ~ISubPass() = default;

	virtual void BeginSubPass() = 0;
	virtual void EndSubPass() = 0;
};
}