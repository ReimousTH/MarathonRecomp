#pragma once

#include <Marathon.inl>
#include <Sonicteam/SoX/IResource.h>
#include <Sonicteam/System/Singleton.h>
#include <Sonicteam/System/CreateStatic.h>

namespace Sonicteam::SoX
{
    template<typename Resouce, typename Manager>
    class IResource2 : public IResource
    {
    public:

        Manager* GetManager()
        {
            Sonicteam::System::Singleton<Manager,0,Sonicteam::System::CreateStatic<Manager,0>>::GetInstance();
            return 0;
        }
    };
}
