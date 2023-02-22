#pragma once

#include "Object.h"

namespace ll
{

class DescriptorSetLayout : public Object
{
public:
	DescriptorSetLayout();
	~DescriptorSetLayout() override;

protected:
	virtual void DoInit(const DescriptorSetLayoutInfo& info) = 0;
	virtual void DoDestroy() = 0;
};

}