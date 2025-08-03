#pragma once

#include <Marathon.inl>

namespace Sonicteam::SoX
{
    class IResourceMgr
    {
    public:
		xpointer<void> m_pVftable;
        be<uint32_t> m_Type;
        MARATHON_INSERT_PADDING(8);
    };
}
