#pragma once

#include <string>
#include <vector>
#include <memory>

namespace ll
{

class Texture;

class FrameGraph
{
public:
//    using ResourceHandleBlackboard = Blackboard<StringHandle, Handle::IndexType, Handle::UNINITIALIZED>;
//
//    FrameGraph() = default;
//    ~FrameGraph() = default;
//    FrameGraph(const FrameGraph&) = delete;
//    FrameGraph(FrameGraph&&) noexcept = delete;
//    FrameGraph& operator=(const FrameGraph&) = delete;
//    FrameGraph& operator=(FrameGraph&&) noexcept = delete;
//
//    static StringHandle StringToHandle(const char* name);
//    static const char* HandleToString(const StringHandle& handle) noexcept;
//
//    void Present(const TextureHandle& input, Texture* target, bool useMoveSemantic = true);
//    void PresentLastVersion(const VirtualResource* virtualResource, Texture* target, bool useMoveSemantic = true);
//    void PresentFromBlackboard(const StringHandle& inputName, Texture* target, bool useMoveSemantic = true);
//    void Compile();
//    void Execute() noexcept;
//    void Reset() noexcept;
//    static void GC(uint32_t unusedFrameCount = 30) noexcept;
//
//    template <typename Data, typename SetupMethod, typename ExecuteMethod>
//    const CallbackPass<Data, ExecuteMethod>& AddPass(PassInsertPoint insertPoint, const StringHandle& name, SetupMethod setup, ExecuteMethod&& execute) noexcept;
//
//    template <typename DescriptorType, typename ResourceType = typename ResourceTypeLookupTable<DescriptorType>::Resource>
//    TypedHandle<ResourceType> Create(const StringHandle& name, const DescriptorType& desc) noexcept;
//    template <typename ResourceType>
//    TypedHandle<ResourceType> ImportExternal(const StringHandle& name, ResourceType& resource) noexcept;
//    void Move(TextureHandle from, TextureHandle to, uint8_t mipmapLevel, uint8_t faceId, uint8_t arrayPosition) noexcept;
//
//    inline ResourceNode& GetResourceNode(const Handle handle) noexcept { return _resourceNodes[handle]; }
//    inline const ResourceNode& GetResourceNode(const Handle handle) const noexcept { return _resourceNodes[handle]; }
//    inline ResourceHandleBlackboard& GetBlackboard() noexcept { return _blackboard; }
//
//    void ExportGraphViz(const std::string& path);
//    inline void EnableMerge(bool enable) noexcept;
//    bool HasPass(StringHandle handle);
//
//private:
//    Handle Create(VirtualResource* virtualResource);
//    PassNode& CreatePassNode(PassInsertPoint insertPoint, const StringHandle& name, Executable* pass);
//    Handle CreateResourceNode(VirtualResource* virtualResource);
//    void Sort() noexcept;
//    void Cull();
//    void ComputeResourceLifetime();
//    void MergePassNodes() noexcept;
//    void ComputeStoreActionAndMemoryless();
//    void GenerateDevicePasses();
//    ResourceNode* GetResourceNode(const VirtualResource* virtualResource, uint8_t version) noexcept;
//
//    std::vector<std::unique_ptr<PassNode>> _passNodes{};
//    std::vector<ResourceNode> _resourceNodes{};
//    std::vector<std::unique_ptr<VirtualResource>> _virtualResources{};
//    std::vector<std::unique_ptr<DevicePass>> _devicePasses{};
//    ResourceHandleBlackboard _blackboard;
//    bool _merge{ true };
//
//    friend class PassNode;
//    friend class PassNodeBuilder;
};

}