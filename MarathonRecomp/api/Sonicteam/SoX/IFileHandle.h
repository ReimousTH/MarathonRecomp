#pragma once

#include <Marathon.inl>
#include <Sonicteam/SoX/RefCountObject.h>

namespace Sonicteam::SoX
{
    class IFileHandle:Sonicteam::SoX::RefCountObject
    {
    public:
        struct Vftable:RefCountObject::Vftable
        {
            be<uint32_t> Initialize;
            be<uint32_t> GetSize;
            be<uint32_t> GetBuffer;
        };

        bool Initialize()
        {
            auto vft = (Vftable*)m_pVftable.get();
            return GuestToHostFunction<bool>(vft->Initialize, this);
        }

        uint64_t GetSize()
        {
            auto vft = (Vftable*)m_pVftable.get();
            return GuestToHostFunction<uint64_t>(vft->GetSize, this);
        }

        void* GetBuffer()
        {
            auto vft = (Vftable*)m_pVftable.get();
            return GuestToHostFunction<void*>(vft->GetBuffer, this);
        }
    };
}
