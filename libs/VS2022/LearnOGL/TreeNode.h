#pragma once

#include <list>
#include <memory>

namespace OGL
{
class TreeNode
{
public:
	virtual ~TreeNode() = default;
	virtual void AppendChild(std::shared_ptr<TreeNode>&& subNode) 
	{
		subNode->mParent = this;
		mChildren.push_back(std::move(subNode));
	}

protected:
	TreeNode* mParent{ nullptr };
	std::list<std::shared_ptr<TreeNode>> mChildren;
};
}