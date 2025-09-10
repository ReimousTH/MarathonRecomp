#pragma once

#include <Marathon.inl>
#include <Sonicteam/SoX/RefCountObject.h>
#include <api/stdx/string.h>
#include <boost/smart_ptr/function.h>

namespace Sonicteam::SoX
{
    
    class IFileLoader: public Sonicteam::SoX::RefCountObject
    {
    public:
        struct Vftable :RefCountObject::Vftable
        {
            be<uint32_t> Load;
        };

        bool Load(stdx::string& path, boost::function<bool(xpointer<void>, be<uint64_t>)>& loader)
        {
            auto vft = (Vftable*)m_pVftable.get();
            return GuestToHostFunction<bool>(vft->Load, &path, &loader);
        };
    };
}
