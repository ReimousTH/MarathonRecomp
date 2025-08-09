#pragma once

#include <Marathon.inl>
#include <api/stdx/string.h>
#include <Sonicteam/Actor.h>

namespace Sonicteam
{
	
    class ActorManager
    {
    public:
        be<uint32_t> m_ActorID[0xFFFF];
        xpointer<Sonicteam::Actor> m_Actor[0xFFFF];
        be<uint32_t> m_LastActorID;
        be<uint32_t> m_LastActorIndex;
    };
}
