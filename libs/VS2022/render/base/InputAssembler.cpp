#include "InputAssembler.h"

ll::InputAssembler::InputAssembler()
    :ll::Object(ObjectType::INPUT_ASSEMBLER)
{
}

ll::InputAssembler::~InputAssembler()
{
}

void ll::InputAssembler::Initialize(const InputAssemblerInfo& info)
{
}

void ll::InputAssembler::Destroy()
{
}

uint32_t ll::InputAssembler::ComputeAttributesHash() const
{
    return 0;
}
