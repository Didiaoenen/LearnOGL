#pragma once

#include <string>

namespace ll
{

	class Root;

class Director
{
public:
	double GetDeltaTime();
	double GetTotalTime();
	double GetCurrentTime();
	uint32_t GetToaltFrames();

	void GetSystem();
	inline Root* GetRoot() { return _root; }

	void Tick(double dt);

	void Init();

private:
	Root* _root;
	uint32_t _totalFrames;

};

}