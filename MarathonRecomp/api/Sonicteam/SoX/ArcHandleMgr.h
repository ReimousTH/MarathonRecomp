#pragma once

#include <Marathon.inl>
#include <Sonicteam/SoX/IResourceMgr.h>
#include <Sonicteam/System/Singleton.h>
#include <Sonicteam/System/CreateStatic.h>
#include <Sonicteam/SoX/LinkNode.h>
#include <Sonicteam/SoX/ArcHandle.h>

namespace Sonicteam::SoX
{
    struct ArcHandleSearchMeta
    {
        xpointer<const char> cArcPath;
        xpointer<void> vArcFile;
        xpointer<void> vArcResourceFile;
        be<uint32_t> uResourceCompressedSize;
        be<uint32_t> uResourceSize;
        bool IsCompressed; //IsFolder?
        bool IsDownloadContent;
        xpointer<Sonicteam::SoX::ArcHandle> pArcHandle;
    };

    class ArcHandleMgr: public Sonicteam::SoX::IResourceMgr, public Sonicteam::System::Singleton<Sonicteam::SoX::ArcHandleMgr,0x82D36710, Sonicteam::System::CreateStatic<Sonicteam::SoX::ArcHandleMgr,0x82163D20>>
    {
    public:
        Sonicteam::SoX::LinkNode<Sonicteam::SoX::ArcHandle> m_laArcHandle; //LinkArray
        stdx::string m_DefaultPath; //root path,-> 'game:\'
    };
}
