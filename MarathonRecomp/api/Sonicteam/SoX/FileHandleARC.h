#pragma once

#include <Marathon.inl>
#include <Sonicteam/SoX/IFileHandle.h>
#include <api/stdx/string.h>
#include <boost/smart_ptr/function.h>

namespace Sonicteam::SoX
{
    
    class FileHandleARC: public IFileHandle
    {
    public:
        stdx::string m_Path;
        bool IsLoaded;
        bool IsProcessed;
        be<uint64_t> m_Size;
        xpointer<void> m_pBuffer;
        boost::function<bool(xpointer<void>, be<uint64_t>)>& m_fFileProcess;
    };
}
