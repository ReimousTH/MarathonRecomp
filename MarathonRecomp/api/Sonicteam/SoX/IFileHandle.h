#pragma once

#include <Marathon.inl>
#include <Sonicteam/SoX/RefCountObject.h>

namespace Sonicteam::SoX
{
    class IFileHandle
    {
    public:
		xpointer<void> m_pVftable;
    };
}
