#pragma once

#include <Marathon.inl>
#include <Sonicteam/SoX/RefCountObject.h>

namespace Sonicteam::SoX
{
    class IResource : public RefCountObject
    {
    public:
        struct Vftable:RefCountObject::Vftable
        {
            MARATHON_INSERT_PADDING(4);
            be<uint32_t> GetPath; //returns fixed name (player/sonic_new.lua) -> game:\\<xenon|win32|common>/player/sonic_new.lua
            be<uint32_t> InArc; 
        };
        stdx::string GetPath(stdx::string filename)
        {
            Vftable* vft = (Vftable*)m_pVftable.get();
            auto name = guest_stack_var<stdx::string>(filename);
            auto return_value = guest_stack_var<stdx::string>();
            GuestToHostFunction<void>(vft->GetPath, return_value.get(), this, name.get());
            return *return_value;
        }
        bool InArc()
        {
            Vftable* vft = (Vftable*)m_pVftable.get();
            return GuestToHostFunction<bool>(vft->InArc, this);
        }
        be<uint32_t> m_MgrRegistryIndex; //used to deallocate resource
        stdx::string m_MgrResourceName;
        stdx::string m_ResourceNameInitial;
        stdx::string m_ResourceName;
        bool m_InResourceManager;
        MARATHON_INSERT_PADDING(3);
    };
}
