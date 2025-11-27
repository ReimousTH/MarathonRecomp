#pragma once

#include <Marathon.inl>
#include <Sonicteam/Player/IPlugIn.h>
#include <Sonicteam/SoX/Graphics/Device.h>
#include <Sonicteam/SoX/RefSharedPointer.h>

namespace Sonicteam::Player
{
    class ILoad : public IPlugIn
    {
    public:
        struct Vftable : IPlugIn::Vftable
        {
            be<uint32_t> fpLoadPackage;
            be<uint32_t> fpConnectListenerToInput;
            be<uint32_t> fpSyncFrame;
            be<uint32_t> fpProcessClump01;
            be<uint32_t> fpAddClump;
            be<uint32_t> fpProcessClump02_01;
            be<uint32_t> fpAddShadowClump;
            be<uint32_t> fpILoadUnknown;
            be<uint32_t> fpProcessClump02_03;
            be<uint32_t> fpGetGraphicDevice;
            be<uint32_t> fpGetParticleManager;
            be<uint32_t> fpSendMessageToSFXAgent;
            be<uint32_t> fpAddThread;
        };
    };

    MARATHON_ASSERT_SIZEOF(ILoad, 0x20);
}
