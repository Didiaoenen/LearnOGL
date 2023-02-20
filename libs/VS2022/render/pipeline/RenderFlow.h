#pragma once

#include "Define.h"

namespace ll
{

    class Camera;
    class RenderStage;
    class RenderPipeline;

struct RenderFlowInfo 
{
    std::string name;
    uint32_t priority = 0;
    uint32_t tag = 0;
    RenderStageList stages;
};

class RenderFlow
{
public:
    RenderFlow();
    virtual ~RenderFlow();

    virtual bool Initialize(const RenderFlowInfo& info);
    virtual void Activate(RenderPipeline* pipeline);
    virtual void Render(Camera* camera);
    virtual void Destroy();

    inline const std::string& GetName() const { return _name; }
    inline uint32_t GetPriority() const { return _priority; }
    inline uint32_t GetTag() const { return _tag; }
    RenderStage* GetRenderstageByName(const std::string& name) const;

protected:
    RenderStageList _stages;
    std::string _name;
    RenderPipeline* _pipeline{ nullptr };
    uint32_t _priority{ 0 };
    uint32_t _tag{ 0 };
    bool _isResourceOwner{ false };
};

}