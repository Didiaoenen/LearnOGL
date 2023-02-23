#pragma once

namespace ll
{

class Camera;
class RenderPipeline;

void ValidPunctualLightsCulling(const RenderPipeline* pipeline, const Camera* camera);
void SceneCulling(const RenderPipeline* pipeline, Camera*);

}