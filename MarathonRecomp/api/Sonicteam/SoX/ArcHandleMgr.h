#pragma once

#include <Marathon.inl>
#include <Sonicteam/SoX/IResourceMgr.h>
#include <Sonicteam/System/Singleton.h>
#include <Sonicteam/System/CreateStatic.h>

namespace Sonicteam::SoX
{
    class ArcHandleMgr:public IResourceMgr, public SSINGLETON(ArcHandleMgr)
    {
    public:
        be<uint32_t> m_Type;
        MARATHON_INSERT_PADDING(8);
    };
}
