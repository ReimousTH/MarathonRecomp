#pragma once

#include <Marathon.inl>
#include <Sonicteam/SoX/IFileHandle.h>
#include <api/stdx/string.h>
#include <boost/smart_ptr/function.h>
#include <Sonicteam/System/CreateStatic.h>
#include <Sonicteam/System/Singleton.h>

namespace Sonicteam::SoX
{
    
    class FileLoaderARC: public IFileHandle, public Sonicteam::System::Singleton<Sonicteam::SoX::FileLoaderARC,0x8262A3E8, Sonicteam::System::CreateStatic<Sonicteam::SoX::FileLoaderARC,0x82D3C17C>>
    {
    };
}
