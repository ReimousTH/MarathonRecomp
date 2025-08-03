#pragma once

#include <Marathon.inl>
#include <Sonicteam/SoX/IFileHandle.h>
#include <api/boost/function.hpp>

namespace Sonicteam::SoX
{
    class FileHandleARC:IFileHandle
    {
    public:
        stdx::string m_FilePath;
        uint8_t m_IsLoaded; //24
        uint8_t m_IsProcess; //28
        be<uint64_t> m_Size; //0x30
        xpointer<void> m_Buffer;
        boost::function<bool(void*, unsigned __int64)> m_Initialize; //0x34
    };
}
