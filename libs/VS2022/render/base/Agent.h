#pragma once

namespace ll
{

template <typename Actor>
class Agent : public Actor
{
public:
    Agent() noexcept = delete;

    explicit Agent(Actor* const actor) noexcept
        : Actor(), _actor(actor) {}

    ~Agent() override = default;

    Agent(Agent const&) = delete;

    Agent(Agent&&) = delete;

    Agent& operator=(Agent const&) = delete;

    Agent& operator=(Agent&&) = delete;

    inline Actor* GetActor() const noexcept { return _actor; }

protected:
    Actor* _actor{ nullptr };
};

}