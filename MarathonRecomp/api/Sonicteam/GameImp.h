#pragma once

#include <Marathon.inl>

namespace Sonicteam
{
    struct RenderBox
    {
        be<float> w, h, d;
        RenderBox operator*=(float value)
        {
            return
            {
                w = w * value,
                h = h * value,
                d = d * value,
            };
        };
    };


    struct GenerateArea
    {
        MARATHON_INSERT_PADDING(0x40);
        RenderBox Box;

    };
    struct ActiveArea
    {
        MARATHON_INSERT_PADDING(0x18);
        struct AXISBOX {
            MARATHON_INSERT_PADDING(0x10);
            RenderBox Box;
        };
        xpointer<AXISBOX> Area; //0x18
   
    };

    class GameImp : public SoX::MessageReceiver
    {
    public:
        struct PlayerData
        {
            be<uint32_t> ActorID;
            be<uint32_t> RingCount;
            MARATHON_INSERT_PADDING(4);
            be<uint32_t> LifeCount;
            be<uint32_t> ScoreCount;
            be<float> AliveTime;
            be<float> Time;
            MARATHON_INSERT_PADDING(4);
            be<float> SectionSaveTime;
            be<float> GaugeValue;
            be<uint32_t> MaturityLevel;
            be<float> MaturityValue;
            MARATHON_INSERT_PADDING(4);
            be<uint32_t> ExtendRingCount;
            be<uint32_t> GemIndex;
            MARATHON_INSERT_PADDING(0x10);
        };

        MARATHON_INSERT_PADDING(0xE3C);
        PlayerData m_PlayerData[4];

        MARATHON_INSERT_PADDING(0xA24);
        xpointer<ActiveArea> m_ActiveArea[4];
        xpointer<GenerateArea> m_GenerateArea[4];

    };
}
