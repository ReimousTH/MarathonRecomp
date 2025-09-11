#pragma once

#include <Marathon.inl>
#include <api/stdx/vector.h>
#include <api/stdx/string.h>

namespace Sonicteam::SoX
{
    
    class FileSystem
    {
    public:
        struct Vftable
        {
            be<uint32_t> GetFullPath;
            be<uint32_t> GetDirectoryFiles;
            be<uint32_t> IsExist;
            be<uint32_t> Destroy;
        };
        xpointer<Vftable> m_pVftable;

        bool IsExist(stdx::string& path)
        {
            return GuestToHostFunction<void*>(m_pVftable->IsExist, this, &path);
        }

        stdx::string GetFullPath(stdx::string& path)
        {
            return GuestToHostFunction<void*>(m_pVftable->GetFullPath, this, &path);
        }
    };
}
